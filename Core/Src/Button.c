#include "button.h"
#include "main.h"
#include "stm32f1xx_it.h"

int iButtonCount;//i代表int型变量，ButtonCount表示按键计数变量
int iButtonFlag;//i代表int型变量，ButtonFlag表示重按键标志，1代表重新按键，0为没有重新按键
int g_iButtonState;//g是globle代表全局变量，会在其他地方引用；i代表int型变量，ButtonState表示按键标志，1代表按下，0代表松开
void ButtonScan(void){
  if(   HAL_GPIO_ReadPin(BUTTON_GPIO_Port,BUTTON_Pin) == GPIO_PIN_RESET )//如果引脚检测到低电平
  {
      iButtonCount++;                         //按键按下，计数iButtonCount加1
      if(iButtonCount>=30)                    //1ms中断服务函数里运行一次，iButtonCount大于等于30，即按键已稳定按下30ms
         {
            if(iButtonFlag==0)                  //判断有没有重按键，1为有，0为没有
                {
                    g_iButtonState=1;                 //设置按键标志
                    iButtonCount=0;
                    iButtonFlag=1;                  //设置重按键标志
                    }
                else                              //如果重按键，则重新计数
                    iButtonCount=0;
                }
    else                                  //如果没有稳定按下30ms，则代表没有按下按键
         g_iButtonState=0;

         }
else                                      //如果一直无检测到低电平，即一直无按键按下
    {
         iButtonCount=0;                  //清零iButtonCount
         g_iButtonState=0;                  //清除按键标志
         iButtonFlag=0;                   //清除重按键标志
    }
}
