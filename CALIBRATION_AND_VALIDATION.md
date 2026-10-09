# Calibration and Bench Validation Protocol

## Purpose and scope
This procedure evaluates a prototype load-cell measurement of an IV-container surrogate. It is not a clinical validation and must not be used to guide real infusion care.

## Equipment
- Final assembled load cell, HX711 module, ESP32, and mechanical holder
- Reference masses covering the intended operating range (record the reference scale and its resolution)
- Empty container with cap and any attached parts that remain supported by the load cell
- Water for controlled bench tests
- Computer with serial monitor/log capture
- Stopwatch or timestamped log for latency measurements

## A. Mechanical and electrical inspection
1. Photograph the assembled setup and record load-cell rating, board model, supply, pinout, firmware version, and library version.
2. Check that wires do not pull on the load cell and that the container hangs freely without touching nearby objects.
3. Confirm HX711 readiness and stable readings before adding a load.
4. Keep liquids away from electronics; use a spill-safe setup.

## B. Calibration procedure
1. Install the sensor in its final mechanical position.
2. Ensure the platform is unloaded and tare it. If the firmware tares the bare platform, keep the bottle off the platform during tare.
3. Place a known reference mass at the normal load position. Record reference mass and displayed mass.
4. Repeat for at least five masses spanning the expected operating range. Use three trials per mass.
5. Determine calibration factor using the library's documented calibration procedure; do not assume the example factor 465.5 is correct for your unit.
6. Repeat the sequence after calibration.
7. Calculate for each reading:
   - Absolute error (g) = measured mass − reference mass
   - Absolute error magnitude (g) = |measured − reference|
   - Percentage error = 100 × |measured − reference| / reference (exclude zero reference)
   - Mean absolute error (MAE) = average of absolute error magnitudes
8. Record the actual factor, conditions, reference instrument, and any recalibration.

## C. Bottle tare and volume conversion
1. Weigh the empty bottle + cap + all parts supported by the load cell. Record this as `EMPTY_BOTTLE_MASS_G`.
2. Add measured water mass in known increments and record the estimated remaining volume.
3. Document the initial volume configured in firmware.
4. Do not report volume accuracy until the estimate is compared with a reference measurement.
5. If fluid volume is inferred from mass, state the density assumption and its limits.

## D. Filtering and slosh test
1. Capture at least 60 seconds of readings with the container stationary.
2. Gently introduce a repeatable small movement (do not spill) and capture another 60 seconds.
3. Compare raw and filtered standard deviation and response delay.
4. A moving average reduces short-term noise but introduces lag. Record both the reduction in variability and the time taken to reflect a sustained change.
5. Do not claim that filtering eliminates all motion artifacts.

## E. Alert-threshold test
Use controlled bench values above, at, and below the configured threshold. Record the input, expected state, observed state, and whether the transition is correct. Repeat each case at least five times. Confirm how the system behaves at zero, negative/noisy readings, sensor disconnect, and startup.

## F. Latency
For each run, timestamp the physical/simulated threshold crossing and the first corresponding serial/API/dashboard alert. Compute:
`latency_ms = alert_timestamp_ms − threshold_crossing_timestamp_ms`
Report sample count, median, 95th percentile, maximum, and test conditions. If only serial output is tested, call it **sensor-to-serial latency**, not end-to-end dashboard latency.

## G. User testing
Only conduct user testing with permission and appropriate supervision. Do not test on patients or use real clinical infusion. Ask target users to perform defined tasks with a simulated setup. Collect anonymous, structured feedback:
- Task completion (pass/fail)
- Time to identify low-level warning
- Whether status/units were understood
- False alarms or missed alerts observed
- Ease-of-use rating (e.g. 1–5)
- Suggested improvements

Record number and role of participants, test environment, consent/approval if applicable, limitations, and actual results. Never invent participants or results.

## Results table template
| Trial | Reference mass (g) | Measured mass (g) | Absolute error (g) | Percentage error (%) | Notes |
|---|---:|---:|---:|---:|---|
| 1 | | | | | |
| 2 | | | | | |
| 3 | | | | | |

## Acceptance criteria
Set numeric criteria before testing with your supervisor. Example criteria must be labelled as **proposed targets**, not achieved results, until verified. Include sensor accuracy, alert correctness, maximum acceptable delay, and sensor-disconnect behavior.
