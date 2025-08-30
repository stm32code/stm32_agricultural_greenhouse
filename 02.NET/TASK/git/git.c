#include "git.h"

Data_TypeDef Data_init;						  // �豸���ݽṹ��
Threshold_Value_TypeDef threshold_value_init; // �豸��ֵ���ýṹ��
Device_Satte_Typedef device_state_init;		  // �豸״̬
DHT11_Data_TypeDef DHT11_Data;

// ��ȡ���ݲ���
mySta Read_Data(Data_TypeDef *Device_Data)
{

	Read_DHT11(&DHT11_Data); // ��ȡ��ʪ������
	Device_Data->temperatuer = DHT11_Data.temp_int + DHT11_Data.temp_deci * 0.01;
	Device_Data->humiditr = DHT11_Data.humi_int + DHT11_Data.humi_deci * 0.01;
	Device_Data->soil_humi = Soil_value();

	return MY_SUCCESSFUL;
}
// ��ʼ��
mySta Reset_Threshole_Value(Threshold_Value_TypeDef *Value, Device_Satte_Typedef *device_state)
{

	Value->humi_value = 65;
	Value->temp_value = 28;
	Value->soil_humi_value = 90;
	Value->light_value = 70;
	// ״̬����
	device_state->pump_state = 0;

	return MY_SUCCESSFUL;
}
// ����OLED��ʾ��������
mySta Update_oled_massage()
{
#if OLED // �Ƿ��
	char str[50];
	sprintf(str, "T:%.1f  H:%.1f  ", Data_init.temperatuer, Data_init.humiditr);
	OLED_ShowCH(0, 0, (unsigned char *)str);
	sprintf(str, "����ʪ��: %d    ", Data_init.soil_humi);
	OLED_ShowCH(0, 2, (unsigned char *)str);
	sprintf(str, "����: %03d  %d ", Data_init.light,Data_init.Flage);
	OLED_ShowCH(0, 4, (unsigned char *)str);
	
//	if(Connect_Net){
//		sprintf(str, "���ݴ����� :%d ",Connect_Net);	
//	}else{
//		sprintf(str, "û���豸����:%d",Connect_Net);
//	}
//	OLED_ShowCH(0, 6, (unsigned char *)str);
#endif

	return MY_SUCCESSFUL;
}

// �����豸״̬
mySta Update_device_massage()
{
	// ��ֵ�ж�
	if (Data_init.soil_humi < threshold_value_init.soil_humi_value || Data_init.temperatuer > threshold_value_init.temp_value || Data_init.humiditr > threshold_value_init.humi_value)
	{
		Beep = ~Beep;
	}
	else
	{
		Beep = 0;
	}
	// ��ʼˮ��
	if (Data_init.soil_humi < threshold_value_init.soil_humi_value || device_state_init.pump_state)
	{
		relay1out = 1 ;
	}else{
		relay1out = 0 ;
	}
	// LED
	if (Data_init.light < threshold_value_init.light_value)
	{
		relay2out = 1 ;
	}else{
		relay2out = 0 ;
	}
	
	// �������ݵ�APP
	if (Data_init.App)
	{
		switch (Data_init.App)
		{
		case 1:
			SendMqtt(1); // �������ݵ�APP
			break;
		case 2:
			break;
		}
		Data_init.App = 0;
	}

	return MY_SUCCESSFUL;
}

// ��ʱ��
void Automation_Close(void)
{

	// 1�뵹��
	Data_init.light = getValue();
	
}
// ��ⰴ���Ƿ���
static U8 num_on = 0;
static U8 key_old = 0;
void Check_Key_ON_OFF()
{
	U8 key;
	key = KEY_Scan(1);
	// ����һ�εļ�ֵ�Ƚ� �������ȣ������м�ֵ�ı仯����ʼ��ʱ
	if (key != 0 && num_on == 0)
	{
		key_old = key;
		num_on = 1;
	}
	if (key != 0 && num_on >= 1 && num_on <= Key_Scan_Time) // 25*10ms
	{
		num_on++; // ʱ���¼��
	}
	if (key == 0 && num_on > 0 && num_on < Key_Scan_Time) // �̰�
	{
		switch (key_old)
		{
		case KEY1_PRES:
			// ��������ˮ��
			if(device_state_init.pump_state){
				device_state_init.pump_state = 0;
			}else{
				device_state_init.pump_state = 1;
			}
			Data_init.Flage = device_state_init.pump_state;
			
			break;
		case KEY2_PRES:
			break;
		case KEY3_PRES:
			break;
		default:
			break;
		}
		num_on = 0;
	}
	else if (key == 0 && num_on >= Key_Scan_Time) // ����
	{
		switch (key_old)
		{
		case KEY1_PRES:
			break;
		case KEY2_PRES:
			break;
		case KEY3_PRES:
			break;
		default:
			break;
		}
		num_on = 0;
	}
}
// ����json����
mySta massage_parse_json(char *message)
{

	cJSON *cjson_test = NULL; // ���json��ʽ
	// cJSON *cjson_data = NULL; // ����

	const char *massage;
	// ������������
	u8 cjson_cmd; // ָ��,����

	/* ��������JSO���� */
	cjson_test = cJSON_Parse(message);
	if (cjson_test == NULL)
	{
		// ����ʧ��
		printf("parse fail.\n");
		return MY_FAIL;
	}

	/* ���θ���������ȡJSON���ݣ���ֵ�ԣ� */
	cjson_cmd = cJSON_GetObjectItem(cjson_test, "cmd")->valueint;
	/* ����Ƕ��json���� */
	// cjson_data = cJSON_GetObjectItem(cjson_test, "data");
	switch (cjson_cmd)
	{
		case 0x01: // ��Ϣ��
			Data_init.Flage = cJSON_GetObjectItem(cjson_test, "flage")->valueint;
			Data_init.App = 1;
			break;
		case 0x02: // ��Ϣ��
			device_state_init.pump_state = cJSON_GetObjectItem(cjson_test, "pump")->valueint;
			Data_init.App = 1;
			break;
		case 0x03: // ���ݰ�
			threshold_value_init.humi_value = cJSON_GetObjectItem(cjson_test, "humi_v")->valueint;
			threshold_value_init.light_value = cJSON_GetObjectItem(cjson_test, "light_v")->valueint;
			threshold_value_init.soil_humi_value = cJSON_GetObjectItem(cjson_test, "soil_humi_v")->valueint;
			threshold_value_init.temp_value = cJSON_GetObjectItem(cjson_test, "temp_v")->valueint;
			Data_init.App = 1;
			break;

		default:
			break;
	}

	/* ���JSON����(��������)���������� */
	cJSON_Delete(cjson_test);

	return MY_SUCCESSFUL;
}

