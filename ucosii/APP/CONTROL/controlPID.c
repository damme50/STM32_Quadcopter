#include "control.h"
#include "Rev.h"
#include "IMU.h"
#include "includes.h"

PID PID_ROL,PID_PIT,PID_YAW;

float Pitch_i,Roll_i,Yaw_i;                                   //������
float Pitch_old,Roll_old,Yaw_old;                 //�Ƕȱ���
float Pitch_d,Roll_d,Yaw_d;          //΢����

void Pid_init(void);

void CONTROL(float rol, float pit, float yaw)
{
	
  u16 moto1=0,moto2=0,moto3=0,moto4=0;
	
	  ////////////////////////�⻷�ǶȻ�(PID)///////////////////////////////
	  Pitch_i+=pit;
	  Roll_i+=rol;
		Yaw_i+=yaw;

//-------------Pitch�����޷�----------------//
  if(Pitch_i>300) Pitch_i=300;
  else if(Pitch_i<-300) Pitch_i=-300;
//-------------Pitch΢��--------------------//
  Pitch_d=pit-Pitch_old;
	Pitch_old=pit;
	//-------------Pitch  PID-------------------//
  PID_PIT.shell_out = PID_PIT.shell_P*pit + PID_PIT.shell_I*Pitch_i + PID_PIT.shell_D*Pitch_d;
	
//-------------rol�����޷�----------------//
  if(Roll_i>300) Roll_i=300;
  else if(Roll_i<-300) Roll_i=-300;
//-------------rol΢��--------------------//
  Roll_d=rol-Roll_old;
	Roll_old=rol;
	//-------------rol  PID-------------------//
  PID_ROL.shell_out = PID_ROL.shell_P*rol + PID_ROL.shell_I*Roll_i + PID_ROL.shell_D*Roll_d;
	
	//-------------Yaw�����޷�----------------//
  if(Yaw_i>300) Yaw_i=300;
  else if(Yaw_i<-300) Yaw_i=-300;
//-------------Pitch΢��--------------------//
  Yaw_d=yaw-Yaw_old;
	Yaw_old=yaw;
	//-------------Pitch  PID-------------------//
  PID_YAW.shell_out = PID_YAW.shell_P*yaw + PID_YAW.shell_I*Yaw_i + PID_YAW.shell_D*Yaw_d;

    ////////////////////////�ڻ����ٶȻ�(PD)///////////////////////////////  
		//e��(t)=AngelPIDOut(t) - ʵ�ʽ��ٶ� Ϊʲô+��Ϊ��������
		PID_PIT.core_out=PID_PIT.core_P* (PID_PIT.shell_out + MPU6050_GYRO_LAST.Y * 3.5)+PID_PIT.core_D* (MPU6050_GYRO_LAST.Y   - GYRO_RADIAN_OLD.Y);
		
		PID_ROL.core_out=PID_ROL.core_P* (PID_ROL.shell_out + MPU6050_GYRO_LAST.X * 3.5)+PID_ROL.core_D* (MPU6050_GYRO_LAST.X   - GYRO_RADIAN_OLD.X);
		
		PID_YAW.core_out=PID_YAW.core_P* (PID_YAW.shell_out + MPU6050_GYRO_LAST.Z * 3.5)+PID_YAW.core_D* (MPU6050_GYRO_LAST.Z   - GYRO_RADIAN_OLD.Z);

		GYRO_RADIAN_OLD=MPU6050_GYRO_LAST;
		
//MOTOR
	if(Rc_Get.THROTTLE>1000)
	{
		//x ģʽ
		moto3 = Rc_Get.THROTTLE - 500 - PID_ROL.core_out - PID_PIT.core_out + PID_YAW.core_out;
		moto4 = Rc_Get.THROTTLE - 500 + PID_ROL.core_out - PID_PIT.core_out - PID_YAW.core_out;
		moto1 = Rc_Get.THROTTLE - 500 + PID_ROL.core_out + PID_PIT.core_out + PID_YAW.core_out;
		moto2 = Rc_Get.THROTTLE - 500 - PID_ROL.core_out + PID_PIT.core_out - PID_YAW.core_out;
		//+ ģʽ
//		moto3 = Rc_Get.THROTTLE - 500 - PID_PIT.core_out + PID_YAW.core_out;
//		moto4 = Rc_Get.THROTTLE - 500 - PID_ROL.core_out - PID_YAW.core_out;
//		moto1 = Rc_Get.THROTTLE - 500 + PID_PIT.core_out + PID_YAW.core_out;
//		moto2 = Rc_Get.THROTTLE - 500 + PID_ROL.core_out - PID_YAW.core_out;
	}
	else
	{
		moto1 = 0;
		moto2 = 0;
		moto3 = 0;
		moto4 = 0;
	}
	if(ARMED){	
		Moto_PwmRflash(moto1,moto2,moto3,moto4);
	//printf("%d\t%d\t%d\t%d\n",moto1,moto3,moto2,moto4);
	//OSTimeDlyHMSM(0,0,0,300);
	}
	else{
	Moto_PwmRflash(0,0,0,0);
	}
}
/*************************************************
Description:��ʼ��PID����
**************************************************/
void Pid_init(void)
{
	
	PID_PIT.shell_P=280;//30 140
	PID_PIT.shell_I=0;//
	PID_PIT.shell_D=0;//
/*********************************/
	PID_ROL.shell_P=250;//30
	PID_ROL.shell_I=0;//10                 
	PID_ROL.shell_D=0;//0.08
/*********************************/
	PID_YAW.shell_P=1.5;//10;//30
	PID_YAW.shell_I=0;//10                 
	PID_YAW.shell_D=0;//0.08;//0.08
	
//float Pitch_core_kp=0.040;
//float Pitch_core_kd=0.008;////0.007;//0.07;
	PID_PIT.core_P=0.040;
	PID_PIT.core_D=0.002;////0.007;//0.07;

	PID_ROL.core_P=0.040;//;
	PID_ROL.core_D=0.002;////0.007;//06;//0.07;

  PID_YAW.core_P=0.046;//;
  PID_YAW.core_D=0.012;////0.007;//06;//0.07;
}
