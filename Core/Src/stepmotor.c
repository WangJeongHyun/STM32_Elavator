#include "main.h"
#include "button.h"

void set_rpm(int rpm);
void stepmotor_main(void);
void stepmotor_drive(int step);

extern void delay_us(unsigned long us);
extern volatile int floor_state;
//extern init_dotmatrix();

volatile int floor_target = 1;

static int step = 0;
// RPM : 분당 회전수
// 1분 = 60초 = 60,000,000us
// 1,000,000us = 1초
// 4096 step = 360도
// 4096/(8*0.7)=512 sequence = 360도  :: 8은 8개의 상 그리고 그게 0.7 도씩 움직임
// 1 sequence (8step) :0.70312도
// 0.70312 * 512 sequence = 360도

/*set rpm(13)
 * 1분 = 60,000,000us -> 60,000,000us / 4096 =rpm
 * 1126( 1step idle time) * 4096 = 4,612,096us
 * 								=4,612ms
 * 								=4.6sec
 * 	60초 / 4.6 ==> 초당 13회전
 * 	시계 1회 반시계 1회
 * 	*/
void set_rpm(int rpm)
{
	delay_us(60000000/4096/rpm);
	// 최대 speed(13) 기준 : delay_us(1126)
}

void stepmotor_direction(int direction)
{

	//위로
	if (direction == 1)
	{
		set_rpm(13);
		step++;
		if (step >= 8) step = 0;
		step %= 8;
		//도착시 정지
		if(floor_state == 4)
		{
			direction = 0;
		}
	}
	//아래로
	else if (direction == 2)
	{
		set_rpm(13);
		step--;
		if (step < 0) step = 7;
		step %= 8;
		//도착시 정지
		if(floor_state == 1)
		{

			direction = 0;
		}
	}
	//정지
	if (direction == 0)
	{
		step = -1;
	}

	stepmotor_drive(step);

}
int current_direction =-1;
int btn1_flag=0;
int btn2_flag=0;
int btn3_flag=0;
int btn4_flag=0;


void stepmotor_main(void)
{
//	printf("floor_state : %d \n",floor_state);
//	printf("floor_target : %d \n",floor_target);

	//도착하면 스탑
	if(floor_state == floor_target) current_direction=0;

	//1층에 대한 logic
	if (get_button(GPIOE, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		btn1_flag++;
		btn1_flag = btn1_flag%2;

		if(btn1_flag==1)
		{
			floor_target = 1;
			if(floor_state < floor_target) current_direction=1;
			else if(floor_state > floor_target) current_direction=2;
		}
		else
		{
			floor_target = 0;
			current_direction=0;
			//취소
		}
	}

	//2층에 대한 logic
	if (get_button(GPIOE, BUTTON1_Pin, 1) == BUTTON_PRESS)
	{
		btn2_flag++;
		btn2_flag = btn2_flag%2;

		if(btn2_flag==1)
		{
			floor_target = 2;
			if(floor_state < floor_target) current_direction=1;
			else if(floor_state > floor_target) current_direction=2;
		}
		else
		{
			floor_target = 0;
			current_direction=0;
			//취소
		}
	}
	//3층에 대한 logic
	else if (get_button(GPIOE, BUTTON2_Pin, 2) == BUTTON_PRESS)
	{
		btn3_flag++;
		btn3_flag = btn3_flag%2;

		if(btn3_flag==1)
		{
			floor_target = 3;
			if(floor_state < floor_target) current_direction=1;
			else if(floor_state > floor_target) current_direction=2;
		}
		else
		{
			floor_target = 0;
			current_direction=0;
			//취소
		}
	}

	//4층에 대한 logic
	else if (get_button(GPIOE, BUTTON3_Pin, 3) == BUTTON_PRESS)
	{
		btn4_flag++;
		btn4_flag = btn4_flag%2;

		if(btn4_flag==1)
		{
			floor_target = 4;
			if(floor_state < floor_target) current_direction=1;
			else if(floor_state > floor_target) current_direction=2;
		}
		else
		{
			floor_target = 0;
			current_direction=0;
			//취소
		}
	}

	stepmotor_direction(current_direction);

}

void stepmotor_drive(int step)
{
	switch(step){
	case 0:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
	case 8:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;

	}

}
