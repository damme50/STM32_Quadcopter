#include "BlueTooth.h" 	
#include "control.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "ucos_ii.h"
#define USART3_REC_LEN  			200 
#define USART3_TX_LEN  			200 
//����3�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   
u8 USART3_RX_BUF[USART3_REC_LEN]={0};     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART3_TX_BUF[USART3_TX_LEN]={0};
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART3_RX_STA=0;       //����״̬���	
u8 Res;//�ֽڽ���

//��Ϣ����
u8 ARMED,pidset,send_angle;
//PID���û���
PID P;



void BT_Send(S_FLOAT_XYZ   *angleTX)
{
	printf("pitch %f;roll %f;yaw %f\n",angleTX->Y,angleTX->X,angleTX->Z);
}
void BLUETOOTH_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
		/* ���ô���3 ��USART3�� ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_USART3 ,ENABLE); 
	/*����GPIO�˿�����*/
  /* ���ô���3 ��USART3 Tx (PD8)��*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);    
	/* ���ô���3 USART3 Rx (PD9)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	  
		/* ����3����ģʽ��USART3 mode������ */
	USART_InitStructure.USART_BaudRate = 9600;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure); 

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�ж�����
	
	USART_Cmd(USART3, ENABLE);//ʹ�ܴ���
}

void USART3_NVIC_Config(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}



void USART3_IRQHandler(void)
{
	//����ϵͳ�ж� ��ֹǶ������     �ص���
	OSIntEnter();
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x23��β)
		{
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
		
		if((USART3_RX_STA&0X8000)==0)//����δ���
			{
				if(Res=='#'){USART3_RX_STA|=0X8000;Command_Read();}
				else
					{
					USART3_RX_BUF[USART3_RX_STA++]=Res;
					if(USART3_RX_STA>(USART3_REC_LEN-1)){USART3_RX_STA=0;}//�������ݴ���,���¿�ʼ����	  
					}		 
			}   		 
		}
		OSIntExit();		
}

void Command_Read(){
	if(USART3_RX_STA&0x8000){
       if(strcmp((const char*)USART3_RX_BUF,"Yes")==0)u3_printf("copy");
			 else if(strcmp((const char*)USART3_RX_BUF,"STOP")==0)
			 {
			 		ARMED=0;
				  u3_printf("Stop Motor");
			 }
			 else if(strcmp((const char*)USART3_RX_BUF,"START")==0)
			 {
					ARMED=1;
				  u3_printf("Start Motor");
			 }
			 else if(strcmp((const char*)USART3_RX_BUF,"ANGLE")==0)
							{send_angle=1;}
			 else 
			 {
				u3_printf("undef info");
			 }
			u3_printf("\r\n");
			USART3_RX_STA=0;
			RX_BUF_Clear();
	}
}

void RX_BUF_Clear(){
	int i;
	for(i=0;i<USART3_REC_LEN;i++){USART3_RX_BUF[i]=0;}
}

void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}





