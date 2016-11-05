#include "Rev.h"
RC_GETDATA Rc_Get;
u8 TIM2CH1_CAPTURE_STA = 0;	//ͨ��1���벶���־������λ�������־����6λ�������־		
u16 TIM2CH1_CAPTURE_UPVAL;
u16 TIM2CH1_CAPTURE_DOWNVAL;

u8 TIM2CH2_CAPTURE_STA = 0;	//ͨ��2���벶���־������λ�������־����6λ�������־		
u16 TIM2CH2_CAPTURE_UPVAL;
u16 TIM2CH2_CAPTURE_DOWNVAL;

u8 TIM2CH3_CAPTURE_STA = 0;	//ͨ��3���벶���־������λ�������־����6λ�������־		
u16 TIM2CH3_CAPTURE_UPVAL;
u16 TIM2CH3_CAPTURE_DOWNVAL;

u8 TIM2CH4_CAPTURE_STA = 0;	//ͨ��1���벶���־������λ�������־����6λ�������־		
u16 TIM2CH4_CAPTURE_UPVAL;
u16 TIM2CH4_CAPTURE_DOWNVAL;

u32 tempup1 = 0;	//�����ܸߵ�ƽ��ʱ��
u32 tempup2 = 0;	//�����ܸߵ�ƽ��ʱ��
u32 tempup3 = 0;	//�����ܸߵ�ƽ��ʱ��
u32 tempup4 = 0;	//�����ܸߵ�ƽ��ʱ��
u32 tim2_T1;
u32 tim2_T2;
u32 tim2_T3;
u32 tim2_T4;

int pwmout1, pwmout2, pwmout3, pwmout4; 				//���ռ�ձ�


void Rev_GPIO_init(){
	GPIO_InitTypeDef GPIO_tim;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_tim.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_tim.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_tim.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA,&GPIO_tim);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3); //����
}

void Rev_NVIC_TIM_init(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM2_ICInitStructure;
	NVIC_InitTypeDef  NVIC_TIM2;
	
	NVIC_TIM2.NVIC_IRQChannel = TIM2_IRQn;                     
  NVIC_TIM2.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_TIM2.NVIC_IRQChannelSubPriority = 1;
  NVIC_TIM2.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_TIM2);
	
		//��ʼ����ʱ��2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = 0xffff; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 	//Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM2���벶����� ͨ��1
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);

	//��ʼ��TIM2���벶����� ͨ��2
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);

	//��ʼ��TIM2���벶����� ͨ��3
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);

	//��ʼ��TIM2���벶����� ͨ��4
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);

	TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4,
			ENABLE);   //����������жϣ�����CC1IE,CC2IE,CC3IE,CC4IE�����ж�	

	TIM_Cmd(TIM2, ENABLE); 		//buʹ�ܶ�ʱ��2
	
}


void TIM2_IRQHandler(void)
{
	
		OSIntEnter();


if ((TIM2CH1_CAPTURE_STA & 0X80) == 0) 		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_CC1); 		//����жϱ�־λ
			if (TIM2CH1_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM2CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM2);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM2CH1_CAPTURE_DOWNVAL < TIM2CH1_CAPTURE_UPVAL)
				{
					tim2_T1 = 65535;
				}
				else
					tim2_T1 = 0;
				tempup1 = TIM2CH1_CAPTURE_DOWNVAL - TIM2CH1_CAPTURE_UPVAL
						+ tim2_T1;		//�õ��ܵĸߵ�ƽ��ʱ��
				pwmout4 = tempup1;		//�ܵĸߵ�ƽ��ʱ��
				TIM2CH1_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM2CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM2);		//��ȡ����������
				TIM2CH1_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM2CH2_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)		//����2���������¼�
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);		//����жϱ�־λ
			if (TIM2CH2_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM2CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM2);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM2CH2_CAPTURE_DOWNVAL < TIM2CH2_CAPTURE_UPVAL)
				{
					tim2_T2 = 65535; 
				}
				else
					tim2_T2 = 0;
				tempup2 = TIM2CH2_CAPTURE_DOWNVAL - TIM2CH2_CAPTURE_UPVAL
						+ tim2_T2;		//�õ��ܵĸߵ�ƽ��ʱ��
				pwmout3 = tempup2;		//�ܵĸߵ�ƽ��ʱ��
				TIM2CH2_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC2PolarityConfig(TIM2, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM2CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM2);		//��ȡ����������
				TIM2CH2_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC2PolarityConfig(TIM2, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM2CH3_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)		//����3���������¼�
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);		//����жϱ�־λ
			if (TIM2CH3_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM2CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM2);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM2CH3_CAPTURE_DOWNVAL < TIM2CH3_CAPTURE_UPVAL)
				{
					tim2_T3 = 65535;
				}
				else
					tim2_T3 = 0;
				tempup3 = TIM2CH3_CAPTURE_DOWNVAL - TIM2CH3_CAPTURE_UPVAL
						+ tim2_T3;		//�õ��ܵĸߵ�ƽ��ʱ��
				pwmout2 = tempup3;		//�ܵĸߵ�ƽ��ʱ��
				TIM2CH3_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC3PolarityConfig(TIM2, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM2CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM2);		//��ȡ����������
				TIM2CH3_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC3PolarityConfig(TIM2, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM2CH4_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)		//����4���������¼�
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);		//����жϱ�־λ
			if (TIM2CH4_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM2CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM2);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM2CH4_CAPTURE_DOWNVAL < TIM2CH4_CAPTURE_UPVAL)
				{
					tim2_T4 = 65535;
				}
				else
					tim2_T4 = 0;
				tempup4 = TIM2CH4_CAPTURE_DOWNVAL - TIM2CH4_CAPTURE_UPVAL
						+ tim2_T4;		//�õ��ܵĸߵ�ƽ��ʱ��
				pwmout1 = tempup4;		//�ܵĸߵ�ƽ��ʱ��
				TIM2CH4_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC4PolarityConfig(TIM2, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM2CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM2);		//��ȡ����������
				TIM2CH4_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC4PolarityConfig(TIM2, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}
	OSIntExit();
}