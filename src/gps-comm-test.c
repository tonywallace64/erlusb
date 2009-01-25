#include <libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
  libusb_context *ctx;
  libusb_init(&ctx);
  libusb_set_debug(ctx, 3);
  libusb_device_handle *dev_handle =
    libusb_open_device_with_vid_pid(NULL,
				    0x091e /* Garmin */,
				    0003 /* misc devices */);
  assert(dev_handle != NULL);
  int claim = libusb_claim_interface(dev_handle, 0);
  assert(claim >= 0);
  printf("ctx=%p dev_hdl=%p claim=%d\n",
	 (void *)ctx, (void *)dev_handle, claim);
  int release = libusb_release_interface(dev_handle, 0);
  assert(release >= 0);
  printf("release=%d\n", release);
  libusb_close(dev_handle);
  libusb_exit(ctx);
}