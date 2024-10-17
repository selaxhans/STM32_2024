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


 
  void run();


  

  run();
  exit(0);
}


void run()
{
  int i;
  uint32_t status;
  uint32_t switch_sense();
 //
 // loop checking buttons; 
 //
  for (i=0; i < 10000000; i++)
  {
  status = switch_sense(i);
  }
return;
}
/* inpu sense varje blinkperiod*/
uint32_t switch_sense(int i)
{ 
int wait(int sek);    // blinkfrekvens justering ej kalibrerad
int lwait(int msek); // blinkfrekvens justering
void led0_onoff();
void led1_onoff();
void led01_onoff();
uint16_t resp;
uint16_t resp1;
uint16_t resp2;
uint16_t response = GPIOA->IDR;
uint16_t resp0=response&(0x01);

//check both buttons

resp2 = response & (0x0401);
resp2=resp2^(0x0001);

if (resp2 == 0x0401)
{
 led01_onoff();
 GPIOA->BSRR=GPIO_BSRR_BS_8;
 return 0;
 }

//check yellow button #1

resp0 = resp0 ^ (0x01);
if (resp0 !=0)
{
 led0_onoff();
 return 0;
 }
 
 //red led button #0

  {
resp1 = (response & (0x0400));
if (resp1 !=0)
{
 resp1 = 1;
 led1_onoff();
 return 0;
 }
}
 




// gul led cycle
}
void led0_onoff()
{
  int wait(int sek);
//  int lwait(int msek1);

  GPIOA->BSRR=GPIO_BSRR_BR_8; //yellow
  wait(1);
  GPIOA->BSRR=GPIO_BSRR_BS_8;
  wait(1);
  return;

 }


void led1_onoff()   //red led
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

int uart_init();
int uartrx();
int uarttx(int msg);
int uart_send_string();


int uart_init()
{


return 0;
}
int uartrx()
{


return 0;
}

int uarttx(int msg)
{
int ack = 0x06;
int nack =0x15;
}

int uart_send_string()
{

return 0;
}


/*************************** End of file ****************************/
