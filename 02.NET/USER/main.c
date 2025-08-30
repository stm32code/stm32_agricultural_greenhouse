#include "git.h"

// �����ʱ���趨
static Timer task1_id;
static Timer task2_id;
static Timer task3_id;
extern u8 time25ms;

// ��ȡȫ�ֱ���
const char *topics[] = {S_TOPIC_NAME};
char str[50];

// Ӳ����ʼ��
void Hardware_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    HZ = GB16_NUM();                                // ����
    delay_init();                                   // ��ʱ������ʼ��
    GENERAL_TIM_Init(TIM_4, 0, 1);
    Usart1_Init(115200); // ����1��ʼ��Ϊ115200
    USART2_Init(115200); // ����2������ESP8266��

    System_PB34_setIO();
    LED_Init();

    DHT11_GPIO_Config(); // dht11
    ADCx_Init();         // ADC
    RELAY_GPIO_Config(); // ���Ⱥ�led
    bh1750_iic_init();   // BH1750
    Key_GPIO_Config();   // key
	
    relay1out = 0;       // �ر�ˮ��
    relay2out = 0;       // �ر�LED
    Beep      = 0;       // �رշ�����

#if OLED // OLED�ļ�����
    OLED_Init();
    OLED_ColorTurn(0);   // 0������ʾ��1 ��ɫ��ʾ
    OLED_DisplayTurn(0); // 0������ʾ 1 ��Ļ��ת��ʾ
#endif
    while (Reset_Threshole_Value(&threshold_value_init, &device_state_init) != MY_SUCCESSFUL)
        delay_ms(5); // ��ʼ����ֵ

#if OLED // OLED�ļ�����
    OLED_Clear();
#endif
}
// �����ʼ��
void Net_Init()
{

#if OLED // OLED�ļ�����
    OLED_Clear();
    // дOLED����
    sprintf(str, "-���WIFI�ȵ�");
    OLED_ShowCH(0, 0, (unsigned char *)str);
    sprintf(str, "-����:%s         ", SSID);
    OLED_ShowCH(0, 2, (unsigned char *)str);
    sprintf(str, "-����:%s         ", PASS);
    OLED_ShowCH(0, 4, (unsigned char *)str);
    sprintf(str, "-Ƶ��: 2.4 GHz   ");
    OLED_ShowCH(0, 6, (unsigned char *)str);
#endif
    ESP8266_Init();          // ��ʼ��ESP8266
	
    while (DevLink()) // ����
        delay_ms(300);
    while (Subscribe(topics, 1)) // ��������
        delay_ms(300);

    Connect_Net = 60; // �����ɹ�
#if OLED              // OLED�ļ�����
    OLED_Clear();
#endif
}

// ����1
void task1(void)
{
    // 1�������
    Automation_Close();
}
// ����2
void task2(void)
{
    Read_Data(&Data_init);   // ���´���������
    Update_oled_massage();   // ����OLED
    Update_device_massage(); // �����豸
                             // BEEP= ~BEEP;
    State = ~State;
}
// ����3
void task3(void)
{
    if ( Data_init.App == 0) {
        Data_init.App = 1;
    }
}
// �����ʼ��
void SoftWare_Init(void)
{
    // ��ʱ����ʼ��
    timer_init(&task1_id, task1, 1000, 1); // ÿ1��
    timer_init(&task2_id, task2, 100, 1);  // �������ݰ�
    timer_init(&task3_id, task3, 3000, 1); // ÿ2.5�뷢��һ�����ݵ��ͻ���

    timer_start(&task1_id);
    timer_start(&task2_id);
    timer_start(&task3_id);
		
}
// ������
int main(void)
{
    char *ptrIPD           = NULL;
    unsigned char *dataPtr = NULL;
    SoftWare_Init(); // �����ʼ��
    Hardware_Init(); // Ӳ����ʼ��
    Net_Init();            // �����ʼ
    TIM_Cmd(TIM4, ENABLE); // ʹ�ܼ�����

    while (1) {

        // �߳�
        timer_loop(); // ��ʱ��ִ��
        // ���ڽ����ж�
        dataPtr = ESP8266_GetIPD(0);
        if (dataPtr != NULL) {
            RevPro(dataPtr); // ��������
        }
#if KEY_OPEN
        // �������
        if (time25ms == MY_TRUE) {
            // ��������
            Check_Key_ON_OFF();
            time25ms = MY_FALSE;
        }
#endif
    }
}
