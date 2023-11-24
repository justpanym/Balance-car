#ifndef __CONTROL_H
#define __CONTROL_H

#include "filter.h"

extern unsigned char g_ucMainEventCount;
extern float g_fAccAngle;//加速度传感器经过atan2()解算得到的角度
extern float g_fGyroAngleSpeed;//陀螺仪角速度
extern float g_fCarAngle;//小车倾角
extern unsigned int g_nLeftMotorPulse;
extern int g_nSpeedTarget;
extern int g_nLeftMotorOutput;
extern float g_fCarSpeed,g_fCarSpeedPrev;
extern int nPwmBais,nPwm;//PWM增量，PWM总量

void GetMpuData(void);
void AngleCalculate(void);
void GetMotorPulse(void);
int SpeedInnerControl(int nPulse,int nTarget);
void SetMotorVoltageAndDirection(int nMotorPwm);

#endif


