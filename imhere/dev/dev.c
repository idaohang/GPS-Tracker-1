/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include "dev.h"

/**
 * STATIC FUNCTION
 */


/**
 * GLOBAL FUNCTION
 */

struct DevList* get_dev()
{
  static struct DevList *dev = NULL;

  if (dev == NULL) {
    dev = (struct DevList*)calloc(1, sizeof(struct DevList));

    dev->gps = gps_ready();
  }

  return dev;
}
