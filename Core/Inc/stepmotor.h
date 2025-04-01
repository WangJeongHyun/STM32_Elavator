#ifndef _STEPMOTOR_H_
#define _STEPMOTOR_H_

#include "main.h"
#include "variable.h"
#include "timer_management.h"

void control_stepmotor(uint8_t curr_status);
void drive_stepmotor(int step);
void set_RPM(int rpm);

#endif /*_STEPMOTOR_H_*/
