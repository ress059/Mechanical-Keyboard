<h1 align="center">USB Stack</h1>
USB stack meant for any compiler that supports the packed attribute. Contains USB descriptor headers and checks.
<br><br><br>

---
<h2 align="center">USB Stack Directory Structure</h2><br>

```
<src/usbstack/>
│
├── class/  # Specific to USB classes. E.g. Audio class, HID class, 
│   │         printer class, etc.
│   │
│   └── hid/  # HID class.
│       │
│       ├── common/  # Common across all HID class devices and hosts.
│       │   │
│       │   ├── usb_hid_descriptors.h   # Standard HID descriptors. Uses GCC packed attribute.
│       │   │
│       │   └── usb_hid_version.h       # The HID version the codebase currently supports.
│       │
│       ├── device/  # Specific to HID Devices.
│       │   │
│       │   └── usb_hid_device_check_descriptors.h/.c  # Functions that check if an 
│       │                                                HID device's descriptors are 
│       │                                                filled out with valid info.
│       │
│       └──  host/   # Specific to HID Hosts. Currently a placeholder directory.
│
├── core/   # General USB code.
│   │
│   ├── common/  # Common across all USB devices and hosts.
│   │   │
│   │   ├── usb_std_descriptors.h  # Standard USB descriptors. Uses GCC packed attribute.
│   │   │
│   │   └── usb_version.h          # The USB version the codebase currently supports.
│   │
│   ├── device/  # Specific to USB Devices.
│   │   │
│   │   └── usb_std_device_check_descriptors.h/.c  # Functions that check if a 
│   │                                                USB device's descriptors are 
│   │                                                filled out with valid info.
│   │
│   └── host/   # Specific to USB Hosts. Currently a placeholder directory.
│
│--------------------------------------------------------------------------
│ # USB Development code when original approach was to create a general USB HAL.
│   This code will be refactored and a USB HAL will be made for each separate target
│   instead. Keeping these placeholders here for now.
│
├── usb.h/.c
├── usb_event_handler.h
├── usb_handler.h/.c
└── usb_registers.h
```
