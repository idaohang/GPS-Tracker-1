/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include "gps.h"
#include "gps_parser.h"

/**
 * STATIC FUNCTION
 */

static int parser_gga(struct DevGps *gps)
{
  struct GPgga  gga;

  memset(&gga, 0, sizeof(struct GPgga));
  gga_parser(gps->rx_buffer, &gga);

  return 0;
}

static int parser_gsa(struct DevGps *gps)
{
  return 0;
}

static int parser_gsv(struct DevGps *gps)
{
  return 0;
}

static int parser_rmc(struct DevGps *gps)
{
  struct GPrmc  rmc;

  memset(&rmc, 0, sizeof(struct GPrmc));
  rmc_parser(gps->rx_buffer, &rmc);

  return 0;
}

static int parser_vtg(struct DevGps *gps)
{
  return 0;
}

static int parser_vender(struct DevGps *gps)
{
  return 0;
}

static int update_data(struct DevGps *gps)
{
  memset(gps->rx_buffer, 0, GPS_RX_BUF_SIZE);
  gps->rx_len = gps->usart->PullBuffer(gps->usart, gps->rx_buffer, GPS_RX_BUF_SIZE);

  return gps->rx_len;
}

static int process_data(struct DevGps *gps)
{
  printlog("%s", gps->rx_buffer);

  if (strncasecmp(MSG_GPGGA, gps->rx_buffer, strlen(MSG_GPGGA)) == 0)
    parser_gga(gps);
  else if (strncasecmp(MSG_GPGSA, gps->rx_buffer, strlen(MSG_GPGSA)) == 0)
    parser_gsa(gps);
  else if (strncasecmp(MSG_GPGSV, gps->rx_buffer, strlen(MSG_GPGSV)) == 0)
    parser_gsv(gps);
  else if (strncasecmp(MSG_GPRMC, gps->rx_buffer, strlen(MSG_GPRMC)) == 0)
    parser_rmc(gps);
  else if (strncasecmp(MSG_GPVTG, gps->rx_buffer, strlen(MSG_GPVTG)) == 0)
    parser_vtg(gps);
  else
    parser_vender(gps);

//  uint32_t  date;       // yymmdd
//  uint32_t  time;       // hhmmss
//  uint16_t  speed;      // Km / x100
//  uint16_t  course;     // degree / x100
//  int32_t   latitude;   // ddmm.mmmm / x10000 / MSB 1[north], 0[south]
//  int32_t   longitude;  // ddmm.mmmm / x10000 / MSB 1[east], 0[west]
//
//  uint8_t   fixed;      // 1[GPS fixed], 0[not fixed]
//  uint8_t   used_sat;   // fixed satellite

  return 0;
}

/**
 * GLOBAL FUNCTION
 */

struct DevGps* gps_ready()
{
  struct DevGps *gps;

  gps = (struct DevGps*)calloc(1, sizeof(struct DevGps));

  gps->usart = usart_ready(kUsartGps);
  usart_set_rxterm(gps->usart, "\r\n");

  gps->UpdateData  = update_data;
  gps->ProcessData = process_data;

  return gps;
}

void gps_done(struct DevGps *gps)
{
  free(gps);
}
