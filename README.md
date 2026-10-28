# Smart IV Monitoring System

## Overview
The Smart IV Monitoring System is an academic prototype intended to support monitoring of intravenous (IV) fluid levels and alert staff when a configured threshold is reached. The design aims to make fluid-level status easier to observe and reduce the need for repeated manual visual checks.

> **Safety notice:** This repository describes an academic prototype for controlled bench testing only. It is not a certified medical device and must not be used to monitor or treat patients, control an infusion, or replace clinical supervision or approved hospital equipment.

## Problem Statement
IV fluid levels may require repeated observation by healthcare staff. A monitoring aid could help make fluid-level changes more visible and provide an additional alert when a predefined threshold is reached. Any such aid must be tested for accuracy, reliability, usability, and safety before clinical consideration.

## Objectives
- Monitor IV-container fluid level using the sensor method implemented in the prototype.
- Process sensor readings and apply a configured threshold.
- Provide local alerts and, if implemented, wireless status updates.
- Record calibration, test conditions, and limitations transparently.
- Build a low-cost prototype that can be evaluated and improved through controlled testing.

## Key Features
- Sensor-based fluid-level estimation (confirm the exact sensor configuration in the hardware BOM).
- Threshold-based alert logic.
- Local audible/visual indication, if installed.
- Optional Wi-Fi dashboard or remote notifications, only if implemented in the current version.
- Calibration and test documentation.

## System Architecture
**Conceptual data flow:**  
`IV container → sensor → signal-conditioning/ADC module (if required) → microcontroller → filtering and threshold logic → local alert / wireless dashboard (if implemented)`

Add the architecture image to `docs/system_architecture.png` and embed it below:

<!-- Replace the path if your architecture image is stored elsewhere. -->
![Smart IV Monitoring System architecture](docs/system_architecture.png)

## Hardware
See [`Smart_IV_Hardware_Bill_of_Materials.docx`](Smart_IV_Hardware_Bill_of_Materials.docx) for the proposed bill of materials.

**Important:** The component list currently describes a proposed configuration. Before claiming that a component is implemented, verify its exact model and ensure it matches the actual prototype. Document actual controller, sensor part numbers, ADC module, wiring, power source, and communication method.

## Software
Document the actual programming language, framework, libraries, and dashboard/server used by your implementation. Do not list technologies that are not present in the code.

## Calibration and Testing
Before reporting performance, document:
- Calibration method and reference weights or other reference measurements.
- Measured readings and calculation of error.
- Sampling rate and filtering settings.
- Threshold configuration and rationale.
- Alert latency, missed alerts, and false-alert observations.
- Network-disconnection and power-interruption behavior, where applicable.

Use actual measurements only. Do not describe planned tests as completed or report example values as measured results.

## Target Users
See [`TARGET_USERS_Smart_IV_Monitoring_System.docx`](TARGET_USERS_Smart_IV_Monitoring_System.docx) for the intended-user summary, including nursing staff, patients receiving IV fluids, medical staff, hospital administrators, and biomedical engineers.

## Limitations and Safety
See [`Smart_IV_Limitations_and_Safety.docx`](Smart_IV_Limitations_and_Safety.docx).

Key limitations may include:
- Readings affected by movement, vibration, tubing forces, container type, and sensor drift.
- False or missed alerts due to calibration, threshold, firmware, or sensor problems.
- Wireless notifications may be delayed or unavailable during network failure.
- A fluid-level threshold does not confirm the prescribed infusion rate or detect every infusion-related problem.
- The prototype has not been established as clinically validated or medically certified.

## Repository Structure
Update this example to match the files actually committed to the repository:

```text
COE-PROJECT/
├── README.md
├── docs/
│   ├── system_architecture.png
│   └── [other project documentation]
├── src/
│   └── [source code, if applicable]
├── images/
│   └── [actual prototype photos]
└── [hardware and testing documents]
```

## How to Run
Add the real setup steps for your project:
1. Identify the exact controller board and required software.
2. Install the required development environment and dependencies.
3. Connect the hardware according to the verified pinout.
4. Configure Wi-Fi or server settings only if those features are implemented.
5. Upload/run the firmware and verify readings using a non-clinical bench setup.
6. Test alerts using controlled test conditions and record the results.

Do not commit Wi-Fi passwords, API keys, personal data, or other secrets to the repository.

## Current Development Status
**Status:** Academic prototype / development stage.  
Replace this status with the actual current stage, and list which features are implemented, in progress, and planned.

## Future Improvements
- Improve calibration and repeatability.
- Evaluate filtering for movement-related noise without introducing excessive alert delay.
- Add connection-status and power-failure handling, if applicable.
- Conduct structured usability testing with intended users when appropriate approvals and supervision are available.
- Complete systematic bench testing and document results before any clinical consideration.

## Contributors
Add team member names and roles here, if appropriate.

## License
Add a license only if you intend to specify the terms under which others may use, modify, and distribute this project.
