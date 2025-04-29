#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tusb.h"
#include "XInputPad.h"

// Define button pins here
#define BUTTON_A_PIN 15

XInputReport XboxButtonData = {
    .report_id = 0,
    .report_size = XINPUT_ENDPOINT_SIZE,
    .buttons1 = 0,
    .buttons2 = 0,
    .lt = 0,
    .rt = 0,
    .lx = GAMEPAD_JOYSTICK_MID,
    .ly = GAMEPAD_JOYSTICK_MID,
    .rx = GAMEPAD_JOYSTICK_MID,
    .ry = GAMEPAD_JOYSTICK_MID,
    ._reserved = {},
};

void initPin(int pin)
{
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_IN);
  gpio_pull_up(pin);
}

uint8_t checkButtons1(bool bit1State)
{
  // Updates only the first bit of the buttons1 byte
  XboxButtonData.buttons1 = XboxButtonData.buttons1 | bit1State;
}

int main(void)
{
  stdio_init_all();
  tusb_init();

  // Must initialize all pins
  initPin(BUTTON_A_PIN);

  while (1)
  {
    bool state = gpio_get(BUTTON_A_PIN);

    checkButtons1(state);
    sendReportData(&XboxButtonData);
    tud_task();
  }
  return 0;
}
