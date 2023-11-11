#include "tim.h"
#include "encoder.h"

int iTimencoder1;

int GetTim4encoder(void)
{
	  iTimencoder1 =(short)( __HAL_TIM_GET_COUNTER(&htim4));
	  __HAL_TIM_SetCounter(&htim4, 0);
	  return iTimencoder1;
}

int iTimencoder2;

int GetTim2encoder(void)
{
	iTimencoder2 = (short)(__HAL_TIM_GET_COUNTER(&htim2));
	__HAL_TIM_SetCounter(&htim2, 0);
	return iTimencoder2;
}

