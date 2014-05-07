/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include "usart.h"

/**
 * STATIC FUNCTION
 */

static int set_next_write_buffer(struct Usart *usart)
{
  usart->rx_wbuf_id++;
  if (usart->rx_wbuf_id == USART_RX_BUF_N) {
    usart->rx_wbuf_id = 0;
  }

  usart->rx_done[usart->rx_wbuf_id] = 0;

  return 0;
}

static int set_next_read_buffer(struct Usart *usart)
{
  int n;

  for (n = 0; n < USART_RX_BUF_N; n++) {
    usart->rx_rbuf_id++;
    if (usart->rx_rbuf_id == USART_RX_BUF_N) {
      usart->rx_rbuf_id = 0;
    }

    if (usart->rx_done[usart->rx_rbuf_id])
      break;
  }

  if (n == USART_RX_BUF_N) {
    usart->rx_rbuf_id = usart->rx_wbuf_id;
  }

  return 0;
}

static int check_term_char(struct Usart *usart, char c)
{
  int n;

  for (n = 0; n < usart->rx_term_len; n++) {
    if (c == usart->rx_term[n])
      return 1;
  }

  return 0;
}

static void push_char(struct Usart *usart, char c)
{
  if (usart->rx_pos == USART_RX_BUF_SIZE) {
    // buffer overflow
    printlog("\"%s\" Rx buffer overflow\r\n", usart->name);

    usart->rx_pos = 0;
  }

  usart->rx_buffers[usart->rx_wbuf_id][usart->rx_pos] = c;

  if (check_term_char(usart, c))
    usart->rx_term_check++;

  if (usart->rx_term_check == usart->rx_term_len) {
    usart->rx_done[usart->rx_wbuf_id] = 1;  // 현재 Rx버퍼는 읽기 준비
    set_next_write_buffer(usart);           // 다음 Rx버퍼로 이동

    if (usart->rx_rbuf_id == usart->rx_wbuf_id)
      set_next_read_buffer(usart);

    usart->rx_pos = 0;
    usart->rx_term_check = 0;
  } else {
    usart->rx_pos++;
  }
}

static int pull_buffer(struct Usart *usart, char *buffer, int size)
{
  int   n, t;
  char  c;

  if (usart->rx_done[usart->rx_rbuf_id]) {
    for (n = 0, t = 0; n < size; n++) {
      c = usart->rx_buffers[usart->rx_rbuf_id][n];
      buffer[n] = c;

      if (check_term_char(usart, c)) {
        t++;
        if (t == usart->rx_term_len)
          break;
      }
    }

    if (n == size) {
      printlog("buffer is too small\r\n");
      n = 0;
    } else {
      n++;
    }

    usart->rx_done[usart->rx_rbuf_id] = 0;
//    set_next_read_buffer(usart);

    return n;
  }

  return 0;
}

/**
 * GLOBAL FUNCTION
 */

struct Usart* usart_ready(int port)
{
  struct Usart  *usart;
  char  name[4];

  usart = (struct Usart*)calloc(1, sizeof(struct Usart));

  switch (port) {
  case kUsartGps:
    strcpy(name, "GPS");
    break;
  case kUsartBluetooth:
    strcpy(name, "BT");
    break;
  default:
    free(usart);
    return NULL;
  }

  usart->port = port;
  strcpy(usart->name, name);

  usart->PushChar   = push_char;
  usart->PullBuffer = pull_buffer;

  return usart;
}

void usart_set_rxterm(struct Usart *usart, char *rx_term)
{
  char  *p = rx_term;
  int   n;

  if (strlen(rx_term) > USART_RX_TERM_LEN) {
    printlog("USART Rx TERM. is limited on \"%d\" char\r\n", USART_RX_TERM_LEN);
    return;
  }

  for (n = 0; *p != '\0'; n++, p++) {
    usart->rx_term[n] = *p;
  }

  usart->rx_term_len = n;
}

void usart_done(struct Usart *usart)
{
  free(usart);
}
