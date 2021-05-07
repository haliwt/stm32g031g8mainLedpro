#include "mainled.h"
#include "usart.h"
#include "pwm.h"
#include "gpio.h"

mainled_t mainled;
static uint8_t lastOnLed = 0xff;
static uint8_t hasLedOn;
static uint8_t level_a;
static uint8_t level_b;


static void setLevel_PWMA(uint8_t level);
static void setLevel_PWMB(uint8_t level);


/*************************************************************************
 	*
	*Function Name: void LedOnOff(void)
	*Function : Turn On LEDAxx LED
	*Input Ref: receive UART of data
	*Output Ref:No
	*
******************************************************************************/
void LedOnOff(uint8_t ledNum,uint8_t onOff)
{
  // uint8_t temp;
   if((lastOnLed !=ledNum)||(onOff ==0)){

                //turn off all led 
              mainTurnOff_TheSecondLedB();
              mainTurnOff_TheFirstLedA();
			  mainled.led_by_a = 0;
			  mainled.led_by_b = 0;

   }
    
   if(onOff){

	   lastOnLed = ledNum;
	   hasLedOn =1;
	  
	  
	   switch(ledNum){
	   	
			case 7://PA2 [0] ---oled "Orange"-{7}
			    mainled.led_by_a = 1;
				mainTurnOff_TheSecondLedB();
                mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
				//1.turn on LEDA1 =1
			   HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_SET);
			   //2.EN on
			    setLevel_PWMA(level_a);
                //HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
                
                break;

            case 4://PA3--[1]----oled menu "Blue2" -{4}
				mainled.led_by_a = 1;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA2  
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
			    setLevel_PWMA(level_a);
				//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
                break;

            case 3: //PA4-[2] -----oled  menu "Blue1" -{3}
				mainled.led_by_a = 1;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA3
                HAL_GPIO_WritePin(LEDA3_GPIO_Port, LEDA3_Pin, GPIO_PIN_SET);
				//2. enable
			      setLevel_PWMA(level_a);
				// HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
			   
                break;

            case 1://PA5-[3]-----oled menu "UV365" {1}
				mainled.led_by_a = 1;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA4
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_SET);
			    //2 .EN
				
			      setLevel_PWMA(level_a);
			    //  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
                break;

            case 2: //PA6-[4]-----oled menu "Violet" {2}
				mainled.led_by_a = 1;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA5
                HAL_GPIO_WritePin(LEDA5_GPIO_Port, LEDA5_Pin, GPIO_PIN_SET);      //1.the first turn on LED
				 setLevel_PWMA(level_a);
			    // HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;  //2.the second turn on Enable
			    
                break;

            case 0://PA7[5]---"white" oled {0}
				mainled.led_by_a = 1;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA6
                HAL_GPIO_WritePin(LEDA6_GPIO_Port, LEDA6_Pin, GPIO_PIN_SET);
				setLevel_PWMA(level_a);
				//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ; //2.the second turn on Enable
			    
                break;

            case 6: //PB0-[6]----oled menu "Green"--{6}
				mainled.led_by_a = 1;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA7
                HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin, GPIO_PIN_SET);
				setLevel_PWMA(level_a);
				//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;//2.the second turn on Enable
			    
                break;

            case 5://PB1-[7]----oled "Cyan"--{5}
				mainled.led_by_a = 1;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA8
                HAL_GPIO_WritePin(LEDA8_GPIO_Port, LEDA8_Pin, GPIO_PIN_SET);
				setLevel_PWMA(level_a);
				//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;  //2.TIM2_CH2
			    
            break;
			
		   //LEDB -The second group 
		    case 9://PA11[8]-----olde "640"-{9}
				mainled.led_by_b = 1;
				mainTurnOff_TheFirstLedA();
				mainTurnOff_TheSecondLedB();
				HAL_Delay(20);
				//1.turn on LEDB1 =1
                HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin, GPIO_PIN_SET);
			     setLevel_PWMB(level_b);
				// HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
                break;

            case 0x0B://PA12[9] -----oled "740"--{11}
				mainled.led_by_b = 1;
				mainTurnOff_TheFirstLedA();
				mainTurnOff_TheSecondLedB();
				HAL_Delay(20);

				//turn on LEDB1
                HAL_GPIO_WritePin(LEDB2_GPIO_Port, LEDB2_Pin, GPIO_PIN_SET);
				setLevel_PWMB(level_b);
				// HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2); //TIM1_CH2
                break;

			case 0x0F: //PA15[0xa]----oled "930"--{15}
				// temp =0x0A;
				// HAL_UART_Transmit(&huart1,&temp,1,2);
				mainled.led_by_b = 1;
				mainTurnOff_TheFirstLedA();
		
				mainTurnOff_TheSecondLedB();
				HAL_Delay(20);
							  //turn on LEDB3=1
                HAL_GPIO_WritePin(LEDB3_GPIO_Port, LEDB3_Pin, GPIO_PIN_SET);
				 setLevel_PWMB(level_b);
				//HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
                break;

            case 0x0E: //[0X0B]----oled "840" {14}
				// temp =0x0B;
				// HAL_UART_Transmit(&huart1,&temp,1,2);
				mainled.led_by_b = 1;
				mainTurnOff_TheFirstLedA();
			
				mainTurnOff_TheSecondLedB();
				HAL_Delay(20);
				//turn on LEDB4=1
                HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin, GPIO_PIN_SET);
			    setLevel_PWMB(level_b);
                // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			break;

            case 0X0C: //[0x0C] ----oled "750"--{12}
				mainled.led_by_b = 1;
				// temp =0x0C;
				// HAL_UART_Transmit(&huart1,&temp,1,2);
				mainTurnOff_TheFirstLedA();
			
				mainTurnOff_TheSecondLedB();
				HAL_Delay(20);
				//turn on LEDB5=1
                HAL_GPIO_WritePin(LEDB5_GPIO_Port, LEDB5_Pin, GPIO_PIN_SET);
			     setLevel_PWMB(level_b);
               // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			break;

            case 0x0A://[0x0D]---oled "690"--{0xA}
			     mainled.led_by_b = 1;
                // HAL_GPIO_WritePin(LEDB6_GPIO_Port,LEDB6_Pin, GPIO_PIN_SET);
                break;

            case 8: // [0xe] -----oled "Red"-{8}
			    mainled.led_by_b = 1;
				// temp =0x0E;
				// HAL_UART_Transmit(&huart1,&temp,1,2);
				mainTurnOff_TheFirstLedA();
			
				mainTurnOff_TheSecondLedB();
				HAL_Delay(20);
				//turn on LEDB7 =1
                HAL_GPIO_WritePin(LEDB7_GPIO_Port, LEDB7_Pin, GPIO_PIN_SET);
				 setLevel_PWMB(level_b);
                // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			break;

            case 0X0D: //[0X0F]-----oled "770" --{13}
				// temp =0x0F;
				// HAL_UART_Transmit(&huart1,&temp,1,2);
				mainled.led_by_b = 1;
				mainTurnOff_TheFirstLedA();
				
				mainTurnOff_TheSecondLedB();
				HAL_Delay(20);
				//turn on LEDB8 =1
                HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_SET);
				 setLevel_PWMB(level_b);
               // HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
				break;
	   
           
	   }
	  
   }
}
/*************************************************************************
 	*
	*Function Name:static void FanControl(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void mainFanControl(uint8_t fanval)
{
    switch(fanval){
		   
			case 0:  
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
			
			case 1:
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_RESET);
			break;
			
			case 2:
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
			
			default :
					HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
		
	  }

}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheFirstLedA(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void mainTurnOff_TheFirstLedA(void)
{
     //turn off LEDA LED
	   HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_2) ; //HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);//TIM2_CH2
	   HAL_Delay(20);
	   HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin | LEDA2_Pin | LEDA3_Pin | LEDA4_Pin | LEDA5_Pin | LEDA6_Pin, GPIO_PIN_RESET);
       HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin | LEDA8_Pin, GPIO_PIN_RESET);

}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheSecondLedB(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void mainTurnOff_TheSecondLedB(void)
{
		 //turn off LEDB LED
		 HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);//TIM1_CH2 --PB3//HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
		 HAL_Delay(20);
		 HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin | LEDB2_Pin | LEDB3_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin | LEDB5_Pin | LEDB7_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_RESET);
	     mainled.pwmDutyCycle_ch12=0;

	     MX_TIM1_Init();
	 
	     
}
/*************************************************************************
 	*
	*Function Name:
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
//static uint8_t BCC_CHECK(void)
//{
//   uint8_t i;
//	 
//	 uint8_t tembyte =0xAA ^ aRxBuffer[2];
//	
//    for (i = 3; i <6; i++) {
//        tembyte = tembyte ^ aRxBuffer[i];
//    }
//    return tembyte;

//}
/*************************************************************************
 	*
	*Function Name:
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/

static void setLevel_PWMB(uint8_t levelval)
{
    if(mainled.pwmDutyCycle_ch12 <LEVEL_MIN) mainled.pwmDutyCycle_ch12 =LEVEL_MIN;

	if(mainled.pwmDutyCycle_ch12>LEVEL_PWM_MAX)mainled.pwmDutyCycle_ch12=LEVEL_PWM_MAX;

	 MX_TIM1_Init();
	 HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
}
/*************************************************************************
 	*
	*Function Name:
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/

static void setLevel_PWMA(uint8_t levelval)
{
	
   if(mainled.pwmDutyCycle_ch22 <LEVEL_MIN) mainled.pwmDutyCycle_ch22=LEVEL_MIN;
   if(mainled.pwmDutyCycle_ch22>LEVEL_PWM_MAX) mainled.pwmDutyCycle_ch22=LEVEL_PWM_MAX;
	
	MX_TIM2_Init();
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;  //2.the second turn on Enable

}
/*************************************************************************
 	*
	*Function Name:void changeBrightness(uint8_t dir)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void changeBrightness(uint8_t dir)
{
	if(hasLedOn)
	{
		if(mainled.led_by_a == 1){
			mainled.led_by_b = 0;
			if(dir=='1')	// adj +
			{
				level_a+=LEVEL_STEP;
				if(level_a>LEVEL_PWM_MAX ) level_a=LEVEL_PWM_MAX ;
			}
			else	// adj -
			{
				if(level_a<LEVEL_MIN)	level_a=LEVEL_MIN;
				else 	level_a-=LEVEL_STEP;
			}
			setLevel_PWMA(level_a);
		}
		if(mainled.led_by_b == 1){
			mainled.led_by_a = 0;
			if(dir=='1')	// adj +
			{
				level_b+=LEVEL_STEP;
				if(level_b>LEVEL_PWM_MAX ) level_b=LEVEL_PWM_MAX ;
			}
			else	// adj -
			{
				if(level_b<LEVEL_MIN)	level_b=LEVEL_MIN;
				else 	level_b-=LEVEL_STEP;
			}
		      setLevel_PWMB(level_b);
		}
	}
}


