/** @file usb.h
*
* @brief USB functionality for keyboard.
*
* Author: Ian Ress
*
*/

#ifndef USB_H
#define USB_H

#define CONFIG_ENDPOINT_DIR_IN                  0x01
#define CONFIG_ENDPOINT_DIR_OUT                 0x00

#define ENDPOINT_TYPE_CONTROL                   0x00
#define ENDPOINT_TYPE_ISOCHRONOUS               0x40
#define ENDPOINT_TYPE_BULK                      0x80
#define ENDPOINT_TYPE_INTERRUPT                 0xC0

#endif /* USB_H */
