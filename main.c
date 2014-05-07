/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include "stm32f10x.h"
#include "sysinit.h"
#include "dev.h"

/**
 * STATIC FUNCTION
 */

static int event_loop()
{
  struct DevGps *gps = get_dev()->gps;
  int len;

  while (1) {
    if ((len = gps->GetData(gps)) > 0) {
      gps->Parser(gps);
    }
  }

  return 0;
}

/**
 * ENTRY POINT
 */

int main()
{
  SystemInit();

  sys_init();

  return event_loop();
}
