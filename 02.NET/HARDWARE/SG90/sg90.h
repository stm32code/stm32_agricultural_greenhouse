#ifndef __SG90_H
#define __SG90_H

#include "stm32f10x.h"
#include "git.h"

/* TIM3--PWM连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的PWM引脚 */
#define TIM2_GPIO_PORT_TIME1_2 GPIOA									 /* GPIO端口 */
#define TIM2_GPIO_PORT_TIME3_4 GPIOA									 /* GPIO端口 */
#define TIM2_GPIO_CLK_TIME1_2 RCC_APB2Periph_GPIOA						 /* GPIO端口时钟 */
#define TIM2_GPIO_CLK_TIME3_4 RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO /* GPIO端口时钟 */
#define TIM2_GPIO_PIN1 GPIO_Pin_0
#define TIM2_GPIO_PIN2 GPIO_Pin_1
#define TIM2_GPIO_PIN3 GPIO_Pin_2
#define TIM2_GPIO_PIN4 GPIO_Pin_3

void TIM2_PWM_Init(U32 f);
// 变速测试
void MG996R_Speed(void);
// SG90舵机控制
/*
	20ms脉冲
	5-14  正转，值越小，转的越快
	16-25 反转，值越大，转的越快
*/
void Automation_SG90_Angle(U8 cmd, U8 dirt);

#endif /* __PWM_H */
