/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main301.c rev 110A USART2 checked inits2024.10-29
Purpose : Generic application start

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
SIDOHÄNVISNING TILL RM0367
*/
#define RCC_CR_HSI16RDYF 0x00000004
  uint32_t check;
  RCC->CR |=RCC_CR_HSION;// P 187
  while (!(RCC->CR & RCC_CR_HSI16RDYF));// PAGE 187
  int goon = 5;
  void uart2out(int tkn);
  void wait(int sek);
  void checkinput(void);
  
  //port config clks
 // RCC->APB1ENR|=RCC_APB1ENR_TIM2EN; //checked 209
  RCC->APB1ENR|=RCC_APB1ENR_USART2EN;//checked P209
  check = RCC->CR;
  RCC->IOPENR|=RCC_IOPENR_IOPAEN;//checked P 204
check = RCC->APB1ENR;
  USART2->BRR = 0xda;// BAURATE UART PAGA 777 16 mhZ KLOCKA 9600 BAUD TERMINALPROGRAMMET.
  USART2->CR2 |= USART_CR2_CLKEN;//

  RCC->CR = (RCC->CR)&(0xffffffef);
  check = RCC->CR;
  GPIOA->MODER|=GPIO_MODER_MODE2_1;  //PAGE246  PA2 ALTERNATE
  GPIOA->MODER&=~GPIO_MODER_MODE2_0;
  GPIOA->MODER|=GPIO_MODER_MODE3_1; //PAGE246  PA3 ALTERNATE
  GPIOA->MODER&=~GPIO_MODER_MODE3_0;
  GPIOA->MODER|=GPIO_MODER_MODE4_1; //PAGE246  PA4 ALTERNATECLK PIN
  GPIOA->MODER&=~GPIO_MODER_MODE4_0;
  GPIOA->MODER=(GPIOA->MODER&~(GPIO_MODER_MODE8))|(GPIO_MODER_MODE8_0);//PAGE251  PA8 AOUTPUT
  check = GPIOA->MODER;
  // alternate func 4. PA2,3,4
  #define AF04 0x04
  GPIOA->AFR[0]|=(AF04<<8);// AF CHECKED USART2 TX,RX,CLK
  GPIOA->AFR[0]|=(AF04<<12);
  GPIOA->AFR[0]|=(AF04<<16);
  check = GPIOA->AFR[0];
  check = GPIOA->AFR[1];
  //order??

  USART2->BRR = 0xda;
  check = USART2->BRR;
  
  USART2->CR2 |= USART_CR2_CLKEN;// enabel tx clock output CR2  page 809  
  //USART2->CR2 |= USART_CR2_ABREN // AUTO baudrate not in use page 809
  //USART2->CR3 |= USART_CR3_OVRDIS; // disregard overrun CR3 page 813
  //USART2->CR2 |= USART_CR2_MSBFIRST;//bitorder reversed CR2 page 812
  USART2->CR1 = USART_CR1_TE|USART_CR1_RE|USART_CR1_RXNEIE ;// TX RX enabel CR1 page 806
//  USART2->CR1 |=USART_CR1_RXNEIE;
  USART2->CR1 |= USART_CR1_UE;//enabel usart| CR1 p 806
  check =USART2->CR1;//debug check result
  check =USART2->CR2;//debug check result


  /* för att kolla klockfunktion och baudrate*/
 //'R' använder jag som test skall tända röd LED

  while (goon)
  {
  goon--;
  wait(1);
  uart2out(0x52);
  /*
  uart2out(0x41);
  uart2out(0x4F);
  uart2out(0x53);
  */
  }

 printf("output klart%d!\n", goon);

 printf("bevakr indata0%d!\n", goon);
 //för read testen använde jag terminal programmet från labmanualen
 //9.600 baud  8 databitar 1 stop bit ingen paritetscheck bit och en stop bit 
 //och ingen handskakning
 // jag har en fil med hundratals utf-8 'R' kommando sendfile
 // check för att läsa av 32-bitars styrkoder.
checkinput();
}


void checkinput(void)
 {
 uint8_t flag =1;
 uint8_t rxdata;
 int lwait(int msek1);
 void wait(int sek);
 int goon1 = 1;
 uint32_t check;
 uint32_t isr; 
   
     printf("count%d!\n",goon1);
      GPIOA->BSRR=GPIO_BSRR_BS_8; // MARKER FOR TRIGG
      lwait(1);
      GPIOA->BSRR=GPIO_BSRR_BR_8;
      rxdata = (USART2->RDR);
      printf("Indata%1d!\n",rxdata);
     // USART2->CR1 =0x0000060c;
      USART2->CR1 |=USART_CR1_UE;
while(flag)
  { 
	/*  kolla setup*/

   GPIOA->BSRR=GPIO_BSRR_BS_8; // MARKER FOR TRIGG visa på oschskop
   GPIOA->BSRR=GPIO_BSRR_BR_8; // MARKER FOR TRIGG
    check =USART2->CR1;
    check =USART2->CR2; 
    isr = USART2->ISR;
    rxdata = (USART2->RDR);
    flag--;
  }
//
//KÖR MOTTAGNINGSTEST
//ALDRIG FÅTT NÅGON DATA 
// EJ HELLER OVERRUN ELLER ANNAN FELINDIKATION
//

 while(1)
  { 
   isr = USART2->ISR;// ISR PAGE 820;
  //  lwait(1);
   // GPIOA->BSRR=GPIO_BSRR_BR_8;
    lwait(1);
   if((USART2->ISR & 0x00000020))
    {
    rxdata = (USART2->RDR);
   // printf("RxD %d!\n", rxdata);
    GPIOA->BSRR=GPIO_BSRR_BS_8; // MARKER FOR TRIGG
    lwait(1);
    GPIOA->BSRR=GPIO_BSRR_BR_8; // MARKER FOR TRIGG
    if (rxdata!= 0)
    printf("Indata %1d!\n",rxdata); 
   }
   }
 
}
  void uart2out(int tkn)
  {
  while(!(USART2->ISR & USART_ISR_TXE)){}

  USART2->TDR = (tkn & 0xFF);   //8 bitar

  return;
  }
 

void wait(int sek)
{
  int i;
  int result = 0;
  int lwait(int msek1);
  uint32_t i32 = 0;
 
  for (i =0;i32<0x00100; i32++)
  {
     result= lwait(5);
  }
 return;
} 

int lwait(int msek1)
 {
 int i;
 int a =100;
 int b= 33;
 int res =0;
 uint32_t i16 = 0;
 
    for (i =0;i16<0x00010; i16++);
    {
    res=a/b; // nop saknas men div tar rätt lång tgid passar här
    res=a/b; // EN SAK I SÄNDER - NÄR RX OK -> TICK
    res=a/b;
    res=a/b;
    }
return 1;
}
 

 


/*************************** End of file ****************************/
