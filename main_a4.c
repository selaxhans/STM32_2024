/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
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
*/

 void  main()
  {
  int uart_init();

/* initiering av portarför output LED gul + röd samt
input från trycknappar; enl anvisningar skall aktiv hög resp låg användas blandat.
pga fel i de två tillgängliga stm 32 chipen har andra portnummer för input använts.
ett externtnt pullupp motstånd används föt PA10. inbyggd saknar funktion ?
button märkt 0 aktiverar röd led button 1 gul. samtidig aktivering av båda->
båda LED aktiverade omväxlande.
Detta är LAB A2. knappar scannas ( ej avbrottshantering) och blinkningar genom 
vänteloopar */

   RCC->IOPENR|=RCC_IOPENR_GPIOAEN;
   //input
  GPIOA->MODER=(GPIOA->MODER&~(GPIO_MODER_MODE0))|(GPIO_MODER_MODE1_0);
  //input
  GPIOA->MODER=(GPIOA->MODER&~(GPIO_MODER_MODE10))|(GPIO_MODER_MODE10_0);
  //PA09 INPUT pull upp
  // GPIOA->PUPDR=(GPIOA->PUPDR|(GPIO_PUPDR_PUPD0_1));
   // printf("PULLUP.10.. %d!\n", GPIOA->PUPDR);
  //pa10 pull down
    GPIOA->PUPDR=(GPIOA->PUPDR|(GPIO_PUPDR_PUPD10_0));
    GPIOA->PUPDR=(GPIOA->PUPDR|(GPIO_PUPDR_PUPD1_1));
//+++++++++++++++++++++++++;
// printf("PULLUP 10+9... %d!\n", GPIOA->PUPDR);

  //Enable peripheral clock GPIOA,GPIOB
   RCC->IOPENR|=RCC_IOPENR_GPIOBEN;
   RCC->IOPENR|=RCC_IOPENR_GPIOAEN;
    //General purpose output mode for LED, PB12 (pin25)
   GPIOB->MODER=(GPIOB->MODER&~(GPIO_MODER_MODE12))|(GPIO_MODER_MODE12_0);
   GPIOA->MODER=(GPIOA->MODER&~(GPIO_MODER_MODE8))|(GPIO_MODER_MODE8_0);
   GPIOA->BSRR=GPIO_BSRR_BS_8;

  uart_init();
 
  void run();


  

  run();
  exit(0);
}


void run()
{
  int i;
  uint32_t status;
  void led0_onoff(int);
  void led1_onoff(int);
  USART2->CR1 = 0x0004603; 
  status = USART2->ISR;
  int uart_send_ack();
  int uart_send_nack();
  int uartrx();
  int goon= 0x01;

  while (goon==0x01)
  {
  if ((status & 0x00000020)!= 0); //RXNE =1 data aviabel
  i = uartrx();
  if (i== 0x01)
  {
  led0_onoff(0);
  led1_onoff(1);
  uart_send_ack();
  }
   if (i== 0x00)
  {
  led0_onoff(1);
  led1_onoff(0);
  uart_send_ack();
  }
  else if ((i !=0x00)|(i !=0x01))
  uart_send_nack();
 } 
}




// gul led cycle

void led0_onoff(int) //yellow led
{
  int wait(int sek);
//  int lwait(int msek1);

  GPIOA->BSRR=GPIO_BSRR_BR_8; //yellow
  wait(1);
  GPIOA->BSRR=GPIO_BSRR_BS_8;
  wait(1);
  return;
 }


void led1_onoff(int)//red led 
{ 
  int wait(int sek);
  //int lwait(int msek1);

  GPIOB->BSRR=GPIO_BSRR_BS_12;
  wait(1);
  GPIOB->BSRR=GPIO_BSRR_BR_12;
  wait(1);
  return;
}
// båda lysdioderna
void led01_onoff()   //red led
{ 
  int wait(int sek);
  //int lwait(int msek1);
  GPIOA->BSRR=GPIO_BSRR_BS_8; //yellow
  GPIOB->BSRR=GPIO_BSRR_BS_12;
  wait(1);
  GPIOA->BSRR=GPIO_BSRR_BR_8; //yellow
  GPIOB->BSRR=GPIO_BSRR_BR_12;//RED
  wait(1);
  return;
}


int wait(int sek)
{
  int i;
  int result = 0;
  int lwait(int msek1);
  uint32_t i32 = 0;
 
  for (i =0;i32<0x001110; i32++)
  {
     result= lwait(5);
  }
 return 0;
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
    res=a/b;
    res=a/b;
    res=a/b;
    }
return 1;
  }



int uart_init()
{
uint32_t modA =GPIOA->MODER;
uint32_t status=0;
uint32_t  pupdr = GPIOA->PUPDR;
//GPIOA->MODER = (modA| 0xFFFFFFCFC);   //port  PA2 Alternatefunction
GPIOA->MODER= modA;
GPIOA->AFR[0] =  0x00044400;
USART_GTPR_GT_Msk;
USART2->BRR = 160000/96;   //tesst1 9.600 16 oversampling
USART2->CR1 = 0x0004600;   //not enabled yet
USART2->CR2 = 0x0004600;   //not enabled yet
USART2->CR3 = 0x0004600;   //not enabled yet
USART2->CR1 = 0x0004603;   //not enabled yet
status =USART2->ISR; // bit 5 RXNE data aviabel
return 0;
}


int uartrx()
{
uint8_t rxdata=0;
int uart_send_ack();
int uart_send_nack();

rxdata =USART2->RDR;
if  (rxdata == 0x47);
uart_send_ack();
return 0x47;
if  (rxdata == 0x52);
uart_send_ack();
return 0x52;
uart_send_nack();
return 0x15;

}





int uart_send_ack()
{
int ack = 0x06;
USART2->TDR =ack;
return 0;
}

int uart_send_nack()
{
int nack = 0x15;
USART2->TDR=nack;
return 0;

}


int uart_send_string()
{

return 0;
}


/*************************** End of file ****************************/
