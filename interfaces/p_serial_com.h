/*
 * p_serial_com.h
 *
 *  Created on: Mar 29, 2015
 *      Author: phi thinh
 */

#ifndef P_SERIAL_COM_H_
#define P_SERIAL_COM_H_

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
	}Requested_relay_st;
	unsigned char requested_flag_b;
}p_serial_com_tdf;


#endif /* P_SERIAL_COM_H_ */
