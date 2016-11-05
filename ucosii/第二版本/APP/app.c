#include "includes.h"

/********************��������ջ****************************/
__align(8) OS_STK task_bluetooth_stk[TASK_STK_SIZE];
__align(8) OS_STK task_atttitude_computation_stk[TASK_STK_SIZE];
__align(8) OS_STK task_atttitude_pid_stk[TASK_STK_SIZE];
__align(8) OS_STK task_gps_stk[TASK_STK_SIZE];

//OS_STK task_led2_stk[TASK_LED2_STK_SIZE];
//OS_STK task_led3_stk[TASK_LED3_STK_SIZE]; 



 //������
void Task_Start(void *p_arg)
{
 (void)p_arg;
	
	//������������@@@
	OSTaskCreate(Task_BlueTooth,(void *)0, //��������ͨ������
	&task_bluetooth_stk[TASK_STK_SIZE-1], TASK_BLUETOOTH_PRIO);
	
	OSTaskCreate(Task_atttitude_computation,(void *)0, //������̬��������
	&task_atttitude_computation_stk[TASK_STK_SIZE-1], TASK_ATTITUDE_COMPUTATION_PRIO);
	
	OSTaskCreate(Task_atttitude_pid,(void *)0, //������̬��������
	&task_atttitude_pid_stk[TASK_STK_SIZE-1], TASK_ATTITUDE_PID_PRIO);
	while(1){
	OSTimeDlyHMSM(0,0,0,1000);
	
	}
	
}

