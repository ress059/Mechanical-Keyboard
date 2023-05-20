/**
 * @file usb_hid_device_check_descriptors.c
 * @author Ian Ress
 * @brief Functions to check if descriptors created for an HID Device are valid.
 * Currently follows HID v1.11
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "endian.h"
#include "usb_hid_descriptors.h"


/**
 * @brief Applies checks to parameters that apply to all Interface Descriptors used in USB HID
 * Devices. These include: bLength, bDescriptorType, bInterfaceClass, bInterfaceSubClass, and 
 * bInterfaceProtocol.
 * 
 * @warning Parameters that describe how the user sets up their Descriptor Tree for their specific
 * device are not checked.
 * 
 * @param Interface_Descriptor pointer to HID Interface Descriptor to check.
 * 
 * @return True if HID Interface Descriptor is valid. False otherwise.
 * 
 */
bool USB_HID_Interface_Descriptor_Check(const USB_Std_Interface_Descriptor_t * const HID_Interface_Descriptor)
{
    bool valid = true;

    if (!HID_Interface_Descriptor)
    {
        valid = false;
    }

    /**
     * USB HID Spec v1.11:
     * HID Devices must indicate they are apart of the HID Class in their Interface Descriptor
     * by setting bInterfaceClass = 3. bInterfaceSubClass indicates if the device supports
     * boot interfaces and must be set to either 0 or 1. Remaining values are reserved and
     * should not be used. If it is not a Boot Device (bInterfaceSubClass = 0), then 
     * bInterfaceProtocol must also be set to 0. If it is a Boot Device, bInterfaceProtocol 
     * must be set to either 1 or 2. Remaining values are reserved and should not be used.  
     */
    else if (   (USB_Std_Interface_Descriptor_Check(HID_Interface_Descriptor) != true) || \
                (HID_Interface_Descriptor->bInterfaceClass != HID_CLASS_CODE) || \
                (HID_Interface_Descriptor->bInterfaceSubClass != HID_NO_SUBCLASS && 
                    HID_Interface_Descriptor->bInterfaceSubClass != HID_BOOT_INTERFACE_SUBCLASS) || \
                (HID_Interface_Descriptor->bInterfaceSubClass == HID_NO_SUBCLASS &&
                    HID_Interface_Descriptor->bInterfaceProtocol != HID_NO_PROTOCOL_CODE) || \
                (HID_Interface_Descriptor->bInterfaceProtocol != HID_NO_PROTOCOL_CODE && \
                    HID_Interface_Descriptor->bInterfaceProtocol != HID_KEYBOARD_INTERFACE_CODE && \
                    HID_Interface_Descriptor->bInterfaceProtocol != HID_MOUSE_INTERFACE_CODE)   )
    {
        valid = false;
    }
    return valid;
}




bool USB_HID_Std_HID_Descriptor_Check(const USB_HID_Std_HID_Descriptor_t * Std_HID_Descriptor)
{
    //bLength < sizeof(USB_HID_Std_HID_Descriptor_t)
    bool valid = true;

    if (!Std_HID_Descriptor)
    {
        valid = false;
    }

    /**
     * USB HID Spec v1.11:
     * HID Devices must indicate they are apart of the HID Class in their Interface Descriptor
     * by setting bInterfaceClass = 3. bInterfaceSubClass indicates if the device supports
     * boot interfaces and must be set to either 0 or 1. Remaining values are reserved and
     * should not be used. If it is not a Boot Device (bInterfaceSubClass = 0), then 
     * bInterfaceProtocol must also be set to 0. If it is a Boot Device, bInterfaceProtocol 
     * must be set to either 1 or 2. Remaining values are reserved and should not be used.  
     */

    /**
     * Along with general Device Descriptor checks, bcdUSB's Endianness is checked.
     * It must be Little Endian. bcdUSB will always contain a Major Version in BCD format
     * so we mask against that. On Little Endian targets the LE16_RUNTIME macro does
     * nothing so bcdUSB should be stored in the form 0x0V00 where V is the Major 
     * Version. LE16_RUNTIME(bcdUSB) will return 0x0V00.
     * 
     * On Big Endian targets the LE_16RUNTIME macro will swap the bytes of its argument.
     * bcdUSB needs be stored in the form 0x000V so it is sent across the bus in Little 
     * Endian. LE16_RUNTIME(bcdUSB) will swap the bytes and return 0x0V00 in this case
     * since we are compiling on a Big Endian target.
     */


    else if (   (Std_HID_Descriptor->bLength != sizeof(USB_HID_Std_HID_Descriptor_t)) || \
                (Std_HID_Descriptor->bDescriptorType != HID_DESCRIPTOR_TYPE) || \
                (!(LE16_RUNTIME(Std_HID_Descriptor->bcdHID) & 0x0F00)) || \
                (Std_HID_Descriptor->bcdHID < )
        
        
        
        
        
        
        (USB_Std_Interface_Descriptor_Check(HID_Interface_Descriptor) != true) || \
                (HID_Interface_Descriptor->bInterfaceClass != HID_CLASS_CODE) || \
                (HID_Interface_Descriptor->bInterfaceSubClass != HID_NO_SUBCLASS && 
                    HID_Interface_Descriptor->bInterfaceSubClass != HID_BOOT_INTERFACE_SUBCLASS) || \
                (HID_Interface_Descriptor->bInterfaceSubClass == HID_NO_SUBCLASS &&
                    HID_Interface_Descriptor->bInterfaceProtocol != HID_NO_PROTOCOL_CODE) || \
                (HID_Interface_Descriptor->bInterfaceProtocol != HID_NO_PROTOCOL_CODE && \
                    HID_Interface_Descriptor->bInterfaceProtocol != HID_KEYBOARD_INTERFACE_CODE && \
                    HID_Interface_Descriptor->bInterfaceProtocol != HID_MOUSE_INTERFACE_CODE)   )
    {
        valid = false;
    }
    return valid;
}