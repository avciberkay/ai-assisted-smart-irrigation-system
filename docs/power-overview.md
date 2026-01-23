## Power Overview

The system uses a multi-source, autonomous power architecture designed for continuous operation under varying environmental and grid conditions.

Instead of relying on a single energy source, the system integrates three independent power inputs:
- A high-voltage solar panel
- A city electricity adapter
- A custom-built 4S3P lithium-ion battery pack

A dedicated power distribution and selection board evaluates source availability and automatically routes the most suitable energy source to the system. When solar energy is available, it is prioritized to power the system and charge the battery. During nighttime, city electricity is preferred due to lower cost. In the event of grid failure, the system seamlessly switches to battery power without interrupting operation.

Key design goals of the power system:
- Autonomous source selection without human intervention
- Battery charging and protection handled at hardware level
- Stable voltage delivery to digital and motor loads
- Protection against over-current, reverse polarity, and voltage instability
- Support for long-term unattended outdoor operation

This architecture allows the system to remain operational across power outages, changing weather conditions, and remote deployment scenarios, while significantly reducing energy waste and manual maintenance requirements.
