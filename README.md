# Test machine controller firmware

  Firmware for STM32H743 and STM32F767 boards realising control, acquare telemetry from sensors, data exchange with host PC, and other services.

## Features:
- Acquare sensors, PID regulating in closed loop at ~10 kHz frequency.
- Control implementation for servo hydraulic, electrical mechanic, electrical hydraulic type of testing machine.
- 11 modes: None, Constant Level, Constant Strain, Constant Displacement, Constant Deformation, Sinus Strain, Sinus Deformation, Sinus Displacement, Sinus Based Displacement, Sinus Based Strain, Sinus Based Deformation.
- Synchonous TM values (Time, Position, Strain, Deformation, Cycles and Diagnostics channels) in interrupt context up to 1 kHz.
- Based on the sine calculating set points for cyclic modes in interrupt context up to 1 kHz.
- Constant movement calculating set points for constant modes in interrupt context up to 1 kHz.
- 3 protection levels for displacement, strain and deformation channels
- Internal fast tasks (closed loop) for fast state machine type routines.
- Async low speed task for not demanding on execution time routines.
- Saving all machine params in RAM, Flash and Backup RAM (optional);
- Data exchange protocol over Ethernet (host PC throught TCP/IP) and  RS-485 (digital remote controller)
- 
