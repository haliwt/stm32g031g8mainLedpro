#ifndef __MAINLED_H
#define __MAINLED_H
#include "main.h"




void mainSingleLed_Test(void);

void mainTurnOff_TheSecondLedB(void);
void mainTurnOff_TheFirstLedA(void);

void mainTheFirstGroup_SingleLEDA(void);
void mainTheSecondGroup_SingleLEDB(void);
void mainFanControl(uint8_t fanval);

typedef struct _mainled_
{
  uint8_t led_by_a;
  uint8_t led_by_b;
  uint8_t pwmDutyCycle_ch12;
  uint8_t pwmDutyCycle_ch22;
 
    
    
}mainled_t;

extern  mainled_t mainled;


#endif 

