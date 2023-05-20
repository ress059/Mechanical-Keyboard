/**
 * @file usb_std_device_check_descriptors.c
 * @author Ian Ress
 * @brief Functions to check if descriptors created for a standard USB Device are valid.
 * Currently follows USB v2.0.
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 */


#include "endian.h"
#include "usb_std_device_check_descriptors.h"
#include "usb_version.h"


/**
 * @brief Applies checks to parameters that apply to all Device Descriptors. These include:
 * bLength, bDescriptorType, bcdUSB, and bMaxPacketSize0.
 * 
 * @warning Parameters that are specific to the type of USB Device are not checked. Parameters 
 * that describe how the user sets up their Descriptor Tree for their specific device are also
 * not checked.
 * 
 * @param Device_Descriptor pointer to the Device Descriptor to check.
 *
 * @return True if Device Descriptor is valid. False otherwise. 
 * 
 */
bool USB_Std_Device_Descriptor_Check(const USB_Std_Device_Descriptor_t * const Device_Descriptor)
{
    bool valid = true;

    if (!Device_Descriptor)
    {
        valid = false;
    }

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
    else if (   (Device_Descriptor->bLength != sizeof(USB_Std_Device_Descriptor_t)) || \
                (Device_Descriptor->bDescriptorType != DEVICE_DESCRIPTOR_TYPE) || \
                (!(LE16_RUNTIME(Device_Descriptor->bcdUSB) & 0x0F00)) || \
                (LE16_RUNTIME(Device_Descriptor->bcdUSB) > SOFTWARE_SUPPORTED_USB_VERSION) || \
                (Device_Descriptor->bMaxPacketSize0 != 8 &&  Device_Descriptor->bMaxPacketSize0 != 16 && \
                Device_Descriptor->bMaxPacketSize0 != 32 && Device_Descriptor->bMaxPacketSize0 != 64)   )
    {
        valid = false;
    }
    return valid;
}


/**
 * @brief Applies checks to parameters that apply to all Configuration Descriptors. These include:
 * bLength, bDescriptorType, bConfigurationValue, and bmAttributes.
 * 
 * @warning Parameters that are specific to the type of USB Device are not checked. Parameters 
 * that describe how the user sets up their Descriptor Tree for their specific device are also
 * not checked.
 * 
 * @param Configuration_Descriptor pointer to the Configuration Descriptor to check.
 *
 * @return True if Configuration Descriptor is valid. False otherwise.
 * 
 */
bool USB_Std_Configuration_Descriptor_Check(const USB_Std_Configuration_Descriptor_t * const Configuration_Descriptor)
{
    bool valid = true;

    if (!Configuration_Descriptor)
    {
        valid = false;
    }

    /**
     * bConfigurationValue starts at 1. Bits 0 to 4 of bmAttributes are set to 0 on reset and bit 7 must
     * always be set. See USB Spec v2.0, Chapter 9.6.3 - Configuration Descriptor.
     */
    else if (   (Configuration_Descriptor->bLength != sizeof(USB_Std_Configuration_Descriptor_t)) || \
                (Configuration_Descriptor->bDescriptorType != CONFIGURATION_DESCRIPTOR_TYPE) || \
                (Configuration_Descriptor->bConfigurationValue == 0) || \
                ((Configuration_Descriptor->bmAttributes & 0b10011111) != 0b10000000)   )
    {
        valid = false;
    }
    return valid;
}


/**
 * @brief Applies checks to parameters that apply to all Interface Descriptors. These include:
 * bLength and bDescriptorType.
 * 
 * @warning Parameters that are specific to the type of USB Device are not checked. Parameters 
 * that describe how the user sets up their Descriptor Tree for their specific device are also
 * not checked.
 * 
 * @param Interface_Descriptor pointer to Interface Descriptor to check.
 * 
 * @return True if Interface Descriptor is valid. False otherwise.
 * 
 */
bool USB_Std_Interface_Descriptor_Check(const USB_Std_Interface_Descriptor_t * const Interface_Descriptor)
{
    bool valid = true;

    if (!Interface_Descriptor)
    {
        valid = false;
    }

    else if (   (Interface_Descriptor->bLength != sizeof(USB_Std_Interface_Descriptor_t)) || \
                (Interface_Descriptor->bDescriptorType != INTERFACE_DESCRIPTOR_TYPE)   )
    {
        valid = false;
    }
    return valid;
}
