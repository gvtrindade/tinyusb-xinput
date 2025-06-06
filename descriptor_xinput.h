#ifndef DESCRIPTOR_XINPUT
#define DESCRIPTOR_XINPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tusb.h"
#include "common/tusb_common.h"
#include "device/usbd.h"
#include "pico/stdlib.h"

static const uint8_t xinputDeviceDescriptor[] = {
    0x12,       // bLength
    0x01,       // bDescriptorType (Device)
    0x00, 0x02, // bcdUSB 2.00
    0xFF,       // bDeviceClass
    0xFF,       // bDeviceSubClass
    0xFF,       // bDeviceProtocol
    0x40,       // bMaxPacketSize0 64
    0x5E, 0x04, // idVendor 0x045E
    0x8E, 0x02, // idProduct 0x028E
    0x14, 0x01, // bcdDevice 2.14
    0x01,       // iManufacturer (String Index)
    0x02,       // iProduct (String Index)
    0x03,       // iSerialNumber (String Index)
    0x01,       // bNumConfigurations 1
};

static const uint8_t xinputConfigurationDescriptor[] = {
    // Configuration Descriptor:
    0x09,       // bLength
    0x02,       // bDescriptorType
    0x30, 0x00, // wTotalLength   (48 bytes)
    0x01,       // bNumInterfaces
    0x01,       // bConfigurationValue
    0x00,       // iConfiguration
    0x80,       // bmAttributes   (Bus-powered Device)
    0xFA,       // bMaxPower      (500 mA)

    // Interface Descriptor:
    0x09, // bLength
    0x04, // bDescriptorType
    0x00, // bInterfaceNumber
    0x00, // bAlternateSetting
    0x02, // bNumEndPoints
    0xFF, // bInterfaceClass      (Vendor specific)
    0x5D, // bInterfaceSubClass
    0x01, // bInterfaceProtocol
    0x00, // iInterface

    // Unknown Descriptor:
    0x10,
    0x21,
    0x10,
    0x01,
    0x01,
    0x24,
    0x81,
    0x14,
    0x03,
    0x00,
    0x03,
    0x13,
    0x02,
    0x00,
    0x03,
    0x00,

    // Endpoint Descriptor:
    0x07,       // bLength
    0x05,       // bDescriptorType
    0x81,       // bEndpointAddress  (IN endpoint 1)
    0x03,       // bmAttributes      (Transfer: Interrupt / Synch: None / Usage: Data)
    0x20, 0x00, // wMaxPacketSize    (1 x 32 bytes)
    0x04,       // bInterval         (4 frames)

    // Endpoint Descriptor:
    0x07,       // bLength
    0x05,       // bDescriptorType
    0x02,       // bEndpointAddress  (OUT endpoint 2)
    0x03,       // bmAttributes      (Transfer: Interrupt / Synch: None / Usage: Data)
    0x20, 0x00, // wMaxPacketSize    (1 x 32 bytes)
    0x08,       // bInterval         (8 frames)
};

// string descriptor table
static char const *string_desc_arr_xinput[] = {
    (const char[]){0x09, 0x04}, // 0: is supported language is English (0x0409)
    "GENERIC",                  // 1: Manufacturer
    "XINPUT CONTROLLER",        // 2: Product
    "1.0"                       // 3: Serials
};

#endif