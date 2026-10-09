# Review 2 Submission Checklist

## Technical completeness
- [ ] Exact ESP32 board model/revision recorded
- [ ] Load-cell capacity/type and HX711 module documented
- [ ] Pinout, power supply, and wiring diagram verified
- [ ] Calibration factor measured on this actual assembly
- [ ] Empty container + cap mass measured
- [ ] Tare procedure explained and consistent
- [ ] Fluid density / volume approximation documented
- [ ] Filter window and sample interval documented
- [ ] Low-level threshold and boundary behavior tested
- [ ] Sensor-disconnect and recovery behavior tested
- [ ] JSON/API/dashboard connection tested end-to-end, if claimed

## Evidence
- [ ] Clear photos of hardware and setup
- [ ] Datasheets / manufacturer links
- [ ] Calibration table with reference masses and repeated trials
- [ ] Raw vs filtered movement test data
- [ ] Alert test matrix and actual results
- [ ] Latency measurement with exact system boundary
- [ ] Screenshots/logs with timestamps
- [ ] User feedback only if genuinely collected with appropriate permission
- [ ] GitHub commits show the changes and meaningful messages
- [ ] Report includes limitations and explicitly states prototype is not clinical equipment

## Before submitting
- [ ] Replace all `[bracketed placeholders]`
- [ ] Remove unverified claims and fake/demo patient details from screenshots where possible
- [ ] Check that no passwords, API keys, tokens, or personal data are committed
- [ ] Run the firmware and capture a real demonstration
- [ ] Ask supervisor to confirm acceptance criteria and report format
