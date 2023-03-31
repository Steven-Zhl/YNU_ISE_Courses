
#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h" //����stm32��ϵͳͷ�ļ�
#include "servor.h"	   //����GPIO��ͷ�ļ�
#include "usart.h"	   //��������ͨ������ͷ�ļ�
#include "delay.h"	   //����ϵͳ��ʱ����ͷ�ļ�
#include "timer.h"	   //������ʱ������ͷ�ļ�
#include "PS2.h"
#include "key.h"
#include "led.h"
#include "beep.h"
#include "common.h"
#include "adc.h"
#include "motor.h"
#include "control_app.h"
#include "oled.h"
#include "show.h"
#include "encoder.h"
#include "math.h"
int Motor_A, Motor_B, Target_A = 50, Target_B = 50; //�������������
int Voltage_Temp, Voltage_Count, Voltage_All, sum;
int Voltage; //��ص�ѹ������صı���
u32 value;
u32 key, key_bak;
extern u32 a; // a�������������ϵͳ�δ�ʱ���ɼ���������ʱ��
extern uint8 flag_RecFul;
int Encoder_Left, Encoder_Right; //���ұ��������������
int Encoder_A_EXTI;
uint16 CPWM[MOTOR_NUM] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
char redata[500] = {0}; // ����������ݱ�������
uint16 adc_value = 0;
unsigned char flag_scan_ps2 = 0;
u8 LX_AD = 0;
u8 LY_AD = 0;
u8 RX_AD = 0;
u8 RY_AD = 0;
int Motor_Pwm = 6900;
u8 ps2_mode = 0;
char menu = 0;
int i = 0; // sin move count
u8 delay_50, delay_flag;
void scan_ps2(void);
void Check_Power(void);
void ps2_handle(void);
void Check_Battery(void);
/**********************************************************************************/
/*****************************������***********************************************/
int main(void)
{
	SysTick_Init();		  //ϵͳ�δ�ʱ����ʼ��
	Servor_GPIO_Config(); // GPIO��ʼ��
	Uart_Init(2);
	Uart_Init(3);
	Timer_Init(); //��ʱ����ʼ��
	Timer_ON();	  //������ʱ��
	LED_Init();
	// KEY_Init();
	Beep_Init();
	Uart_Init(1);
	PS2_Init();
	OLED_Init(); //=====OLED��ʼ��
	Encoder_Init_TIM3();
	Encoder_Init_TIM_Exit0();
	Encoder_Init_TIM_Exit1();
	Adc_Init();
	USART_Config(USART1, 115200);
	USART_Config(USART2, 115200);
	USART_Config(USART3, 115200);
	Motor_Gpio_init();
	PWM2_Init(7199, 0); // ��ʼ���������Ƶ�� 72/(5+1)  12KHZ
	Led_Test();
	Beep_Test();

	while (1)
	{
		Check_Battery(); //=====��ȡ��ص�ѹ
		scan_ps2();
		oled_show(); //===��ʾ����
		delay_flag = 1;
		delay_50 = 0;
		while (delay_flag)
			; //ͨ����ʱ�ж�ʵ�ֵ�50ms��׼��ʱ
	}
}

void Check_Battery(void)
{
	Voltage_Temp = Get_battery_volt(); //=====��ȡ��ص�ѹ
	Voltage_Count++;				   //=====ƽ��ֵ������
	Voltage_All += Voltage_Temp;	   //=====��β����ۻ�
	if (Voltage_Count == 10)
		Voltage = Voltage_All / 10, Voltage_All = 0, Voltage_Count = 0; //=====��ƽ��ֵ
}

/******  �ص㣡����
һ�δ�����ҡ��ֵ
		LX_AD 0-255 ��ҡ��x��
		LY_AD 0-255 ��ҡ��y��
		RX_AD 0-255 ��ҡ��x��
		RY_AD 0-255 ��ҡ��y��
ת�亯��
	CPWM[1]=1500;�����루��ֵ��Χ500-2500��
ǰ������
		Set_Pwm_Motor1(0);���ֵ����Ϊ7000
		Set_Pwm_Motor2(0);
******/

