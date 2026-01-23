## Battery Pack Design

The system uses a custom-built lithium-ion battery pack designed to support uninterrupted operation during power outages and low solar availability.

### Configuration

The battery pack is configured as a 4S3P arrangement:
- 4 cells in series to increase system voltage
- 3 cells in parallel per series group to increase capacity

This configuration provides a balance between voltage stability, current capability, and energy density suitable for both logic circuits and motor loads.

### Protection and Management

A dedicated Battery Management System (BMS) is integrated with the pack to provide:
- Over-charge protection
- Over-discharge protection
- Over-current protection
- Cell balancing

These protections ensure safe operation and extend battery lifespan under continuous outdoor use.

### Charging Strategy

Charging is handled externally by a CCCV buck converter and controlled at the hardware level.
The battery is charged only when a suitable external source is available, and reverse current flow into the charger is prevented by diode isolation.

### Real-World Validation

The battery pack was tested under real operating conditions.
During testing, the system continued operating for multiple days solely on battery power without voltage instability or unexpected shutdowns.
