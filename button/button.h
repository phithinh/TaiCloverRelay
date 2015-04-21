/*
 * button.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Phi Thinh
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "key.h"

typedef enum{
	BUTTON_OP_INIT = 0,
	BUTTON_OP_Year,
	BUTTON_OP_Month,
	BUTTON_OP_Date,
	BUTTON_OP_Day,
	BUTTON_OP_Hour,
	BUTTON_OP_Min,
	BUTTON_OP_Sec,
	BUTTON_OP_AM,
	BUTTON_OP_IDEL,
}BUTTON_OPTION_MODE_DEF;

void Button_Option_Task(void);
BUTTON_OPTION_MODE_DEF Button_getSta(void);

#endif /* BUTTON_H_ */
