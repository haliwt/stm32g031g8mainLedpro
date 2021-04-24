#include "mainled.h"
#include "usart.h"
#include "pwm.h"
#include "gpio.h"

mainled_t mainled;
static uint8_t BCC_CHECK(void);


void mainSingleLed_Test(void)
{
    uint8_t temp;
	uint8_t cmdType_0 = aRxBuffer[0]; //command order 1
	uint8_t cmdType_1 = aRxBuffer[1]; //command order 1
	mainled.led_by_a =    aRxBuffer[2];	  //command order 0
	mainled.led_by_b =    aRxBuffer[3];	  //command order 1
	//uint8_t cmdType_4 = aRxBuffer[4]; //command order 1
	uint8_t cmdType_5 = aRxBuffer[5]; //check sum codes
	uint8_t cmdType_6 = aRxBuffer[6]; //command order 1
	temp = BCC_CHECK();
	HAL_UART_Transmit(&huart1,&temp,1, 2);
	if(cmdType_0 == 0x42){
		if(cmdType_1 == 0x4c){
			if(cmdType_6 == temp){
				
				mainTheFirstGroup_SingleLEDA();
				mainTheSecondGroup_SingleLEDB();
				mainFanControl(cmdType_5);
			}
		}
	}
}
  
/*************************************************************************
 	*
	*Function Name: void TheFirstGroup_SingleLEDA(uint8_t ledvala)
	*Function : Turn On LEDAxx LED
	*Input Ref: receive UART of data
	*Output Ref:No
	*
******************************************************************************/
void mainTheFirstGroup_SingleLEDA(void)
{
        if (mainled.led_by_a > 8)
        {
          mainTurnOff_TheFirstLedA();
		
		}
        else
        {
            switch (mainled.led_by_a)
            {

			case 0:
					mainTurnOff_TheFirstLedA();
				
			break;
			
			case 1:
			    mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
                mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
				//1.turn on LEDA1 =1
			   HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_SET);
			   //2.EN on
                HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
                
                break;

            case 2:
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
	
				mainTurnOff_TheFirstLedA();
								HAL_Delay(100);
                //turn on LEDA2  
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
                break;

            case 3:
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA3
                HAL_GPIO_WritePin(LEDA3_GPIO_Port, LEDA3_Pin, GPIO_PIN_SET);
				//2. enable
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
                break;

            case 4:
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA4
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_SET);
			    //2 .EN
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
                break;

            case 5:
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA5
                HAL_GPIO_WritePin(LEDA5_GPIO_Port, LEDA5_Pin, GPIO_PIN_SET);      //1.the first turn on LED
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;  //2.the second turn on Enable
                break;

            case 6:
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA6
                HAL_GPIO_WritePin(LEDA6_GPIO_Port, LEDA6_Pin, GPIO_PIN_SET);
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ; //2.the second turn on Enable
                break;

            case 7:
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA7
                HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin, GPIO_PIN_SET);
				 HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;//2.the second turn on Enable
                break;

            case 8:
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
                //turn on LEDA8
                HAL_GPIO_WritePin(LEDA8_GPIO_Port, LEDA8_Pin, GPIO_PIN_SET);
				HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;  //2.the second turn on Enable
                break;
            }
        }
}

/*************************************************************************
 	*
	*Function Name: void mainTheSecondGroup_SingleLEDB(uint_8 ledvalb)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void mainTheSecondGroup_SingleLEDB(void)
{

	if (mainled.led_by_b> 8)
	{
		mainTurnOff_TheSecondLedB();
			
		}
        else
        {
			switch (mainled.led_by_b)
			{
			case 0:
				 mainTurnOff_TheSecondLedB();
				
				 break;

            case 1:
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				//1.turn on LEDB1 =1
                HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin, GPIO_PIN_SET);
				 HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
                break;

            case 2:
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);

				//turn on LEDB1
                HAL_GPIO_WritePin(LEDB2_GPIO_Port, LEDB2_Pin, GPIO_PIN_SET);
				 HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
                break;

			case 3:
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
							  //turn on LEDB3=1
                HAL_GPIO_WritePin(LEDB3_GPIO_Port, LEDB3_Pin, GPIO_PIN_SET);
				HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
                break;

            case 4:
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				//turn on LEDB4=1
                HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin, GPIO_PIN_SET);
                 HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			break;

            case 5:
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				//turn on LEDB5=1
                HAL_GPIO_WritePin(LEDB5_GPIO_Port, LEDB5_Pin, GPIO_PIN_SET);
                HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			break;

            case 6:
                // HAL_GPIO_WritePin(LEDB6_GPIO_Port,LEDB6_Pin, GPIO_PIN_SET);
                break;

            case 7:
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				//turn on LEDB7 =1
                HAL_GPIO_WritePin(LEDB7_GPIO_Port, LEDB7_Pin, GPIO_PIN_SET);
                 HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			break;

            case 8:
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				HAL_Delay(100);
				mainTurnOff_TheSecondLedB();
				HAL_Delay(100);
				//turn on LEDB8 =1
                HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_SET);
                HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
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
	   HAL_Delay(200);
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
		 HAL_Delay(200);
		 HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin | LEDB2_Pin | LEDB3_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin | LEDB5_Pin | LEDB7_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_RESET);
}
/*************************************************************************
 	*
	*Function Name:
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
static uint8_t BCC_CHECK(void)
{
   uint8_t i;
	 
	 uint8_t tembyte =0xAA ^ aRxBuffer[2];
	
    for (i = 3; i <6; i++) {
        tembyte = tembyte ^ aRxBuffer[i];
    }
    return tembyte;

}


