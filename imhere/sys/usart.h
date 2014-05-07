/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#ifndef USART_H__
#define USART_H__

#include "global.h"

enum {
  kUsartGps,
  kUsartBluetooth,
};

enum { USART_RX_BUF_N = 2 };
enum { USART_RX_BUF_SIZE = 128 };
enum { USART_PORT_NAME_LEN = 4 };
enum { USART_RX_TERM_LEN = 4 };

struct Usart {
  int   port;
  char  name[USART_PORT_NAME_LEN];

  char  rx_buffers[USART_RX_BUF_N][USART_RX_BUF_SIZE];    // Rx ����(������)
  char  rx_done[USART_RX_BUF_N];
  char  rx_term[USART_RX_TERM_LEN];   // term char ��
  short rx_pos;           // ���� ���ۿ��� ������ ����� ����Ʈ ��ġ
  short rx_wbuf_id;       // ���� writing�ϴ� ���� id
  short rx_rbuf_id;       // pull buffer���� �о ���� id
  short rx_term_check;    // term char �� ��� match�Ǿ���
  short rx_term_len;      // term char ����

  void  (*PushChar)(struct Usart *usart, char c);
  int   (*PullBuffer)(struct Usart *usart, char *buffer, int size);
};

extern struct Usart*  usart_ready(int port);
extern void usart_set_rxterm(struct Usart *usart, char *rx_term);
extern void usart_done(struct Usart *usart);

#endif  /* USART_H__ */
