/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include "i2c.h"

#define I2C_WA(a)   (a & 0xFE)
#define I2C_RA(a)   (a | 0x01)

/**
 * STATIC FUNCTION
 */

static int read_data(struct I2c *i2c, uint8_t sub_addr, uint8_t *buffer, int size)
{
  /* While the bus is busy */
  while(I2C_GetFlagStatus(i2c->i2c, I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(i2c->i2c, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(i2c->i2c, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send DEV address for write */
  I2C_Send7bitAddress(i2c->i2c, I2C_WA(i2c->addr), I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(i2c->i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the DEV internal address to read from: MSB of the address first */
  I2C_SendData(i2c->i2c, sub_addr);

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(i2c->i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STRAT condition a second time */
  I2C_GenerateSTART(i2c->i2c, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(i2c->i2c, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send DEV address for read */
  I2C_Send7bitAddress(i2c->i2c, I2C_RA(i2c->addr), I2C_Direction_Receiver);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(i2c->i2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  /* While there is data to be read */
  while (size) {
      if (size == 1) {
          /* Disable Acknowledgement */
          I2C_AcknowledgeConfig(i2c->i2c, DISABLE);

          /* Send STOP Condition */
          I2C_GenerateSTOP(i2c->i2c, ENABLE);
      }

      /* Test on EV7 and clear it */
      if(I2C_CheckEvent(i2c->i2c, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
          /* Read a byte from the EEPROM */
          *buffer = I2C_ReceiveData(i2c->i2c);

          /* Point to the next location where the byte read will be saved */
          buffer++;

          /* Decrement the read bytes counter */
          size--;
      }
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(i2c->i2c, ENABLE);

  return 0;
}

/**
 * GLOBAL FUNCTION
 */

struct I2c* i2c_ready(int port, uint8_t addr)
{
  struct I2c  *i2c;
  I2C_TypeDef *get_i2c;
  char  name[I2C_PORT_NAME_LEN];

  switch (port) {
  case kI2cCompass:
    get_i2c = I2C1;
    strcpy(name, "CP");
    break;
  default:
    return NULL;
  }

  i2c = (struct I2c*)calloc(1, sizeof(struct I2c));

  i2c->port = port;
  i2c->i2c  = get_i2c;
  i2c->addr = addr;
  strcpy(i2c->name, name);

  i2c->ReadData = read_data;

  return i2c;
}
void i2c_done(struct I2c *i2c)
{
  free(i2c);
}
