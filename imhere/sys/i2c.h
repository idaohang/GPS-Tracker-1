/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#ifndef I2C_H__
#define I2C_H__

#include "global.h"
#include "stm32f10x_i2c.h"

enum {
  kI2cCompass,
};

enum { I2C_PORT_NAME_LEN = 4 };

struct I2c {
  int   port;
  char  name[I2C_PORT_NAME_LEN];

  I2C_TypeDef *i2c;
  uint8_t   addr;

  int   (*ReadData)(struct I2c *i2c, uint8_t sub_addr, uint8_t *buffer, int size);
};

extern struct I2c*  i2c_ready(int port, uint8_t addr);
extern void i2c_done(struct I2c *i2c);

#endif  /* I2C_H__ */
