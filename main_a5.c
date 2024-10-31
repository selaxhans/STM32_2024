/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main301.c rev 110A USART2 checked inits2024.10-29
Purpose : LAB A5 Clock out
*/

#include <stdio.h>
#include <stdlib.h>
#include "stm32l053xx.h"


/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
   transmitt + rewcieve
*/
int main(void) {
  int rev=0x110A;
  int rxtx =1;// tx ==1  rx==2;
/*
SET CLK TO HSI16 as USART baudrate is used and req a stabel clk source
select HSI16 as clock sorce as a exampel.
*/
#define RCC_CR_HSI16RDYF 0x00000004
  uint32_t check;
  RCC->CR |=RCC_CR_HSION;// P 187
  while (!(RCC->CR & RCC_CR_HSI16RDYF));// PAGE 187
  int goon = 1;


  void uart2out(int tkn);
  void wait(int sek);
 
  
  //port config clks
  // configuration for USART2 application
  // moified for Clock _Out measure
 // RCC->APB1ENR|=RCC_APB1ENR_TIM2EN; //checked 209
  RCC->APB1ENR|=RCC_APB1ENR_USART2EN;//checked P209
  check = RCC->CR;
  RCC->IOPENR|=RCC_IOPENR_IOPAEN;//checked P 204
  check = RCC->APB1ENR;
  USART2->BRR = 0xda;// BAURATE UART page 777  RM 0367  USART2->CR2 |= USART_CR2_CLKEN;//,
  // select clock distribution..

  RCC->CR = (RCC->CR)&(0xffffffef);
  check = RCC->CR;
  // initiate GPIOA for usart2
  GPIOA->MODER|=GPIO_MODER_MODE2_1;  //PAGE246  PA2 ALTERNATE
  GPIOA->MODER&=~GPIO_MODER_MODE2_0;
  GPIOA->MODER|=GPIO_MODER_MODE3_1; //PAGE246  PA3 ALTERNATE
  GPIOA->MODER&=~GPIO_MODER_MODE3_0;
  GPIOA->MODER|=GPIO_MODER_MODE4_1; //PAGE246  PA4 ALTERNATECLK PIN
  GPIOA->MODER&=~GPIO_MODER_MODE4_0;
  // enabel pin #2w9 == PA8 on package LQFP 28 reak out board
  GPIOA->MODER=(GPIOA->MODER&~(GPIO_MODER_MODE8))|(GPIO_MODER_MODE8_0);//PAGE251  PA8 As OUTPUT
  check = GPIOA->MODER; // check to verify bitmap...
  // naming convention manual and #defines differs high_ low replaced by array [index] may differ or alternate endian setting.
  // alternate func 4. PA2,3,4
  #define AF04 0x04
  GPIOA->AFR[0]|=(AF04<<8);// AF CHECKED USART2 TX,RX,CLK
  GPIOA->AFR[0]|=(AF04<<12);
  GPIOA->AFR[0]|=(AF04<<16);
  check = GPIOA->AFR[0];
  check = GPIOA->AFR[1];
  //order??
  // with this chip, markt with blank blue label settings for 9600 baud
  USART2->BRR = 0xda;
  check = USART2->BRR;
  // some common options..
  USART2->CR2 |= USART_CR2_CLKEN;// enabel tx clock output CR2  page 809  
  //USART2->CR2 |= USART_CR2_ABREN // AUTO baudrate not in use page 809
  //USART2->CR3 |= USART_CR3_OVRDIS; // disregard overrun CR3 page 813
  //USART2->CR2 |= USART_CR2_MSBFIRST;//bitorder reversed CR2 page 812 bit order
  USART2->CR1 = USART_CR1_TE|USART_CR1_RE|USART_CR1_RXNEIE ;// TX RX enabel CR1 page 806
//  USART2->CR1 |=USART_CR1_RXNEIE;
  USART2->CR1 |= USART_CR1_UE;//enabel usart| CR1 p 806
  check =USART2->CR1;//debug check result
  check =USART2->CR2;//debug check result
  
  printf("CONNECT SCOPE TO PIN #29 LQFP48, Package,read freq output and multiplay by d9169\n");

  while(1)
    { 
     GPIOA->BSRR=GPIO_BSRR_BS_8; // MARKER FOR TRIGG
     GPIOA->BSRR=GPIO_BSRR_BR_8; // MARKER FOR TRIGG
    }

 
}



/*************************** End of file ****************************/
