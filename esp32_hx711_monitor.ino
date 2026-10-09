/*
  Smart IV Monitoring System — ESP32 + HX711 bench prototype
  Output: one JSON record per sample over Serial (115200 baud).

  Verify these settings against the actual circuit:
    HX711 DOUT -> GPIO 4
    HX711 SCK  -> GPIO 5

  Calibration requirements:
  - Calibrate the scale with known masses in the final mechanical setup.
  - This sketch assumes get_units() reports grams after set_scale().
  - Set EMPTY_BOTTLE_MASS_G to the measured empty bottle + cap + supported
    hardware mass. Do NOT subtract it if the system has already been tared
    with the bottle present.
  - Fluid density is approximated as 1 g/mL for a water-like bench test only.
    Do not assume this conversion is valid for every clinical solution.

  Prototype only — not for clinical use.
*/
#include <Arduino.h>
#include "HX711.h"

constexpr int HX711_DOUT_PIN = 4;
constexpr int HX711_SCK_PIN  = 5;

// Replace with measured calibration result. Existing repo example: 465.5.
// Calibration factor sign/magnitude depends on load cell and wiring.
float calibrationFactor = 465.5f;

// Replace after weighing the actual empty bottle + cap + supported parts.
constexpr float EMPTY_BOTTLE_MASS_G = 30.0f;

// Configure to the actual starting fluid mass for your bench test.
// For a nominal 500 mL water test, 500 g is an approximation.
constexpr float NOMINAL_INITIAL_FLUID_ML = 500.0f;
constexpr float LOW_LEVEL_PERCENT = 20.0f;
constexpr float EMPTY_LEVEL_PERCENT = 2.0f;
constexpr unsigned long SAMPLE_INTERVAL_MS = 1000;
constexpr int FILTER_SAMPLES = 5;
constexpr float GRAMS_PER_ML_BENCH_APPROX = 1.0f;

HX711 scale;
float samples[FILTER_SAMPLES];
int sampleIndex = 0;
int sampleCount = 0;
unsigned long lastSampleMs = 0;

float filteredMean(float value) {
  samples[sampleIndex] = value;
  sampleIndex = (sampleIndex + 1) % FILTER_SAMPLES;
  if (sampleCount < FILTER_SAMPLES) sampleCount++;

  float total = 0.0f;
  for (int i = 0; i < sampleCount; i++) total += samples[i];
  return total / sampleCount;
}

float clampFloat(float value, float low, float high) {
  if (value < low) return low;
  if (value > high) return high;
  return value;
}

const char* statusFor(float remainingMl, float percent) {
  if (remainingMl <= 0.0f || percent <= EMPTY_LEVEL_PERCENT) return "EMPTY_OR_NEAR_EMPTY";
  if (percent <= LOW_LEVEL_PERCENT) return "LOW";
  return "NORMAL";
}

void setup() {
  Serial.begin(115200);
  delay(500);

  scale.begin(HX711_DOUT_PIN, HX711_SCK_PIN);
  Serial.println(F("{\"type\":\"info\",\"message\":\"Smart IV bench monitor starting\"}"));

  if (!scale.is_ready()) {
    Serial.println(F("{\"type\":\"error\",\"message\":\"HX711 not ready; check wiring and power\"}"));
    return;
  }

  scale.set_scale(calibrationFactor);

  // Tare the bare weighing platform only. Place the bottle after this step.
  Serial.println(F("{\"type\":\"instruction\",\"message\":\"Remove bottle and all load; taring platform\"}"));
  delay(2000);
  scale.tare(20);
  Serial.println(F("{\"type\":\"info\",\"message\":\"Tare complete; place bottle on platform\"}"));
}

void loop() {
  if (millis() - lastSampleMs < SAMPLE_INTERVAL_MS) return;
  lastSampleMs = millis();

  if (!scale.is_ready()) {
    Serial.println(F("{\"type\":\"error\",\"message\":\"HX711 not ready\"}"));
    return;
  }

  // Read multiple conversions before filtering. Check latency on your hardware.
  float rawTotalMassG = scale.get_units(5);
  float smoothTotalMassG = filteredMean(rawTotalMassG);

  // Because tare was done with the platform empty, total mass includes bottle.
  float fluidMassG = smoothTotalMassG - EMPTY_BOTTLE_MASS_G;
  if (fluidMassG < 0.0f) fluidMassG = 0.0f;

  float fluidMl = fluidMassG / GRAMS_PER_ML_BENCH_APPROX;
  float percent = (fluidMl / NOMINAL_INITIAL_FLUID_ML) * 100.0f;
  percent = clampFloat(percent, 0.0f, 100.0f);
  fluidMl = clampFloat(fluidMl, 0.0f, NOMINAL_INITIAL_FLUID_ML);

  const char* status = statusFor(fluidMl, percent);

  Serial.print(F("{\"type\":\"sample\",\"uptime_ms\":"));
  Serial.print(millis());
  Serial.print(F(",\"mass_total_g\":"));
  Serial.print(smoothTotalMassG, 2);
  Serial.print(F(",\"fluid_mass_g\":"));
  Serial.print(fluidMassG, 2);
  Serial.print(F(",\"fluid_volume_ml_approx\":"));
  Serial.print(fluidMl, 2);
  Serial.print(F(",\"fluid_percent\":"));
  Serial.print(percent, 2);
  Serial.print(F(",\"status\":\""));
  Serial.print(status);
  Serial.println(F("\"}"));
}
