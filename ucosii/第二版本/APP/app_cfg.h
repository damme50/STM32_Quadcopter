#ifndef __APP_CFG_H__
#define __APP_CFG_H__


/*******************�����������ȼ�*******************/
#define STARTUP_TASK_PRIO 7
#define TASK_BLUETOOTH_PRIO 6
#define TASK_ATTITUDE_COMPUTATION_PRIO 5
#define TASK_ATTITUDE_PID_PRIO 8
#define TASK_GPS_PRIO 9

////DEBUG
//#define TASK_LED2_PRIO 9
//#define TASK_LED3_PRIO 10
/************����ջ��С����λΪ OS_STK ��************/
#define STARTUP_TASK_STK_SIZE 256
#define TASK_STK_SIZE 512
//#define TASK_LED2_STK_SIZE 80
//#define TASK_LED3_STK_SIZE 80
#endif
