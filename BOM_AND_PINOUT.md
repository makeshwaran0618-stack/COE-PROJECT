# Hardware Bill of Materials and Pinout

Complete the **Actual hardware** column from the parts physically used. Do not leave an example part listed as if it were confirmed.

| Subsystem | Required detail | Actual hardware (fill in) | Evidence |
|---|---|---|---|
| Controller | Exact ESP32 board/module and revision | `[board name / revision]` | Photo, purchase link/datasheet |
| Weight sensor | Load-cell type, rated capacity, mounting arrangement | `[e.g., single-point load cell, ___ kg]` | Label/photo/datasheet |
| ADC/amplifier | HX711 module, supply voltage, output rate/configuration | `HX711 module; verify exact board` | Module photo/datasheet |
| Power | USB / regulated supply, voltage and current rating | `[fill in]` | Label/photo |
| Connectivity | Wi-Fi / USB serial / other | `[fill in; do not claim cloud if not implemented]` | Code/config |
| Alert output | Buzzer/LED, if installed | `[fill in or N/A]` | Photo and test |
| Mechanical fixture | Bottle holder, mounting, anti-sway arrangement | `[fill in]` | Photo/drawing |
| Software | Arduino IDE/core and HX711 library versions | `[fill in exact versions]` | Screenshot/package list |

## Pinout used by the repository example
The existing calibration example indicates:
- HX711 DOUT/DT → ESP32 GPIO 4
- HX711 SCK/CLK → ESP32 GPIO 5

**Verify these connections against the actual circuit.** Do not wire by assumption. Confirm the module's supply and logic levels from its documentation before connecting to the ESP32.

## ADC and measurement notes
The HX711 is a dedicated 24-bit bridge-sensor ADC commonly used with load cells. The effective measurement resolution and accuracy depend on the load cell, excitation, wiring, mechanical mounting, electrical noise, calibration, temperature, and filtering; do not equate nominal ADC bit depth with system accuracy.

## Measurement model
For a platform tared without the bottle:
- `total_mass_g = calibrated load-cell reading`
- `fluid_mass_g = max(0, total_mass_g - empty_bottle_and_cap_mass_g)`
- `fluid_volume_mL ≈ fluid_mass_g / density_g_per_mL`

For a water-like **bench test only**, 1 g ≈ 1 mL is a convenient approximation. If a different solution is used, record its assumed/known density and quantify the error. `fluid_percent = 100 × estimated_remaining_volume / configured_initial_volume`, clamped to 0–100%.

If the platform is tared with the bottle already present, do **not** subtract bottle mass again. Choose one measurement method and document it consistently.
