/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#ifndef COMPASS_H__
#define COMPASS_H__

#include "global.h"
#include "i2c.h"

#define REG_CONFIG_A     0
#define REG_CONFIG_B     1
#define REG_MODE         2
#define REG_DATA_X_H     3
#define REG_DATA_X_L     4
#define REG_DATA_Y_H     5
#define REG_DATA_Y_L     6
#define REG_DATA_Z_H     7
#define REG_DATA_Z_L     8
#define REG_STATUS       9
#define REG_ID_A        10
#define REG_ID_B        11
#define REG_ID_C        12

struct DevCompass {
  struct I2c  *i2c;

  uint8_t   config_A;
  uint8_t   config_B;
  uint8_t   mode;
  uint16_t  data_X;
  uint16_t  data_Y;
  uint16_t  data_Z;
  uint8_t   status;

  int (*UpdateData)(struct DevCompass *gps);
  int (*ProcessData)(struct DevCompass *gps);
};

extern struct DevCompass* compass_ready();
extern void compass_done(struct DevCompass *compass);

#endif  /* COMPASS_H__ */
