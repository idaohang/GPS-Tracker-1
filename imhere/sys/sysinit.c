/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include "sysinit.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

/**
 * STATIC FUNCTION
 */

static int init_nvic()
{
  NVIC_InitTypeDef  nvic_init;

  /* logger */

  nvic_init.NVIC_IRQChannel                   = USART1_IRQn;
  nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_init.NVIC_IRQChannelSubPriority        = 0;
  nvic_init.NVIC_IRQChannelCmd                = ENABLE;

  NVIC_Init(&nvic_init);

  /* gps */

  nvic_init.NVIC_IRQChannel                   = USART2_IRQn;
  nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_init.NVIC_IRQChannelSubPriority        = 0;
  nvic_init.NVIC_IRQChannelCmd                = ENABLE;

  NVIC_Init(&nvic_init);

  /* bluetooth */

  nvic_init.NVIC_IRQChannel                   = USART3_IRQn;
  nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_init.NVIC_IRQChannelSubPriority        = 0;
  nvic_init.NVIC_IRQChannelCmd                = ENABLE;

  NVIC_Init(&nvic_init);

  return 0;
}

static int init_gpio()
{
  GPIO_InitTypeDef  gpio_init;

  /* logger */

  gpio_init.GPIO_Pin   = GPIO_Pin_9;            // PA.09 as Tx
  gpio_init.GPIO_Mode  = GPIO_Mode_AF_PP;       // alternate function push-pull
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &gpio_init);

  gpio_init.GPIO_Pin   = GPIO_Pin_10;           // PA.10 as Rx
  gpio_init.GPIO_Mode  = GPIO_Mode_IN_FLOATING; // input floating

  GPIO_Init(GPIOA, &gpio_init);

  /* gps */

  gpio_init.GPIO_Pin   = GPIO_Pin_2;            // PA.02 as Tx
  gpio_init.GPIO_Mode  = GPIO_Mode_AF_PP;       // alternate function push-pull
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &gpio_init);

  gpio_init.GPIO_Pin   = GPIO_Pin_3;            // PA.03 as Rx
  gpio_init.GPIO_Mode  = GPIO_Mode_IN_FLOATING; // input floating

  GPIO_Init(GPIOA, &gpio_init);

  /* logger */

  gpio_init.GPIO_Pin   = GPIO_Pin_10;           // PB.10 as Tx
  gpio_init.GPIO_Mode  = GPIO_Mode_AF_PP;       // alternate function push-pull
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &gpio_init);

  gpio_init.GPIO_Pin   = GPIO_Pin_11;           // PB.11 as Rx
  gpio_init.GPIO_Mode  = GPIO_Mode_IN_FLOATING; // input floating

  GPIO_Init(GPIOB, &gpio_init);

  return 0;
}

static int init_usart()
{
  USART_InitTypeDef usart_init;

  /* logger */

  usart_init.USART_BaudRate            = 115200;
  usart_init.USART_WordLength          = USART_WordLength_8b;
  usart_init.USART_StopBits            = USART_StopBits_1;
  usart_init.USART_Parity              = USART_Parity_No;
  usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_init.USART_Mode                = USART_Mode_Tx;

  USART_Init(USART1, &usart_init);
  USART_Cmd(USART1, ENABLE);

  /* gps */

  usart_init.USART_BaudRate            = 9600;
  usart_init.USART_WordLength          = USART_WordLength_8b;
  usart_init.USART_StopBits            = USART_StopBits_1;
  usart_init.USART_Parity              = USART_Parity_No;
  usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_init.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART2, &usart_init);
  USART_Cmd(USART2, ENABLE);

  /* bluetooth */

  usart_init.USART_BaudRate            = 57600;
  usart_init.USART_WordLength          = USART_WordLength_8b;
  usart_init.USART_StopBits            = USART_StopBits_1;
  usart_init.USART_Parity              = USART_Parity_No;
  usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_init.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &usart_init);
  USART_Cmd(USART3, ENABLE);

  /* interrupt enable */

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

  return 0;
}

/**
 * GLOBAL FUNCTION
 */

int sys_init()
{
  /* clock */

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);   // logger
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB2Periph_GPIOA, ENABLE);   // gps
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB2Periph_GPIOB, ENABLE);   // bluetooth

  /* peripheral */

  init_nvic();
  init_gpio();
  init_usart();

  return 0;
}
