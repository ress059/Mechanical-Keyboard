<h1 align="center">User-Definable Settings</h1>
This README contains an overview of all user-definable settings. See the Source Code for more detailed comments.<br><br><br>

<h1 align="center">Table Of Contents</h1>

[KeyboardConfig.h](#keyboardconfigh)<br>
[USBConfig.h](#usbconfigh)<br>
[USBEventHandler.c](#usbeventhandlerc)<br>
[USBHIDConfig.h](#usbhidconfigh)
<br><br><br>

---
<a id="keyboardconfigh"></a> <h2 align="center">KeyboardConfig.h</h2>
Keyboard layouts, pin assignments, and settings are defined within this header file.<br><br>

```C
#define DEBOUNCE_TIME           <Enter value>

/* Example */
#define DEBOUNCE_TIME           5
```
+ Keyswitch debounce time in milliseconds. The example above sets the debounce time to 5ms.<br><br><br>


```C
#define NUM_ROWS                <Enter value>

/* Example */
#define NUM_ROWS                4
```
+ Number of rows in your keyboard layout. For example, the layout below is 4 rows.

<p align="center">
  <img src= "../../Docs/Images/UserConfig/Basic-Keyboard-Layout.png" width="400"/>
</p><br><br>


```C
#define NUM_COLUMNS             <Enter value>

/* Example */
#define NUM_COLUMNS             10
```
+ Number of columns in your keyboard layout. For example, the layout above is 10 columns.<br><br><br>


```C
#define NUM_LAYERS              <Enter value>

/* Example */
#define NUM_LAYERS              3
```
+ Layers are additional layouts that you can access by pressing a designated key on your keyboard. For example on all keyboards, holding down the Shift Key accesses a second layer with all uppercase letters and symbols. A common use-case is to have a press of the Fn Key access another user-definable layer. Define how many of these layers are on your keyboard here.<br><br><br>


```C
#define ROW_PINS                {PIN_xx, PIN_xx,...}

/* Example */
#define ROW_PINS                {PIN_PB0, PIN_PB1, PIN_PB2, PIN_PC7}
```
+ Each row is connected to a GPIO pin on the target CPU in order to detect key presses. Therefore this definition depends on the schematic and PCB layout of your keyboard. Below is the pinout for an ATmega32U4 which is one of the supported targets in this codebase.

<p align="center">
  <img src= "../../Docs/Images/UserConfig/atmega32u4-pinout.png" width="300" />
</p>

+ PB0, PB1, PB2, PC7, etc are GPIO pins. If the rows are connected to PB0, PB1, PB2, and PC7, your **ROW_PINS** definition would be **{PIN_PB0, PIN_PB1, PIN_PB2, PIN_PC7}**<br><br><br>


```C
#define COLUMN_PINS     {PIN_xx, PIN_xx,...}

/* Example */
#define COLUMN_PINS     {PIN_PC6, PIN_PC5, PIN_PC4,...}
```
+ Exact same logic as **ROW_PINS**. See **ROW_PINS** explanation above. 
+ **Note: A column pin cannot be the same as a row pin.**<br><br><br>


```C
#define KEY_LAYOUT      { \ /* Layer 1 */
                            {KEY_ESC, KEY_1, KEY_2,...} \
                            {KEY_TAB, KEY_Q, KEY_W,...} \
                            ...
                        } \
                        { \ /* Layer 2 */
                            ...
                        }...

```
+ The actual keyboard layout. The full list of available keys are defined in **Keycodes.h**.

<br><br>

---
<a id="usbconfigh"></a><h2 align="center">USBConfig.h</h2>
The USB version, clock sources, speed settings, and Control Endpoint configurations are defined within this header file.<br><br>

```C
#define USB_VERSION_                    <Enter value 0xMMnn>

/* Example */
#define USB_VERSION_                    0x0200
```
+ The USB Version to compile for in BCD format 0xMMnn where MM is the major version and nn is the minor version. For example if you want to compile for USB v1.0, **USB_VERSION_** would be set to 0x0100. If you want to compile for USB v2.0, **USB_VERSION_** would be set to 0x0200.
+ **Note: A compilation error will occur if this is set to a version that is not supported either by the target CPU or the codebase. The current codebase supports USB v2.0 and lower.**<br><br><br>


```C
#define USB_LOW_SPEED_DEVICE            <Enter 0 or 1>

/* Example */
#define USB_LOW_SPEED_DEVICE            0
```
+ Set to 1 if you want a Low Speed Device. Otherwise set to 0. 
+ **Note: Only a single speed setting (USB_LOW_SPEED_DEVICE or USB_FULL_SPEED_DEVICE) must be set to 1. A compilation error will occur if this is not followed.**<br><br><br>


```C
#define USB_FULL_SPEED_DEVICE           <Enter 0 or 1>

/* Example */
#define USB_FULL_SPEED_DEVICE           1
```
+ Set to 1 if you want a Full Speed Device. Otherwise set to 0. 
+ **Note: Only a single speed setting (USB_LOW_SPEED_DEVICE or USB_FULL_SPEED_DEVICE) must be set to 1. A compilation error will occur if this is not followed.**<br><br><br>


```C
#define USB_SELF_POWERED_DEVICE         <Enter 0 or 1>

/* Example */
#define USB_SELF_POWERED_DEVICE         0
```
+ When the USB Device isn't plugged in can it still be powered on? Do you want the device to be responsible for supplying its own power instead of the Host? Set to 1 if the answer is yes to to both of these questions. Otherwise set to 0. 
+ For example if I want to have a computer power a USB keyboard that I plug into it, **USB_SELF_POWERED_DEVICE** would be set to 0.<br><br><br>


```C
#define USB_USE_VBUS_DETECTION          <Enter 0 or 1>

/* Example */
#define USB_USE_VBUS_DETECTION          0
```
+ Set to 1 if you want the device to know when it is plugged in. A user-definable interrupt will execute when the device is plugged in.
+ **Note: This can only be used for self-powered devices (USB_SELF_POWERED_DEVICE set to 1). The GPIO pin used for VBUS detection must also be defined in USB_VBUS_DETECT_GPIO. A compilation error will occur if this is not followed.**<br><br><br>


```C
#define USB_VBUS_DETECT_GPIO            {PIN_xx}

/* Example */
#define USB_VBUS_DETECT_GPIO            {PIN_PB2}
```
+ The GPIO pin used to detect a VBUS signal. For example if this is assigned to pin PB2, **USB_VBUS_DETECT_GPIO** would be **{PIN_PB2}**<br><br><br>


```C
#define USB_USE_INTERNAL_OSCILLATOR     <Enter 0 or 1>

/* Example */
#define USB_USE_INTERNAL_OSCILLATOR     0
```
+ Set to 1 to have the target CPU's Internal Oscillator be used as the USB clock source. Otherwise set to 0.
+ **Note: Only a single clock source (USB_USE_INTERNAL_OSCILLATOR or USB_USE_EXTERNAL_OSCILLATOR) must be set to 1. A compilation error will occur if this is not followed. Some targets also do not have an Internal Oscillator so this feature can't be used. A compilation error will occur in this situation.**
+ **Note: On some targets this will also set the Internal Oscillator as the CPU clock.**<br><br><br>


```C
#define USB_USE_EXTERNAL_OSCILLATOR     <Enter 0 or 1>

/* Example */
#define USB_USE_EXTERNAL_OSCILLATOR     1
```
+ Set to 1 to have an External Oscillator be used as the USB clock source. Otherwise set to 0.
+ **Note: Only a single clock source (USB_USE_INTERNAL_OSCILLATOR or USB_USE_EXTERNAL_OSCILLATOR) must be set to 1. A compilation error will occur if this is not followed.**<br><br><br>


```C
#define USB_EXTERNAL_CLOCK_FREQUENCY     <Enter value>

/* Example */
#define USB_EXTERNAL_CLOCK_FREQUENCY     16000000 /* 16MHz */
```
+ The External Oscillator's frequency in Hz. This value is ignored if **USB_USE_EXTERNAL_OSCILLATOR** is set to 0.
+ **Note: The External Oscillator has to be a frequency that can drive the target CPU and its USB Controller (either by itself or via prescaling). These acceptable values will be defined in the target CPU's datasheet. A compilation error will occur if an External Oscillator has an invalid frequency for the target CPU being compiled on.**<br><br><br>


```C
#define USB_CONTROL_ENDPOINT_SIZE       <Enter value>

/* Example */
#define USB_CONTROL_ENDPOINT_SIZE       8 /* 8 bytes */
```
+ The Control Endpoint's size in bytes.
+ **Note: This must be set to 8, 16, 32, or 64. If this is a Low Speed Device (USB_LOW_SPEED_DEVICE set to 1) this can only be set to 8. A compilation error will occur if this is not followed.** 

<br><br>

---
<a id="usbeventhandlerc"></a><h2 align="center">USBEventHandler.c</h2>
User-definable event handlers and error handlers. TODO: <br><br>

<br><br>

---
<a id="usbhidconfigh"></a><h2 align="center">USBHIDConfig.h</h2>
The HID version and HID endpoint configurations are defined within this header file.<br><br>

```C
#define HID_VERSION_            <Enter value 0xMMnn>

/* Example */
#define HID_VERSION_            0x0111
```
+ The HID version to compile for in BCD format 0xMMnn where MM is the major version and nn is the minor version. For example, 0x0111 corresponds to v1.11 of the HID spec.
+ **Note: A compilation error will occur if this is set to a version that is not supported by this codebase. The current codebase supports HID spec v1.11 and lower.**<br><br><br>


```C
#define HID_ENDPOINT_NUMBER     <Enter value>

/* Example */
#define HID_ENDPOINT_NUMBER     1
```
+ The endpoint to send and receive HID data from.
+ **Note: This must be set to a non-zero value. Do not set to 0 as this is always reserved for the Control Endpoint. A compilation error will occur if this is not followed.**<br><br><br>


```C
#define HID_ENDPOINT_SIZE       <Enter value>

/* Example */
#define HID_ENDPOINT_SIZE       64 /* 64 bytes */
```
+ The size of the HID endpoint in bytes.
+ **Note: This must be 8 bytes or less for Low Speed Devices (USB_LOW_SPEED_DEVICE set to 1). This must be 64 bytes or less for Full Speed Devices (USB_FULL_SPEED_DEVICE set to 1). A compilation error will occur if this is not followed.**
