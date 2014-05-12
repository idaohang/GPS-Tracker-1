/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#ifndef GPS_H__
#define GPS_H__

#include "global.h"
#include "usart.h"

enum { GPS_RX_BUF_SIZE = 128 };

struct DevGps {
  char  rx_buffer[GPS_RX_BUF_SIZE];
  int   rx_len;
  struct Usart  *usart;

  uint32_t  date;       // yymmdd
  uint32_t  time;       // hhmmss
  uint16_t  speed;      // Km / x100
  uint16_t  course;     // degree / x100
  int32_t   latitude;   // ddmm.mmmm / x10000 / MSB 1[north], 0[south]
  int32_t   longitude;  // ddmm.mmmm / x10000 / MSB 1[east], 0[west]

  uint8_t   fixed;      // 1[GPS fixed], 0[not fixed]
  uint8_t   used_sat;   // fixed satellite

  int (*UpdateData)(struct DevGps *gps);
  int (*ProcessData)(struct DevGps *gps);
};

extern struct DevGps* gps_ready();
extern void gps_done(struct DevGps *gps);

#endif  /* GPS_H__ */
