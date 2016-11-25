#include "includes.h"
u8 SYS_INIT_OK = 0;
extern u8 debug;
extern float zoffset;

void BSP_Init()
{
	int i;
	float temp;
	
	/*************************
	
	��������Ӳ����ʼ��
	
	**************************/
	
	/* ����ϵͳʱ��Ϊ 72M  3.5���������ļ��ѵ���*/
	SysTick_init(); /* ��ʼ����ʹ�� SysTick ��ʱ�� */
	tim7_init();/*��ʼ����ʹ��tim7*/
	LED_GPIO_Config(); /* LED �˿ڳ�ʼ�� ָʾ����*/

	
	//����1
	USART1_Config();
	USART1_NVIC_Config();
	
	//��������3
	BLUETOOTH_GPIO_Config();
	USART3_NVIC_Config();

	//���ջ�tim2
	Rev_GPIO_init();
	Rev_NVIC_TIM_init();
	
	//���
	Motor_GPIO_init();
	Motor_TIM_init();

	Motor_PWM_ALL(100);
	delay_ms(2000);
	Motor_PWM_ALL(0);
	delay_ms(2000);
	
	//PID
	Pid_init();
	
	//I2C
	I2C_GPIO_Configuration();
	
	//gy86 MPU6050 HMC5883L
	MPU6050_Init(); 
	Init_HMC5883L();

	printf("bsp init OK next\n");
	/****************************************/

		
		
	

	/*********************
	
	��һ������Ҫ��Ϊ���ȶ�����ĽǶȣ��ⶨƫ�ƣ�����Z��Ƕȵ�0
	
	**********************/
	
	GYRO_OFFSET_OK=0; 
	ACC_OFFSET_OK=0;
	debug=0;
	
  i=0;
	while(i<1500)
	{
		Prepare_Data();
		Read_HMC5883L();
		Get_Attitude();
		i++;
	}
	
	i=0;
	while(i<10)
	{
		Prepare_Data();
		Read_HMC5883L();
		Get_Attitude();
		
		temp+=Q_ANGLE.Z;
		i++;
	}
	 zoffset=temp/10;
	
	debug=1;
	/**********************/
	
	
	printf("data init OK\n");
	u3_printf("bsp  and  data init OK\n");

	
	
	
	/***************
	Ƭ����Դ�����ʼ����PID���ݴ�ȡ����
	****************/
	//��������ͳ�ʼ��
	FLASH_Unlock();//FLASH����
	EE_Init();
	
	
	printf("flash init OK\n");
	u3_printf("flash init OK \n");
	
//	EE_READ_ACC_OFFSET();
//	EE_READ_GYRO_OFFSET();

		printf("data init OK\n");

		EE_READ_PID_Send();
		//�Ѿ������Գɹ���ȡ������������
		printf("pid test end OK\n");
		u3_printf("pid test end OK\n");
}
	


void SysTick_init(void)
{
 SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);//��ʼ����ʹ�� SysTick ��ʱ�� 3.5��궨�岻ͬ
}


