#include "filter.h"

// a = tau / (tau + dt)  加权系数 a 其中tau为时间常数 每个系统的tau不一样
// acc = 加速度传感器数据
// gyro = 陀螺仪数据
// dt = 运行周期  一般是我们自己设置的，例如在1s内运行200次， 那么dt = 1000ms / 200hz = 5ms

float a;
float angle;

float ComplementaryFilter(float acc, float gyro, float dt)
{
	a = 0.98;
	angle = a * (angle + gyro * dt) + (1 - a) * (acc);
	return angle;
}

