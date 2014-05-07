/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include <ctype.h>
#include "gps_parser.h"

enum { TOKEN_MAX_LEN = 16 };

/**
 * STATIC FUNCTION
 */

static int get_next_token(char *msg, char *token)
{
  int n;

  for (n = 0; n < TOKEN_MAX_LEN; n++) {
    if (msg[n] == ',')
      break;

    token[n] = msg[n];
  }

  if (n == TOKEN_MAX_LEN) {
    printlog("buffer overflow\r\n");
    return 0;
  }

  return n;
}

/**
 * GLOBAL FUNCTION
 */

int gga_parser(char *msg, struct GPgga *gga)
{
  char  *p = msg, *q;
  char  token[TOKEN_MAX_LEN];
  int   len = strlen(MSG_GPGGA);
  uint32_t  n;

  if (strncasecmp(p, MSG_GPGGA, len) != 0) {
    printlog("not GPGGA message : %s\r\n", msg);
    return -1;
  }

  p += len + 1;   // skip ','

  /**
   * UTC time   hhmmss.sss
   */

  memset(token, 0, TOKEN_MAX_LEN);
  if ((len = get_next_token(p, token)) > 0) {
    gga->utc_time = strtoul(token, NULL, 10);
  }
  p += len + 1;   // skip ','

  /**
   * latitude ddmm.mmmm
   */

  memset(token, 0, TOKEN_MAX_LEN);
  if ((len = get_next_token(p, token)) > 0) {
    gga->latitude = strtoul(token, &q, 10);
    gga->latitude *= 10000;
    n = strtoul(q, NULL, 10);
    gga->latitude += n;
  }
  p += len + 1;   // skip ','

  /**
   * N/S indicator
   */

  memset(token, 0, TOKEN_MAX_LEN);
  if ((len = get_next_token(p, token)) > 0) {
    gga->is_north = (toupper(token[0]) == 'N') ? 1 : 0;
  }
  p += len + 1;   // skip ','

  /**
   * longitude ddmm.mmmm
   */

  memset(token, 0, TOKEN_MAX_LEN);
  if ((len = get_next_token(p, token)) > 0) {
    gga->longitude = strtoul(token, &q, 10);
    gga->longitude *= 10000;
    n = strtoul(q, NULL, 10);
    gga->longitude += n;
  }
  p += len + 1;   // skip ','

  /**
   * E/W indicator
   */

  memset(token, 0, TOKEN_MAX_LEN);
  if ((len = get_next_token(p, token)) > 0) {
    gga->is_east = (toupper(token[0]) == 'E') ? 1 : 0;
  }
  p += len + 1;   // skip ','

  /**
   * position fix indicator
   */

  memset(token, 0, TOKEN_MAX_LEN);
  if ((len = get_next_token(p, token)) > 0) {
    gga->pos_fix = strtoul(token, NULL, 10);
  }
  p += len + 1;   // skip ','

  /**
   * satellite used
   */

  memset(token, 0, TOKEN_MAX_LEN);
  if ((len = get_next_token(p, token)) > 0) {
    gga->used_sat = strtoul(token, NULL, 10);
  }
  p += len + 1;   // skip ','

  /**
   * skip HDOP
   */

  len = get_next_token(p, token);
  p += len + 1;   // skip ','

  /**
   * altitude
   */

  memset(token, 0, TOKEN_MAX_LEN);
  if ((len = get_next_token(p, token)) > 0) {
    gga->altitude = strtoul(token, &q, 10);
    gga->altitude *= 10;
    n = strtoul(q, NULL, 10);
    gga->altitude += n;
  }
  p += len + 1;   // skip ','

  /**
   * SKIP CHECKSUM !!!
   */

  return 0;
}

int rmc_parser(char *msg, struct GPrmc *rmc)
{
  return 0;
}