void scan_ps2(void)
{
	if (flag_scan_ps2) //
	{
		flag_scan_ps2 = 0;
		key = PS2_DataKey();
		// Gain LX_AD,RY_AD and so on
		LX_AD = PS2_AnologData(PSS_LX);
		RY_AD = PS2_AnologData(PSS_RY);
		// UART_Put_Inf("LY_AD:",LY_AD);
		ps2_mode = PS2_RedLight();

		if (ps2_mode == 0)
		{
			//ע��һ��Ҫ�����Ȼ��DEAL_RY_AD��DEAL_RX_AD��ֵ(����ֵĿǰû�ж���)

			Set_Pwm_Motor1((RY_AD - 255 / 2) * 25);
			Set_Pwm_Motor2((RY_AD - 255 / 2) * 25);
			CPWM[1] = LX_AD * 2000 / 255 + 500;

			switch (key) //��Ϊ�ο�����һ��Ҫ������if��Ҳ��
			{
			case PSB_PAD_UP:
				Set_Pwm_Motor1(5000); //�������
				Set_Pwm_Motor2(5000);
				break;
			case PSB_PAD_DOWN:
				Set_Pwm_Motor1(-5000); //�������
				Set_Pwm_Motor2(-5000);
				break;
			case PSB_PAD_LEFT:
				CPWM[1] = 1000; //��תһ���Ƕ�
				break;
			case PSB_PAD_RIGHT:
				CPWM[1] = 1500 + LX_AD * 1000 / 255; //��ת���ʽǶ�(���м俪ʼ)
				break;
			case PSB_TRIANGLE:
				break;
			case PSB_CROSS:
				break;
			case PSB_PINK:
				break;
			case PSB_CIRCLE:
				break;
			case PSB_L1:
				break;
			case PSB_L2:
				break;
			case PSB_R1:
				break;
			case PSB_R2:
				break;
			default:
				break;
			}
			/******
			һ�δ�����ҡ��ֵ
					LX_AD 0-255 ��ҡ��x��
					LY_AD 0-255 ��ҡ��y��
					RX_AD 0-255 ��ҡ��x��
					RY_AD 0-255 ��ҡ��y��
			ת�亯��
				CPWM[1]=1500;�����루��ֵ��Χ500-2500��
			ǰ������
					Set_Pwm_Motor1(0);���ֵ����Ϊ7000
					Set_Pwm_Motor2(0);
			******/
		}
		else // PS2Ϊ����ģʽ
		{
			switch (key) //��Ϊ�ο�����һ��Ҫ������if��Ҳ��
			{
			case PSB_PAD_UP:
				break;
			case PSB_PAD_DOWN:
				break;
			case PSB_PAD_LEFT:
				break;
			case PSB_PAD_RIGHT:
				break;
			case PSB_TRIANGLE:
				//�˶�ģʽ=Բ��
				Set_Pwm_Motor1(5000); //�������
				Set_Pwm_Motor2(5000);
				CPWM[1] = 2300; //��תһ���Ƕ�
				break;
			case PSB_CROSS:
				//�˶�ģʽ=��ֹ
				Set_Pwm_Motor1(0); //�������
				Set_Pwm_Motor2(0);
				CPWM[1] = 1500; //��תһ���Ƕ�
				break;
			case PSB_SQUARE:
				break;
			case PSB_CIRCLE:
				//�˶�ģʽ=����(�����趨)
				while (1)
				{
					int angle = (int)(1000 * sin(i * 3.14159 / 180)) + 1500; // ����ǰ�ֵ�ת��Ƕ�
					CPWM[1] = angle;										 // ��ת��Ƕȴ�����̿��ƺ���
					Set_Pwm_Motor1(2500);
					Set_Pwm_Motor2(2500);
					key = PS2_DataKey();
					if (key == PSB_CROSS)
						break;
					// ����ǰ�����Ǻ��ˣ������ƽǶ�
					Delay_ms(5); // �źż��5ms����ʱǰ��ת������ԼΪ1.8s������ת��һ�η���ԼΪ5s
					i++;
				}
				break;
			case PSB_L1:
				break;
			case PSB_L2:
				break;
			case PSB_R1:
				break;
			case PSB_R2:
				break;
			default:
				break;
			}
		}
	}
}
