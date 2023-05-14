<h1 align="center"> Mechanical Keyboard Firmware</h1>
This repository contains the firmware currently being worked on for my Mechanical Keyboard Project (https://www.ianjress.com/#/keyboard/).<br><br><br>

<p align="middle">
  <img src="https://images.squarespace-cdn.com/content/v1/5c7764f9ebfc7f804169e11d/1592416168365-PI403GQHYZGZ2PTTIXA9/Front+View1+Resized.jpg?format=1000w" width="400" />
</p>

<p align="middle">
  <img src="https://images.squarespace-cdn.com/content/v1/5c7764f9ebfc7f804169e11d/1592415739447-7NJ06JUF5XI0GF7KKCOH/Back+View2+Resized.jpg?format=1000w" width="400" />
</p>

<p align="middle">
  <img src="https://images.squarespace-cdn.com/content/v1/5c7764f9ebfc7f804169e11d/1591905753066-03DQTJXZU8PPUQXRHNO6/GIF1.gif?format=1000w" width="400" />
</p>
<br><br><br>

---

<h2 align="center">Repository Directory Structure</h2>
Top-level repository directory structure. If needed, each folder has a separate README explaining its directory structure. For example, src/mainapp/ will have a README explaining its files, src/drivers/ will have a README explaining its directory structure, etc.<br><br>

```
<Repository>
│
├── doc/  # Documentation and images for READMEs.
│
├── src/  # Source Code. 
│   │
│   ├── drivers/    # Target-specific HALs. The README within the drivers/ folder 
│   │                 explains its directory structure more in depth.
│   │
│   ├── mainapp/    # Source code for the main application. Hardware-independent.
│   │                 The README within the mainapp/ folder explains its directory 
│   │                 structure more in depth.
│   │
│   ├── usbstack/   # USB stack meant for any compiler that supports the packed 
│   │                 attribute. Contains USB descriptor headers and checks. The 
│   │                 README within the usbstack/ folder explains its directory 
│   │                 structure more in depth.
│   │
│   └── userconfig/ # Header files where user configures USB settings, USB HID
│                     settings, and keyboard-specific settings. The README within
│                     the userconfig/ folder explains how to configure these settings.
│   
├── tests/  # Unit Tests for CI pipeline. Currently a placeholder directory.
│
│--------------------------------------------------------------------------
│ # Project settings specific to Atmel Studio. In the future looking to
│   get rid of this and use makefiles instead.
│
├── Keyboard.atsln
├── Keyboard.componentinfo.xml
└── Keyboard.cproj
```
