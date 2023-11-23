#include "control.h"
#include "mpu6050.h"
#include "filter.h"
#include "math.h"
#include "tim.h"

short x_nAcc, y_nAcc, z_nAcc;
short x_nGyro, y_nGyro, z_nGyro;
float x_fAcc, y_fAcc, z_fAcc;

float g_fAccAngle;
float g_fGyroAngleSpeeed;
float g_fCarAngle;  //小车倾角
float dt = 0.005;

unsigned char g_ucMainEventCount;

unsigned int g_nLeftMotorPulse; //全局变量，用于保存左电机的脉冲数


int g_nSpeedTarget = 0;  //全局变量，速度目标值
int g_nLeftMotorOutput; //做电机输出

int nErrorPrev; //上一次偏差值
int nPwmBais, nPwm; //pwm增量，pwm总量

void GetMpuData(void)
{	
		MPU_Get_Accelerometer(&x_nAcc, &y_nAcc, &z_nAcc);
		MPU_Get_Gyroscope(&x_nGyro, &y_nGyro, &z_nGyro);
}

void AngleCalculate(void)
{
	// 量程为±2g， 灵敏度：16384 LSB/g
	
		x_fAcc = x_nAcc / 16384.0;
		y_fAcc = y_nAcc / 16384.0;
		z_fAcc = z_nAcc / 16384.0;
		
		g_fAccAngle = atan2(y_fAcc, z_fAcc) * 180.0 / 3.14;
		
		g_fGyroAngleSpeeed = x_nGyro / 16.4;  // 角速度， 范围为2000deg/s时， 换算为16.4 LSB/(deg / s)
		
		g_fCarAngle = ComplementaryFilter(g_fAccAngle, g_fGyroAngleSpeeed, dt);
}

void GetMotorPulse(void)
{
		g_nLeftMotorOutput = (short)(__HAL_TIM_GET_COUNTER(&htim4));
		__HAL_TIM_SET_COUNTER(&htim4, 0);   
}

int SpeedInnerControl(int nPluse, int nTarget){
		int nError;
		float		fP = 10.0, fI = 0.9;	
	  uint8_t OutData[3];
	  nError = nPluse - nTarget;
	
		nPwmBais = fP * (nError - nErrorPrev) + fI * nError;
	
		nErrorPrev = nError; //保存上一次的误差
		
		nPwm += nPwmBais;
	  
	  if(nPwm > 999) nPwm = 999;//限制上限，防止超出PWM量程
    if(nPwm <-999) nPwm =-999;
		
		OutData[0] = (float)nPluse;	
	  OutData[1] = (float)nTarget;
		OutData[2] = (float)nPwm; 
	  
	  return nPwm;
}

void SetMotorVoltageAndDirection(int nMotorPwm)
{
		if(nMotorPwm < 0){
						HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
						HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
						nMotorPwm = (-nMotorPwm);//如果计算值是负值，先取负得正，因为PWM寄存器只能是正值
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, nMotorPwm);
        }
		else
        {
						HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, nMotorPwm);
        }
}

