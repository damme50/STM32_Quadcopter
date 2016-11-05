#include "motor.h"
#include "includes.h"
int16_t MOTO1_PWM = 0;
int16_t MOTO2_PWM = 0;
int16_t MOTO3_PWM = 0;
int16_t MOTO4_PWM = 0;

/*PWM ˢ��*/
void Moto_PwmRflash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
{		
	if(MOTO1_PWM>Moto_PwmMax)	MOTO1_PWM = Moto_PwmMax;
	if(MOTO2_PWM>Moto_PwmMax)	MOTO2_PWM = Moto_PwmMax;
	if(MOTO3_PWM>Moto_PwmMax)	MOTO3_PWM = Moto_PwmMax;
	if(MOTO4_PWM>Moto_PwmMax)	MOTO4_PWM = Moto_PwmMax;
	if(MOTO1_PWM<0)	MOTO1_PWM = 0;
	if(MOTO2_PWM<0)	MOTO2_PWM = 0;
	if(MOTO3_PWM<0)	MOTO3_PWM = 0;
	if(MOTO4_PWM<0)	MOTO4_PWM = 0;
	
	TIM4->CCR1 = MOTO1_PWM;
	TIM4->CCR2 = MOTO2_PWM;
	TIM4->CCR3 = MOTO3_PWM;
	TIM4->CCR4 = MOTO4_PWM;
	
	
	
//	TIM4->CCR1 = MOTO1_PWM;
//	TIM4->CCR2 = MOTO2_PWM;
//	TIM4->CCR3 = MOTO3_PWM;
//	TIM4->CCR4 = MOTO4_PWM;
	//u3_printf("%d\n", MOTO3_PWM);
}

void Motor_GPIO_init()
{
	GPIO_InitTypeDef GPIO_pwm;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_pwm.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_pwm.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_pwm);
}

void Motor_TIM_init(){
	TIM_TimeBaseInitTypeDef TIM_tb4;
	TIM_OCInitTypeDef TIM_oc4;

	u16 CCR1_Val = 20; 	//���ó�ʼ���ߵ�ƽΪ2ms
	u16 CCR2_Val = 20;
	u16 CCR3_Val = 20;
	u16 CCR4_Val = 20;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//������ʱ��4��ʱ��
	
	TIM_tb4.TIM_Period = 20000-1;  //��PWM��������Ϊ20ms
	TIM_tb4.TIM_Prescaler = 72-1;//��Ƶ��ĵ�λ��0.1ms
	TIM_tb4.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_tb4.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_tb4);
	
	TIM_oc4.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_oc4.TIM_OutputState = TIM_OutputState_Enable;
	TIM_oc4.TIM_Pulse = CCR1_Val;
	TIM_oc4.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM_oc4);//��ʼ��ͨ��1
	
	TIM_oc4.TIM_OutputState = TIM_OutputState_Enable;
	TIM_oc4.TIM_Pulse = CCR2_Val;
	TIM_OC2Init(TIM4, &TIM_oc4);//��ʼ��ͨ��2
	
	TIM_oc4.TIM_OutputState = TIM_OutputState_Enable;
	TIM_oc4.TIM_Pulse = CCR3_Val;
	TIM_OC3Init(TIM4, &TIM_oc4);//��ʼ��ͨ��3
	
	TIM_oc4.TIM_OutputState = TIM_OutputState_Enable;
	TIM_oc4.TIM_Pulse = CCR4_Val;
	TIM_OC4Init(TIM4, &TIM_oc4);//��ʼ��ͨ��4
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ���ĸ�ͨ��
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);//ʹ��TIM4���ؼĴ���ARR
	
	TIM_Cmd(TIM4, ENABLE);//ʹ�ܶ�ʱ��4

}



void Motor_PWM_ALL(int p){
	TIM4->CCR1=1000+1000*p/100;
	TIM4->CCR2=1000+1000*p/100;
	TIM4->CCR3=1000+1000*p/100;
	TIM4->CCR4=1000+1000*p/100;
}
void Motor_PWM_SEPRATE(int p1, int p2, int p3, int p4){
	TIM4->CCR1=1000+1000*p1/100;
	TIM4->CCR2=1000+1000*p2/100;
	TIM4->CCR3=1000+1000*p3/100;
	TIM4->CCR4=1000+1000*p4/100;
}
