#include "includes.h"

// ����ͨ������50HZ 
// ���ȼ�5
extern OS_EVENT * ANGLE;  //�ź���
extern INT8U errANGLE;
extern int debug;
S_FLOAT_XYZ   *angleTX=&Q_ANGLE;
extern u8 ARMED,pidset,send_angle;
void Task_BlueTooth(void*p_arg)
{
	(void)p_arg;
	u3_printf("\r\n Bluetooth task succeed!\r\n");
	
	while(1)
	{
		if(debug==1) //&& send_angle==1
		{
			//�Ӹ��ź���
			OSMutexPend (ANGLE,0, &errANGLE);
			BT_Send(angleTX);
			OSMutexPost (ANGLE);
		}
		if(pidset>0)
		{
		 pidset=0;
		}
		//BT_Send(angleTX);
		OSTimeDlyHMSM(0,0,1,0);
	}
}


