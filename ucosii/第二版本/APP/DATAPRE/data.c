#include "includes.h"


//��̬��������250HZ
//���ȼ�6
void Task_atttitude_computation(void *p_arg)
{
	int i;
  float x,y,magn_x,magn_y;
	//float z,magn_z;
  (void)p_arg;			
	while (1)
 {

	 
	 //����̬���Ʒ�����Ϣ@@@
	 //OSQPost(PIDQ,  void * );
	 
	 
  OSTimeDlyHMSM(0, 0,0,4);
 }
}