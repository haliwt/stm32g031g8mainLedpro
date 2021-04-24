#include "mainboard.h"
#include "gpio.h"
#include "singleled.h"
#include "usart.h"

uint8_t runStep;
static uint8_t inputCmd[RXBUFFERSIZE];


//static uint8_t cmd;
static uint8_t state;
static uint8_t decodeFlag;

static uint8_t cmdSize;
static uint8_t paraIndex;
static uint8_t crcCheck;
static uint8_t level;

static void RunCmd(void);
/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
static void RunCmd(void)
{
	uint8_t cmdType=inputCmd[0];
	//uint8_t ret;

	switch(cmdType)
	{
	case 'S':	//	select led  hex:53
		//ledCtrl(((inputCmd[1]-0x30)*10+inputCmd[2]-0x30),1);
		break;
	case 'C':
		//turnOffAll();
		break;
	case 'A':
		//changeBrightness(inputCmd[1]);
		break;
	default:
		break;
	}



}
/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
void UART_ReceiveDataFunction(void)
{
	switch(state)
	{
	case STATE_PREAMBLE1:
		if(aRxBuffer[0]=='M') // hex:4D
			state=STATE_PREAMBLE2;
		break;
	case STATE_PREAMBLE2:
		if(aRxBuffer[0]=='X') // hex:58
		{
			state=STATE_ADDR;
		}
		else
			state=STATE_PREAMBLE1;  //'M' - hex:4D
		break;
	case STATE_ADDR:
		if(aRxBuffer[0]==BOARD_ADDR)
		{
			state=STATE_CMD; //hex:53 -'S'
		}
		else
			state=STATE_PREAMBLE1; //hex:4D-- 'M'
		break;
	case STATE_CMD:
		inputCmd[0]=aRxBuffer[0];
		crcCheck = 0x55 ^ inputCmd[0];
		//decodeFlag=1;
		state=STATE_SIZE;
		break;
	case STATE_SIZE:
		cmdSize=aRxBuffer[0]-0x30;
		if(cmdSize>MAX_CMD_PARA_SIZE)	// out of range
		{
			state=STATE_PREAMBLE1;
		}
		else if(cmdSize>0)
		{
			paraIndex=1;
			crcCheck ^= aRxBuffer[0];
			state=STATE_PARA;
		}
		else	// no parameter
		{
			crcCheck ^= aRxBuffer[0];
			decodeFlag=1;
			state=STATE_PREAMBLE1;
		}
		break;
	case STATE_PARA:
		inputCmd[paraIndex]=aRxBuffer[0];
		crcCheck ^= aRxBuffer[0];
		paraIndex++;
		cmdSize--;
		if(cmdSize==0)
		{
			decodeFlag=1;
			state=STATE_PREAMBLE1;
		}
		break;
	case STATE_CRC:
		//if((crcCheck ^ aRxBuffer[0])==0)
		{
			//decodeFlag=1;
		}
		state=STATE_PREAMBLE1;
		break;
	default:
		state=STATE_PREAMBLE1;
		decodeFlag=0;
	}
	HAL_UART_Receive_IT(&huart1,aRxBuffer,1);


}
/*************************************************************************
 	*
	*Function Name: void DecodeTestCase(void)
	*Function : decode from UART receive data
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
 void DecodeTestCase(void)
 {
       if(runStep){
			runStep=0;
		    RunCmd();
	   
	   
	   }
 
 
 }
 /********************************************************************************
	*
	*Function Name: HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*
	*
	*
********************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   
     UART_ReceiveDataFunction();


}
 