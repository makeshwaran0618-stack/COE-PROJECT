# Smart IV Monitoring System — Review 2 Technical Report

**Student:** [Name / ID]  
**Course / Project:** [Course and project code]  
**Review milestone:** Review 2 — target 35% project completion  
**Repository:** https://github.com/makeshwaran0618-stack/COE-PROJECT  
**Firmware commit:** [commit hash]  
**Report date:** [date]

> Replace every bracketed field with verified information. Remove claims that are not supported by your actual implementation or test evidence.

## 1. Problem statement
Manual checking of IV containers can increase caregiver workload and delay awareness of a low or empty container. This project prototypes a monitoring system that estimates remaining fluid from a load-cell measurement and communicates status to a monitoring interface. The prototype is an adjunct for demonstration and is not a substitute for a clinically approved infusion device or professional monitoring.

## 2. Review 2 objectives
1. Specify and document the actual sensor, controller, ADC interface, power, and communications.
2. Calibrate the load-cell system using reference masses.
3. Implement filtering and bounded conversion of mass into estimated remaining volume.
4. Verify status thresholds and sensor-disconnect behavior.
5. Measure latency at the tested system boundary.
6. Complete structured bench tests and record evidence.

## 3. System architecture
**Physical container → load cell → HX711 bridge ADC → ESP32 → calibration/filtering/threshold logic → JSON serial telemetry → [existing API/dashboard, only if connected and tested].**

Explain the actual data path. Add a labelled architecture diagram and photos of the assembled circuit. Distinguish implemented functions from planned functions.

## 4. Hardware specification
Insert the completed BOM from `BOM_AND_PINOUT.md`. Include manufacturer datasheets and links for exact parts. Explain why the sensor capacity and mechanical fixture suit the expected supported load. Document the HX711 interface pins and supply arrangement.

## 5. Measurement and processing
Describe the calibration procedure, actual calibration factor, tare procedure, bottle tare mass, assumed density, initial volume setting, sample interval, filter window, and status thresholds.

Equations:
- `fluid_mass = max(0, total_mass − empty_container_mass)`
- `estimated_volume ≈ fluid_mass / assumed_density`
- `remaining_percent = 100 × estimated_volume / configured_initial_volume`

State that the volume estimate is approximate and depends on calibration, container tare, mechanical stability, and density assumption.

## 6. Alert logic
Document the exact implemented conditions and resulting states. Include threshold boundary cases and behavior when the sensor is unavailable. Do not claim remote notifications unless the complete path has been tested.

## 7. Test method and results
Attach the completed `tests/test_plan.csv` and calibration sheets. Report actual:
- Sample count and test conditions
- Mean absolute error and maximum absolute error
- Repeatability / variability
- Correct alert transitions and any false positives/negatives
- Median and 95th-percentile latency at the named system boundary
- Sensor disconnect and recovery behavior

Do not replace missing data with estimates or illustrative numbers.

## 8. User testing and feedback
Describe participants by role and count without identifying personal information. Include tasks, survey questions, observed outcomes, feedback themes, changes made, and limitations. If user testing has not yet occurred, state it as planned work.

## 9. Progress against Review 1 feedback
| Reviewer feedback | Action taken | Evidence | Status |
|---|---|---|---|
| Exact hardware details | Completed actual BOM and pinout | BOM, photos, datasheets | [Done/In progress] |
| Calibration and ADC details | Calibration procedure and recorded trials | Calibration sheet | [Done/In progress] |
| Real-time latency | Timestamped test at stated boundary | Log/summary | [Done/In progress] |
| Filtering for movement | Compared raw and filtered readings | Data/plot | [Done/In progress] |
| Structured user testing | Conducted or scheduled with appropriate permission | Anonymized results | [Done/In progress] |

## 10. Limitations and risks
List known limitations: load-cell drift, slosh/movement, incorrect bottle tare, assumptions about density, network loss, stale dashboard data, power failure, and lack of clinical validation. Explain safe fallback behavior and why this prototype must not be used for patient-care decisions.

## 11. Next steps
Prioritize measured calibration, repeatable validation, API integration verification, stale-data/error indication, user testing, and review of security/privacy for any patient-related data.

## 12. Evidence appendix
Include: physical prototype photos, wiring diagram, BOM/datasheets, firmware version/commit, serial logs, calibration data, test results, screenshots of the actual working dashboard, and anonymized feedback summary.
