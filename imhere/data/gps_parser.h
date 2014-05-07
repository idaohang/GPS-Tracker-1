/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#ifndef GPS_PARSER_H__
#define GPS_PARSER_H__

#include "global.h"

/**
 * DEFINITION
 */

#define MSG_GPGGA   "$GPGGA"
#define MSG_GPGSA   "$GPGSA"
#define MSG_GPGSV   "$GPGSV"
#define MSG_GPRMC   "$GPRMC"
#define MSG_GPVTG   "$GPVTG"

/**
 * Global Positioning System Fix Data. Time, Position and fix related data for a GPS receiver
 */

struct GPgga {
  uint32_t  utc_time;         // hhmmss.sss
  uint32_t  latitude;         // ddmm.mmmm / x10000
  uint32_t  longitude;        // ddmm.mmmm / x10000

  uint32_t  is_north    : 1;  // 1[north], 0[south]
  uint32_t  is_east     : 1;  // 1[east], 0[west]
  uint32_t  pos_fix     : 2;  // 0[not available], 1[GPS fix], 2[DGPS fix]
  uint32_t  used_sat    : 8;  // 0~14
  uint32_t  altitude    :16;  // meter / x10
};

/**
 * GPS DOPand active satellites
 */

//struct GPgsa {
//
//};

/**
 * Satellites in view
 */

//struct GPgsv {
//
//};

/**
 * Recommended Minimum Navigation Information
 */

struct GPrmc {
  uint32_t  utc_time;         // hhmmss.sss
  uint32_t  latitude;         // ddmm.mmmm / x10000
  uint32_t  longitude;        // ddmm.mmmm / x10000

  uint32_t  status      : 1;  // 1[valid], 0[not valid]
  uint32_t  is_north    : 1;  // 1[north], 0[south]
  uint32_t  is_east     : 1;  // 1[east], 0[west]

  uint16_t  speed;            // knot / x100
  uint16_t  course;           // degree / x100
  uint32_t  date;             // ddmmyy
};

/**
 * Track Made Good and Ground Speed
 */

//struct GPvtg {
//
//};

/**
 * PROTOTYPE
 */

extern int  gga_parser(char *msg, struct GPgga *gga);
extern int  rmc_parser(char *msg, struct GPrmc *rmc);

#endif  /* GPS_PARSER_H__ */
