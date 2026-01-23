## Source Selection and Charging Logic

The power system was designed with an energy redundancy mindset. The goal is that the system keeps running even if the solar input drops or if city electricity is cut. :contentReference[oaicite:0]{index=0}

### Stage 1 Energy Selector and Charging Unit

This stage is the main energy hub where three sources meet:
- Solar panel
- AC grid adapter
- Custom 4S3P battery pack :contentReference[oaicite:1]{index=1}

A CCCV buck converter module (XL4015) is used in the charging path and tuned to safely charge the battery without overshooting voltage limits. :contentReference[oaicite:2]{index=2}

### OR-ing Logic With Schottky Diodes

Multiple power sources cannot be tied together directly because they would fight each other and cause dangerous back-feeding, such as current flowing into the solar panel or the grid adapter. :contentReference[oaicite:3]{index=3}

To prevent this and make selection automatic, the system uses OR-ing logic implemented with multiple Schottky diodes. The diode network forces the system to naturally pick the highest available voltage source while blocking reverse current flow. :contentReference[oaicite:4]{index=4}

Schottky diodes were selected specifically because of their low forward voltage drop, which improves overall energy efficiency. :contentReference[oaicite:5]{index=5}

### Field Safety With Fuses

To make the power system field-safe, fuses are integrated into key paths:
- 2.5A fuse for logic, sensors, and battery protection
- 7.5A fuse on the city electricity and charging path
- 10A fuse as a master protection for the main bus and solar input :contentReference[oaicite:6]{index=6}

### Validated Behavior in Real Tests

The selection logic was validated through stress testing by manually disconnecting sources. When the solar panel was removed, the system transitioned to AC grid power without reboot or data loss. When grid power was also removed, the system continued running on the 4S3P battery pack for an entire week. :contentReference[oaicite:7]{index=7}
