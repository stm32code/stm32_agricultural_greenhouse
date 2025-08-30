#ifndef __GIT__H
#define __GIT__H

//  �豸ʹ�����趨��
#define OLED 1			// �Ƿ�ʹ��OLED
#define NET_SERVE 1		// ƽ̨ѡ��
#define NETWORK_CHAEK 1 // �Ƿ������߼��
#define KEY_OPEN 1		// �Ƿ��������Ͷ̰����
#define USART2_OPEN 0	// �Ƿ�ʹ�ô��ڶ�

// ���ݶ���
typedef unsigned char U8;
typedef signed char S8;
typedef unsigned short U16;
typedef signed short S16;
typedef unsigned int U32;
typedef signed int S32;
typedef float F32;

//  C��
#include "cjson.h"
#include <string.h>
#include <stdio.h>
// ��Ƭ��ͷ�ļ�
#include "sys.h"
#include "usart.h"
// ����Э���
#include "net.h"
// �����豸
#include "esp8266.h"
// ������
#include "task.h"
#include "timer.h"
// Ӳ������
#include "delay.h"
#include "usart.h"
#include "git.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "flash.h"
#include "dht11.h"
#include "sgp30.h"
#include "sg90.h"
#include "adc.h"
#include "level.h"
#include "relay.h"
#include "BH1750.h"

#if OLED // OLED�ļ�����
#include "oled.h"
#endif

// ��������Ϣ
#define SSID "NET"		 // ·����SSID����
#define PASS "12345678"		 // ·��������

// ����������ƽ̨��������֧�֣�
#define ServerIP "iot-06z00axdhgfk24n.mqtt.iothub.aliyuncs.com" // ������IP��ַ
#define ServerPort 1883											// ������IP��ַ�˿ں�

// �豸��Ϣ
#define PROID "smart_device&h9sjsuVlfGs"																// ��ƷID
#define DEVID "h9sjsuVlfGs.smart_device|securemode=2,signmethod=hmacsha256,timestamp=1706946178834|" // �豸ID
#define AUTH_INFO "d8c70085d0b48e85d3c42d572df6ede03cc8e49d6da91ec4b741bf76078cbc4d"						// ��Ȩ��Ϣ

// MQTT���� /broadcast/
#define S_TOPIC_NAME "/broadcast/h9sjsuVlfGs/test1" // ��Ҫ���ĵ�����
#define P_TOPIC_NAME "/broadcast/h9sjsuVlfGs/test2" // ��Ҫ����������

#define P_TOPIC_CMD "/sys/h9sjsuVlfGs/smart_device/thing/event/property/post"

// �Զ��岼������
typedef enum
{
	MY_TRUE,
	MY_FALSE
} myBool;

// �Զ���ִ�н������
typedef enum
{
	MY_SUCCESSFUL = 0x01, // �ɹ�
	MY_FAIL = 0x00		  // ʧ��

} mySta; // �ɹ���־λ

typedef enum
{
	OPEN = 0x01, // ��
	CLOSE = 0x00 // �ر�

} On_or_Off_TypeDef; // �ɹ���־λ

typedef enum
{
	DERVICE_SEND = 0x00, // �豸->ƽ̨
	PLATFORM_SEND = 0x01 // ƽ̨->�豸

} Send_directino; // ���ͷ���

typedef struct
{
	U8 App;			 // ָ��ģʽ
	U8 Device_State; // ģʽ
	U8 Page;		 // ҳ��
	U8 Error_Time;
	U8 time_cut_page; // ҳ��
	U8 Flage;		  // ģʽѡ��

	F32 temperatuer; // �¶�
	F32 humiditr;	 // ʪ��
	U16 soil_humi;	 // ����ʪ��

	u8 light; // ����
	u8 ucId;

} Data_TypeDef; // ���ݲ����ṹ��

typedef struct
{

	U16 soil_humi_value; // ������ֵ
	U16 humi_value;		 // ʪ����ֵ
	U16 temp_value;		 // �¶���ֵ
	U16 light_value;	 // ������ֵ

} Threshold_Value_TypeDef; // ���ݲ����ṹ��

typedef struct
{
	U8 pump_state; // ˮ��״̬

} Device_Satte_Typedef; // ״̬�����ṹ��

// ȫ������
extern Data_TypeDef Data_init;
extern Device_Satte_Typedef device_state_init; // �豸״̬

extern Threshold_Value_TypeDef threshold_value_init; // �豸��ֵ���ýṹ��

// ��ȡ���ݲ���
mySta Read_Data(Data_TypeDef *Device_Data);
// ��ʼ��
mySta Reset_Threshole_Value(Threshold_Value_TypeDef *Value, Device_Satte_Typedef *device_state);
// ����OLED��ʾ��������
mySta Update_oled_massage(void);
// �����豸״̬
mySta Update_device_massage(void);
// ����json����
mySta massage_parse_json(char *message);
// ��ⰴ���Ƿ���
void Check_Key_ON_OFF(void);
// ��ʱ��
void Automation_Close(void);

#endif
