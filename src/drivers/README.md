<h1 align="center">Drivers</h1>
Contains target-specific HALs.
<br><br><br>

---
<h2 align="center">Drivers Directory Structure</h2><br>

```
<src/drivers/>
│
├── atmel/  # Microcontrollers from Atmel and Microchip.
│   │
│   └── avr/  # All microcontrollers within the AVR family.
│       │
│       ├── common/  # Common across all microcontrollers within the AVR family.
│       │   │
│       │   ├── attributes.h       # Function attributes specific to GCC. Ensures 
│       │   │                        AVR GCC v3.1 and up is used when compiling 
│       │   │                        for a microcontroller within the AVR family. This
│       │   │                        ensures all function attributes used throughout the
│       │   │                        code are supported.
│       │   │
│       │   └── target_specific.h  # Defines CPU wordsize, Endianness, and USB 
│       │                            peripheral capabilities for all microcontrollers 
│       │                            within the AVR family.
│       │
│       ├── megaavr/  # megaAVR series microcontrollers.
│       │   │
│       │   └── atmegaxxu4/  # ATMega16U4 and ATMega32U4 HAL.
│       │
│       └── xmega/  # XMEGA series microcontrollers
│           │
│           └── atxmegaxxxb3/  # ATxmega64B3 and ATxmega128B3 HAL.
│
└── common/  # Common across all devices and architectures
    │          however contains dependencies based on file(s) within 
    │          the drivers/ folder
    │
    └── endian.h  # Endianness swapping macros that are defined based
                    on the target's endianness that was specified in 
                    target_specific.h. Used to ensure info is always 
                    sent across the USB bus in Little Endian, regardless
                    of the target architecture.
```