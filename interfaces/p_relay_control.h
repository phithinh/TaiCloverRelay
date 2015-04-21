/*
 * p_relay_control.h
 *
 *  Created on: Mar 29, 2015
 *      Author: phi thinh
 */

#ifndef P_RELAY_CONTROL_H_
#define P_RELAY_CONTROL_H_


typedef struct{
	union{
		unsigned short Val_uw;
		struct{
			unsigned short Num_1: 1;
			unsigned short Num_2: 1;
			unsigned short Num_3: 1;
			unsigned short Num_4: 1;
			unsigned short Num_5: 1;
			unsigned short Num_6: 1;
			unsigned short Num_7: 1;
			unsigned short Num_8: 1;
			unsigned short Num_9: 1;
			unsigned short Num_10: 1;
			unsigned short Num_11: 1;
			unsigned short Num_12: 1;
			unsigned short Num_13: 1;
			unsigned short Num_14: 1;
			unsigned short Num_15: 1;
			unsigned short Num_16: 1;
		}Relay_st;
	}Relay_status_st;
	struct{
		unsigned short Overtime_1: 1;
		unsigned short Overtime_2: 1;
		unsigned short reserve: 14;
	}Overtime_status_st;
}p_relay_control_tdf;


#endif /* P_RELAY_CONTROL_H_ */
