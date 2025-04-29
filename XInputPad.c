#include "XInputPad.h"

static inline uint32_t board_millis(void)
{
    return to_ms_since_boot(get_absolute_time());
}

uint8_t endpoint_in = 0;
uint8_t endpoint_out = 0;

void sendReportData(void *report)
{
    // Poll every 1ms
    const uint32_t interval_ms = 1;
    static uint32_t start_ms = 0;

    if (board_millis() - start_ms < interval_ms)
        return; // not enough time
    start_ms += interval_ms;

    // Remote wakeup
    if (tud_suspended())
    {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }

    if ((tud_ready()) && ((endpoint_in != 0)) && (!usbd_edpt_busy(0, endpoint_in)))
    {
        usbd_edpt_claim(0, endpoint_in);
        usbd_edpt_xfer(0, endpoint_in, (uint8_t *)report, XINPUT_ENDPOINT_SIZE);
        usbd_edpt_release(0, endpoint_in);
    }
}

static void xinput_init(void)
{
}

static void xinput_reset(uint8_t __unused rhport)
{
}

static uint16_t xinput_open(uint8_t __unused rhport, tusb_desc_interface_t const *itf_desc, uint16_t max_len)
{
    //+16 is for the unknown descriptor
    uint16_t const drv_len = sizeof(tusb_desc_interface_t) + itf_desc->bNumEndpoints * sizeof(tusb_desc_endpoint_t) + 16;
    TU_VERIFY(max_len >= drv_len, 0);

    uint8_t const *p_desc = tu_desc_next(itf_desc);
    uint8_t found_endpoints = 0;
    while ((found_endpoints < itf_desc->bNumEndpoints) && (drv_len <= max_len))
    {
        tusb_desc_endpoint_t const *desc_ep = (tusb_desc_endpoint_t const *)p_desc;
        if (TUSB_DESC_ENDPOINT == tu_desc_type(desc_ep))
        {
            TU_ASSERT(usbd_edpt_open(rhport, desc_ep));

            if (tu_edpt_dir(desc_ep->bEndpointAddress) == TUSB_DIR_IN)
            {
                endpoint_in = desc_ep->bEndpointAddress;
            }
            else
            {
                endpoint_out = desc_ep->bEndpointAddress;
            }
            found_endpoints += 1;
        }
        p_desc = tu_desc_next(p_desc);
    }
    return drv_len;
}

static bool xinput_device_control_request(uint8_t __unused rhport, uint8_t __unused stage, tusb_control_request_t __unused const *request)
{
    return true;
}

static bool xinput_control_complete_cb(uint8_t __unused rhport, tusb_control_request_t __unused const *request)
{
    return true;
}
// callback after xfer_transfer
static bool xinput_xfer_cb(uint8_t __unused rhport, uint8_t __unused ep_addr, xfer_result_t __unused result, uint32_t __unused xferred_bytes)
{
    return true;
}

static usbd_class_driver_t const xinput_driver = {
#if CFG_TUSB_DEBUG >= 2
    .name = "XINPUT",
#endif
    .init = xinput_init,
    .reset = xinput_reset,
    .open = xinput_open,
    .control_xfer_cb = xinput_device_control_request,
    .xfer_cb = xinput_xfer_cb,
    .sof = NULL};

// Implement callback to add our custom driver
usbd_class_driver_t const *usbd_app_driver_get_cb(uint8_t *driver_count)
{
    *driver_count = 1;
    return &xinput_driver;
}
