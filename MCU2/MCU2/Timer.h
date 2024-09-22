/*
 * Timer.h
 *
 * Created: 9/29/2023 3:08:51 PM
 *  Author: a3abd
 */ 


#ifndef TIMER_H_
#define TIMER_H_


void Timer0_Fast_PWM_INIT();
void Timer2_Servo_Motor_INIT();
void Timer0_Set_Duty_Cycle(float DC);
void Timer2_Set_Duty_Cycle(float DC);

extern volatile int count;


#endif /* TIMER_H_ */