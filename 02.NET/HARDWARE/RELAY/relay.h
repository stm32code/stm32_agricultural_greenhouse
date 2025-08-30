#ifndef __RELAY_H
#define __RELAY_H

#include "stm32f10x.h"

#define BEEP_GPIO_PORT GPIOA
#define BEEP_GPIO_CLK RCC_APB2Periph_GPIOA
#define BEEP_GPIO_PIN GPIO_Pin_11

#define RELAY1_GPIO_PORT GPIOA
#define RELAY1_GPIO_CLK RCC_APB2Periph_GPIOA
#define RELAY1_GPIO_PIN GPIO_Pin_12

#define RELAY2_GPIO_PORT GPIOA
#define RELAY2_GPIO_CLK RCC_APB2Periph_GPIOA
#define RELAY2_GPIO_PIN GPIO_Pin_15


#define Beepin PAin(11)   
#define relay1in PAin(12)
#define relay2in PAin(15)


#define Beep PAout(11)   // Beep
#define relay1out PAout(12) // 风扇接口
#define relay2out PAout(15) // LED接口

void RELAY_GPIO_Config(void);

#endif /* __RELAY_H */
