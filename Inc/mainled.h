#ifndef __MAINLED_H
#define __MAINLED_H
#include "main.h"

#define LEVEL_DEFAULT   14 
#define LEVEL_MAX       20
#define LEVEL_MIN       8
#define LEVEL_ZERO      0
#define LEVEL_STEP      6
#define LEVEL_PWM_STEP     1
#define LEVEL_PWM_MAX      100


void mainSingleLed_Test(void);

void mainTurnOff_TheSecondLedB(void);
void mainTurnOff_TheFirstLedA(void);

void mainTheFirstGroup_SingleLEDA(void);
void mainTheSecondGroup_SingleLEDB(void);
void mainFanControl(uint8_t fanval);

void LedOnOff(uint8_t ledNum,uint8_t onOff);

void changeBrightness(uint8_t dir);



typedef struct _mainled_
{
  uint8_t led_by_a;
  uint8_t led_by_b;
  uint8_t pwmDutyCycle_ch12;
  uint8_t pwmDutyCycle_ch22;
 
    
    
}mainled_t;

extern  mainled_t mainled;

void LedOnOff(uint8_t ledNum,uint8_t onOff);



#endif 

