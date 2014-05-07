/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#ifndef DEV_H__
#define DEV_H__

#include "global.h"
#include "gps.h"

struct DevList {
  struct DevGps *gps;
};

extern int  dev_init();
extern struct DevList*  get_dev();

#endif  /* DEV_H__ */
