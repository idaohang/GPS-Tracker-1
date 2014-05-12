/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include "compass.h"

/**
 * STATIC FUNCTION
 */

static int read_id(struct I2c *i2c)
{
  uint8_t id_A, id_B, id_C;

  i2c->ReadData(i2c, REG_ID_A, &id_A, 1);
  i2c->ReadData(i2c, REG_ID_B, &id_B, 1);
  i2c->ReadData(i2c, REG_ID_C, &id_C, 1);

  printlog("%c%c%c\r\n", id_A, id_B, id_C);

  if ((id_A != 'H') || (id_B != '4') || (id_C != '3')) {
    printlog("HMC5883L is not found\r\n");
    return -1;
  }

  return 0;
}

static int update_data(struct DevCompass *compass)
{
//  struct I2c  *i2c = compass->i2c;


  return 0;
}

static int process_data(struct DevCompass *compass)
{
  return 0;
}

/**
 * GLOBAL FUNCTION
 */

struct DevCompass* compass_ready()
{
  struct DevCompass *compass;

  compass = (struct DevCompass*)calloc(1, sizeof(struct DevCompass));

  compass->i2c = i2c_ready(kI2cCompass, 0x1E);

  if (read_id(compass->i2c) != 0) {
    i2c_done(compass->i2c);
    return NULL;
  }

  compass->UpdateData  = update_data;
  compass->ProcessData = process_data;

  return compass;
}

void compass_done(struct DevCompass *compass)
{
  free(compass);
}
