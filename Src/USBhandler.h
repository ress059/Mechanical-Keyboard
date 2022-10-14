/** @file USBhandler.h
*
* @brief USB functionality for keyboard.
*
*/

#ifndef USB_HANDLER_H_
#define USB_HANDLER_H_

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>

#include "matrix.h"
#include "LUFA/Drivers/USB/USB.h"
#include "LUFA/Platform/Platform.h"

/** Endpoint address of the Keyboard HID reporting IN endpoint. */
#define KEYBOARD_EPADDR              	(ENDPOINT_DIR_IN | 1)

/** Size in bytes of the Keyboard HID reporting IN endpoint. */
#define KEYBOARD_EPSIZE              	8
#define MAX_USB_BUFFER_SIZE				6

typedef struct
{
	USB_Descriptor_Configuration_Header_t Config;

	// Keyboard HID Interface
	USB_Descriptor_Interface_t            HID_Interface;
	USB_HID_Descriptor_HID_t              HID_KeyboardHID;
	USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
} USB_Descriptor_Configuration_t;

/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
 *  should have a unique ID index associated with it, which can be used to refer to the
 *  interface from other descriptors.
 */
enum InterfaceDescriptors_t
{
	INTERFACE_ID_Keyboard = 0, /**< Keyboard interface descriptor ID */
};

/** Enum for the device string descriptor IDs within the device. Each string descriptor should
 *  have a unique ID index associated with it, which can be used to refer to the string from
 *  other descriptors.
 */
enum StringDescriptors_t
{
	STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
	STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
	STRING_ID_Product      = 2, /**< Product string ID */
};

extern USB_ClassInfo_HID_Device_t Keyboard_HID_Interface;

void SetupHardware(void);
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);


bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize);

void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize);

#endif /* USB_HANDLER_H_ */

