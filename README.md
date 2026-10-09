# Smart IV Monitoring System — Review 2 Upgrade Pack

This is an **add-on pack** for the existing COE-PROJECT repository. It targets the current load-cell/HX711 + ESP32 prototype described in the repository's calibration code and dashboard. It does not overwrite the existing files.

## Included
- `firmware/esp32_hx711_monitor.ino`: ESP32 + HX711 monitoring sketch with rolling-average filtering, bounded values, state classification, and JSON serial output.
- `docs/REVIEW2_TECHNICAL_REPORT.md`: technical report structure mapped to the evaluator's feedback.
- `docs/CALIBRATION_AND_VALIDATION.md`: repeatable calibration and bench-test protocol.
- `docs/BOM_AND_PINOUT.md`: hardware bill-of-materials template and pinout.
- `tests/test_plan.csv`: test cases to execute and fill with real measured results.
- `docs/REVIEW2_SUBMISSION_CHECKLIST.md`: evidence checklist.

## Important: verify before use
The repository's current calibration example uses HX711 DOUT=GPIO4, SCK=GPIO5, calibration factor 465.5, empty-bottle weight 30 g, and a 500 g fluid reference. Treat these as **existing example values**, not verified specifications. Confirm your actual wiring, load cell capacity, calibration factor, bottle tare, and container weight before presenting results.

The sketch assumes the load cell is calibrated to report **grams of total supported mass**, with the bottle and liquid both on the load cell. `EMPTY_BOTTLE_MASS_G` must match the actual empty bottle + cap + any supported hanging hardware. Do not tare with the bottle present and then subtract the bottle mass again.

## Install
1. Back up your current repository.
2. Copy the files/folders into the repository.
3. Open `firmware/esp32_hx711_monitor.ino` in Arduino IDE.
4. Install the `HX711` library compatible with your installed Arduino environment.
5. Select the correct ESP32 board and port.
6. Verify GPIO pins and sensor wiring against your actual circuit before powering.
7. Calibrate using known masses and complete the validation sheet.
8. Only after bench tests pass, connect the JSON output to your existing PHP/API endpoint. The sketch prints JSON to serial; it does **not** automatically post to the server.

## Safety and honesty
This is an academic prototype, not a medical device. Do not use it to control patient infusion or make clinical decisions. Do not claim measured accuracy, latency, user acceptance, or clinical safety unless you actually measured and documented it. Use water/bench loads for testing, not patients.
