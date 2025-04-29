#ifndef _XINPUTPAD_H_
#define _XINPUTPAD_H_

#include <stdint.h>
#include "tusb.h"
#include "device/usbd_pvt.h"

#include "descriptor_xinput.h"

#define GAMEPAD_JOYSTICK_MID 0
#define XINPUT_ENDPOINT_SIZE 20

typedef struct __attribute((packed, aligned(1)))
{
	uint8_t report_id;
	uint8_t report_size;

	uint8_t buttons1;
	uint8_t buttons2;
	uint8_t lt;
	uint8_t rt;
	int16_t lx;
	int16_t ly;
	int16_t rx;
	int16_t ry;
	uint8_t _reserved[6];
} XInputReport;

#ifdef __cplusplus
extern "C"
{
#endif

	void sendReportData(void *report);

#ifdef __cplusplus
}
#endif

#endif