#include "sg90.h"
#include "delay.h"
#include "key.h"

/*********************************************************************************
 * @Function	: TIM3 PWM�����ʼ��
 * @Input		: F :Ƶ�ʣ�HZ��
 * @Output		: None
 * @Return		: None
 * @Others		: None
 * @Date		: 2022-11-2
 **********************************************************************************/
void TIM2_PWM_Init(U32 f)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(TIM2_GPIO_CLK_TIME3_4, ENABLE);
    //  GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); // ��仰������ԭ�ӹٷ����̡�PWM���ʵ�顱�и��ģ�Ŀ����Timer3��ȫ��ӳ�䣬��TIM3_CH4->PC9����ʵ�鲻����ӳ��
    //  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //��仰������ԭ�ӹٷ����̡�PWM���ʵ�顱�и��ģ�Ŀ����Timer3������ӳ�䣬��TIM3_CH2->PB5����ʵ�鲻����ӳ��

    // ����PC6��PC7Ϊ����������ܣ����TIM3 CH1��TIM3 CH2��PWM���岨��
    //    GPIO_InitStructure.GPIO_Pin = TIM2_GPIO_PIN1 | TIM2_GPIO_PIN2;
    //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // �����������
    //    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //    GPIO_Init(TIM2_GPIO_PORT_TIME1_2, &GPIO_InitStructure);

    // ����PC8��PC9Ϊ����������ܣ����TIM3 CH3��TIM3 CH4��PWM���岨��
    GPIO_InitStructure.GPIO_Pin = TIM2_GPIO_PIN3 | TIM2_GPIO_PIN4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TIM2_GPIO_PORT_TIME3_4, &GPIO_InitStructure);

    TIM_DeInit(TIM3); // ��ʱ��1��ʼ��
    /*--------------------ʱ���ṹ���ʼ��-------------------------*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    // �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = 200 - 1;
    // ����CNT��������ʱ�� = Fck_int/(psc+1)
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;
    // ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    // ����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // �ظ���������ֵ��û�õ����ù�
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    // ��ʼ����ʱ��
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    /*--------------------����ȽϽṹ���ʼ��-------------------*/
    TIM_OCInitTypeDef TIM_OCInitStructure;
    // ����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    // ���ʹ��
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    // ����ʱ�����ƽΪ��
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    // ���ͨ����ƽ��������
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // TIM_OCInitStructure.TIM_Pulse = xperiod_xprescaler.TIM2_Period / 2; // �������Ƚ�ֵ��ռ�ձ�Ϊ50%

    //    // ��ʼ��TIM3 Channel 1 PWM
    //    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               // ����ΪPWM2ģʽ��TIMx_CNT>TIMx_CCR1��Ϊ��Ч��ƽ
    //    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;  // ����ʱ1NҲ����׵�ƽ
    //    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;      // ��ʱ������֮������͵�ƽ
    //    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // ʹ�����
    //    TIM_OC1Init(TIM2, &TIM_OCInitStructure);                        // ����Ƚ�ͨ�� 1
    //    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

    //    // ��ʼ��TIM3 Channel 2 PWM
    //    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               // ����ΪPWM2ģʽ��TIMx_CNT>TIMx_CCR1��Ϊ��Ч��ƽ
    //    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;  // ����ʱ1NҲ����ߵ�ƽ
    //    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;      // ��ʱ������֮������͵�ƽ
    //    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // ʹ�����
    //    TIM_OC2Init(TIM2, &TIM_OCInitStructure);                        // ����Ƚ�ͨ�� 2
    //    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // // ��ʼ��TIM3 Channel 3 PWM
    // TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               // ����ΪPWM2ģʽ��TIMx_CNT>TIMx_CCR1��Ϊ��Ч��ƽ
    // TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;  // ����ʱ1NҲ����׵�ƽ
    // TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;      // ��ʱ������֮������͵�ƽ
    // TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // ʹ�����
    // TIM_OC3Init(TIM2, &TIM_OCInitStructure);                        // ����Ƚ�ͨ�� 3
    // TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // ��ʼ��TIM3 Channel 4 PWM
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               // ����ΪPWM2ģʽ��TIMx_CNT>TIMx_CCR1��Ϊ��Ч��ƽ
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;  // ����ʱ1NҲ����ߵ�ƽ
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;      // ��ʱ������֮������͵�ƽ
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // ʹ�����
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);                        // ����Ƚ�ͨ�� 4
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_CtrlPWMOutputs(TIM2, ENABLE);
    TIM_ARRPreloadConfig(TIM2, ENABLE); // ʹ���Զ���װ�ؼĴ�����arr��Ԥװ��
    TIM_Cmd(TIM2, ENABLE);

    // TIM_SetCompare1(TIM2, 15);
    // TIM_SetCompare2(TIM2, 15);
    // TIM_SetCompare3(TIM2, 15);
    TIM_SetCompare4(TIM2, 15);
}

// SG90�������
/*
    20ms����
    5-14  ��ת��ֵԽС��ת��Խ��
    16-25 ��ת��ֵԽ��ת��Խ��
*/
void Automation_SG90_Angle(U8 cmd, U8 dirt)
{

    switch (cmd)
    {
    case 1:
        TIM_SetCompare1(TIM2, dirt);
        break;
    case 2:
        TIM_SetCompare2(TIM2, dirt);
        break;
    case 3:
        TIM_SetCompare3(TIM2, dirt);
        break;
    case 4:
        TIM_SetCompare4(TIM2, dirt);
        break;
    }
    delay_ms(50); // �ȴ��ȶ�
}
