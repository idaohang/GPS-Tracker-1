/**
 * imindude@gmail.com
 * tab-width:2; space only;
 * This is free software; you can redistribute it and/or modify it without any restrictions
 */

#include "inthandler.h"
#include "stm32f10x_usart.h"
#include "dev.h"

/**
 * INTERRUPT HANDLER - USART
 */

//void USART1_IRQHandler(void)
//{
//  int n;
//
//  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
//    n = USART_ReceiveData(USART1);
//  }
//}

void USART2_IRQHandler(void)
{
  struct Usart  *usart = get_dev()->gps->usart;
  int n;

  if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET) {
    n = USART_ReceiveData(USART2);

    usart->PushChar(usart, (char)n);
  }
}

//void USART3_IRQHandler(void)
//{
//  int n;
//
//  if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET) {
//    n = USART_ReceiveData(USART3);
//  }
//}
