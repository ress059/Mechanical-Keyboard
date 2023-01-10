/** @file usb_requests.h
*
* @brief At the start of every control transfer the host sends a request to the device.
* A collection of data types specific for USB requests are declared here. Follows USB 2.0
*
* Author: Ian Ress
*
*/

#ifndef USB_REQUESTS_H
#define USB_REQUESTS_H

#include <stdint.h>

#include "gcc_attributes.h"

typedef struct
{
    uint8_t  bmRequestType;     /*  Bitfield.
                                    Bit 7 = Transfer Direction:
                                        0 = Host to Device
                                        1 = Device to Host
                                    
                                    Bits 5 and 6 = Request Type:
                                        00 = Standard
                                        01 = Class
                                        10 = Vendor
                                        11 = Reserved

                                    Bits 0 to 4 = Recipient:
                                        00 = Device
                                        01 = Interface
                                        10 = Endpoint
                                        11 = Other
                                        All other values = Reserved */
                                        
    uint8_t  bRequest;          /* Request command code. E.g. SET_ADDRESS(), GET_DESCRIPTOR(), etc. See spec. */
    uint16_t wValue;            /* wValue parameter of the request (host passing parameter with request). */
    uint16_t wIndex;            /* wIndex parameter of the request (host passing parameter with request). */
    uint16_t wLength;           /* Number of bytes to transfer if there's a data phase. */
} GCCATTRIBUTE_PACKED USB_Request_Header_t;

#endif /* USB_REQUESTS_H */