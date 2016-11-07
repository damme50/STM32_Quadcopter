#ifndef __BSP_H
#define __BSP_H

#include "bsp_led.h" //LED ��������
#include "BlueTooth.h" 	//����ͨ�ź���
//#include "GPS.h"//gps
#include "i2cdev.h"//i2c
#include "motor.h"//���
#include "IMU.h"//�˲��㷨
#include "MPU6050.h"//mpu6050
#include "HMC5883L.h"//hmc5883l
#include "Rev.h"//������
#include "tim7.h"//TIM7��ʱ��
#include "usart1.h"//����1
#include "control.h"
#include "eeprom.h"
#include "flash.h"

void SysTick_init(void);
void BSP_Init(void);

#endif // __BSP_H
