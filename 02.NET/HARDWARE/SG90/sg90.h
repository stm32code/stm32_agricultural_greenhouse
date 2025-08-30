#ifndef __SG90_H
#define __SG90_H

#include "stm32f10x.h"
#include "git.h"

/* TIM3--PWM���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�PWM���� */
#define TIM2_GPIO_PORT_TIME1_2 GPIOA									 /* GPIO�˿� */
#define TIM2_GPIO_PORT_TIME3_4 GPIOA									 /* GPIO�˿� */
#define TIM2_GPIO_CLK_TIME1_2 RCC_APB2Periph_GPIOA						 /* GPIO�˿�ʱ�� */
#define TIM2_GPIO_CLK_TIME3_4 RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO /* GPIO�˿�ʱ�� */
#define TIM2_GPIO_PIN1 GPIO_Pin_0
#define TIM2_GPIO_PIN2 GPIO_Pin_1
#define TIM2_GPIO_PIN3 GPIO_Pin_2
#define TIM2_GPIO_PIN4 GPIO_Pin_3

void TIM2_PWM_Init(U32 f);
// ���ٲ���
void MG996R_Speed(void);
// SG90�������
/*
	20ms����
	5-14  ��ת��ֵԽС��ת��Խ��
	16-25 ��ת��ֵԽ��ת��Խ��
*/
void Automation_SG90_Angle(U8 cmd, U8 dirt);

#endif /* __PWM_H */
