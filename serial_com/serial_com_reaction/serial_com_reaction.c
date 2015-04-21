/*
 * serial_com_reaction.c
 *
 *  Created on: Mar 31, 2015
 *      Author: phi thinh
 */

#include "../serial_com_appl.h"
#include "../../interfaces/interfaces.h"

#define SERIAL_COM_MAX_NUM_RELAY 16
#define SERIAL_COM_STARTED_IDX_RELAY 2

unsigned short serial_com_relay_adapt [] = {Y1  ,
											Y2  ,
											Y3  ,
											Y4  ,
											Y5  ,
											Y6  ,
											Y7  ,
											Y8  ,
											Y9  ,
											Y10 ,
											Y11 ,
											Y12 ,
											Y13 ,
											Y14 ,
											Y15 ,
											Y16 ,
};

void serial_com_send_ok_v(void)
{
	serial_com_sending_context_st.data_ub[0] = '<';
	serial_com_sending_context_st.data_ub[1] = 'o';
	serial_com_sending_context_st.data_ub[2] = 'k';
	serial_com_sending_context_st.data_ub[3] = '>';
	serial_com_sending_context_st.data_ub[4] = 0;
	serial_com_sending_context_st.sent_length_ub = 4;
}
void serial_com_send_nok_v(void){
	serial_com_sending_context_st.data_ub[0] = '<';
	serial_com_sending_context_st.data_ub[1] = 'n';
	serial_com_sending_context_st.data_ub[2] = 'o';
	serial_com_sending_context_st.data_ub[3] = 'k';
	serial_com_sending_context_st.data_ub[4] = '>';
	serial_com_sending_context_st.data_ub[5] = 0;
	serial_com_sending_context_st.sent_length_ub = 5;
}
void serial_com_set_relay_state_v(void){
	unsigned short t_requested_relay_uw = 0;
	unsigned char t_index_ub;
	for(t_index_ub = 0; t_index_ub<SERIAL_COM_MAX_NUM_RELAY;t_index_ub++){
		if (serial_com_receiving_context_st.data_ub[t_index_ub+SERIAL_COM_STARTED_IDX_RELAY] == '1'){
			t_requested_relay_uw |= serial_com_relay_adapt[t_index_ub];
		}
		l_serial_com_requested_relay_uw = t_requested_relay_uw;
		l_serial_com_requested_relay_flag_b = 1;
	}
}
void serial_com_send_relay_state_v(void){
	serial_com_sending_context_st.data_ub[0] = '<';
	serial_com_sending_context_st.data_ub[1] = 's';
	serial_com_sending_context_st.data_ub[2] = 't';
	serial_com_sending_context_st.data_ub[3] = 'a';
	serial_com_sending_context_st.data_ub[4] = 't';
	serial_com_sending_context_st.data_ub[5] = 'u';
	serial_com_sending_context_st.data_ub[6] = 's';
	serial_com_sending_context_st.data_ub[7] = ' ';
	serial_com_sending_context_st.data_ub[8] = 	((relay_control_st.Relay_status_st.Val_uw & Y1)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[9] = 	((relay_control_st.Relay_status_st.Val_uw & Y2)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[10] = ((relay_control_st.Relay_status_st.Val_uw & Y3)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[11] = ((relay_control_st.Relay_status_st.Val_uw & Y4)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[12] = ((relay_control_st.Relay_status_st.Val_uw & Y5)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[13] = ((relay_control_st.Relay_status_st.Val_uw & Y6)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[14] = ((relay_control_st.Relay_status_st.Val_uw & Y7)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[15] = ((relay_control_st.Relay_status_st.Val_uw & Y8)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[16] = ((relay_control_st.Relay_status_st.Val_uw & Y9)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[17] = ((relay_control_st.Relay_status_st.Val_uw & Y10)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[18] = ((relay_control_st.Relay_status_st.Val_uw & Y11)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[19] = ((relay_control_st.Relay_status_st.Val_uw & Y12)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[20] = ((relay_control_st.Relay_status_st.Val_uw & Y13)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[21] = ((relay_control_st.Relay_status_st.Val_uw & Y14)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[22] = ((relay_control_st.Relay_status_st.Val_uw & Y15)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[23] = ((relay_control_st.Relay_status_st.Val_uw & Y16)!= 0)?'1':'0';
	serial_com_sending_context_st.data_ub[24] = '\r';
	serial_com_sending_context_st.data_ub[25] = '\n';
	serial_com_sending_context_st.data_ub[26] = 'o';
	serial_com_sending_context_st.data_ub[27] = 't';
	serial_com_sending_context_st.data_ub[28] = '1';
	serial_com_sending_context_st.data_ub[29] = ' ';
	if(relay_control_st.Overtime_status_st.Overtime_1 == 1){
		serial_com_sending_context_st.data_ub[30] = 'o';
		serial_com_sending_context_st.data_ub[31] = 'n';
		serial_com_sending_context_st.data_ub[32] = ' ';
	} else{
		serial_com_sending_context_st.data_ub[30] = 'o';
		serial_com_sending_context_st.data_ub[31] = 'f';
		serial_com_sending_context_st.data_ub[32] = 'f';
	}
	serial_com_sending_context_st.data_ub[33] = '\r';
	serial_com_sending_context_st.data_ub[34] = '\n';
	serial_com_sending_context_st.data_ub[35] = 'o';
	serial_com_sending_context_st.data_ub[36] = 't';
	serial_com_sending_context_st.data_ub[37] = '2';
	serial_com_sending_context_st.data_ub[38] = ' ';
	if(relay_control_st.Overtime_status_st.Overtime_2 == 1){
		serial_com_sending_context_st.data_ub[39] = 'o';
		serial_com_sending_context_st.data_ub[40] = 'n';
		serial_com_sending_context_st.data_ub[41] = ' ';
	} else{
		serial_com_sending_context_st.data_ub[39] = 'o';
		serial_com_sending_context_st.data_ub[40] = 'f';
		serial_com_sending_context_st.data_ub[41] = 'f';
	}
	serial_com_sending_context_st.data_ub[42] = '>';
	serial_com_sending_context_st.data_ub[43] = 0;
	serial_com_sending_context_st.sent_length_ub = 43;
}
