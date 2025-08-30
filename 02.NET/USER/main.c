#include "git.h"

// 软件定时器设定
static Timer task1_id;
static Timer task2_id;
static Timer task3_id;
extern u8 time25ms;

// 获取全局变量
const char *topics[] = {S_TOPIC_NAME};
char str[50];

// 硬件初始化
void Hardware_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    HZ = GB16_NUM();                                // 字数
    delay_init();                                   // 延时函数初始化
    GENERAL_TIM_Init(TIM_4, 0, 1);
    Usart1_Init(115200); // 串口1初始化为115200
    USART2_Init(115200); // 串口2，驱动ESP8266用

    System_PB34_setIO();
    LED_Init();

    DHT11_GPIO_Config(); // dht11
    ADCx_Init();         // ADC
    RELAY_GPIO_Config(); // 风扇和led
    bh1750_iic_init();   // BH1750
    Key_GPIO_Config();   // key
	
    relay1out = 0;       // 关闭水泵
    relay2out = 0;       // 关闭LED
    Beep      = 0;       // 关闭蜂鸣器

#if OLED // OLED文件存在
    OLED_Init();
    OLED_ColorTurn(0);   // 0正常显示，1 反色显示
    OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示
#endif
    while (Reset_Threshole_Value(&threshold_value_init, &device_state_init) != MY_SUCCESSFUL)
        delay_ms(5); // 初始化阈值

#if OLED // OLED文件存在
    OLED_Clear();
#endif
}
// 网络初始化
void Net_Init()
{

#if OLED // OLED文件存在
    OLED_Clear();
    // 写OLED内容
    sprintf(str, "-请打开WIFI热点");
    OLED_ShowCH(0, 0, (unsigned char *)str);
    sprintf(str, "-名称:%s         ", SSID);
    OLED_ShowCH(0, 2, (unsigned char *)str);
    sprintf(str, "-密码:%s         ", PASS);
    OLED_ShowCH(0, 4, (unsigned char *)str);
    sprintf(str, "-频率: 2.4 GHz   ");
    OLED_ShowCH(0, 6, (unsigned char *)str);
#endif
    ESP8266_Init();          // 初始化ESP8266
	
    while (DevLink()) // 接入
        delay_ms(300);
    while (Subscribe(topics, 1)) // 订阅主题
        delay_ms(300);

    Connect_Net = 60; // 入网成功
#if OLED              // OLED文件存在
    OLED_Clear();
#endif
}

// 任务1
void task1(void)
{
    // 1秒计算器
    Automation_Close();
}
// 任务2
void task2(void)
{
    Read_Data(&Data_init);   // 更新传感器数据
    Update_oled_massage();   // 更新OLED
    Update_device_massage(); // 更新设备
                             // BEEP= ~BEEP;
    State = ~State;
}
// 任务3
void task3(void)
{
    if ( Data_init.App == 0) {
        Data_init.App = 1;
    }
}
// 软件初始化
void SoftWare_Init(void)
{
    // 定时器初始化
    timer_init(&task1_id, task1, 1000, 1); // 每1秒
    timer_init(&task2_id, task2, 100, 1);  // 跟新数据包
    timer_init(&task3_id, task3, 3000, 1); // 每2.5秒发送一次数据到客户端

    timer_start(&task1_id);
    timer_start(&task2_id);
    timer_start(&task3_id);
		
}
// 主函数
int main(void)
{
    char *ptrIPD           = NULL;
    unsigned char *dataPtr = NULL;
    SoftWare_Init(); // 软件初始化
    Hardware_Init(); // 硬件初始化
    Net_Init();            // 网络初始
    TIM_Cmd(TIM4, ENABLE); // 使能计数器

    while (1) {

        // 线程
        timer_loop(); // 定时器执行
        // 串口接收判断
        dataPtr = ESP8266_GetIPD(0);
        if (dataPtr != NULL) {
            RevPro(dataPtr); // 接收命令
        }
#if KEY_OPEN
        // 按键监测
        if (time25ms == MY_TRUE) {
            // 密码输入
            Check_Key_ON_OFF();
            time25ms = MY_FALSE;
        }
#endif
    }
}
