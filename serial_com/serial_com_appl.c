/*
 * serial_com_appl.c
 *
 *  Created on: Mar 29, 2015
 *      Author: phi thinh
 */

#define SERIAL_COM_APPL

#include "pic30_serial_com.h"
#include "serial_com_appl.h"
#include "../interfaces/interfaces.h"
#include "serial_com_reaction/serial_com_reaction.h"

/*
 * @ serial communication state machine
 *
 * State:
 * 		+ uninit
 * 		+ idle
 * 		+ receiving
 * 		+ sending
 *
 * uninit -> idle:
 * 			Condition:
 * 				1. initial function is done
 * idle -> receiving:
 * 			Condition:
 * 				1. got starting char '<'
 * idle -> sending:
 * 			Condition:
 * 				1. got state request
 * 				2. there is a error
 * receiving -> idle:
 * 			Condition:
 * 				1. got end char '>'
 * 				2. rx time out
 * sending -> idle:
 * 			Condition:
 * 				1. completed sending
 * 				2. tx time out
 *
 *
 * */
extern signed long tick_count;
unsigned char l_serial_com_send_status_flag_b;

void serial_com_init_v(void){
	ConsoleInit();
	serial_com_state = SERIAL_COM_STATE_IDLE;
	serial_com_receiving_context_st.sent_index_ub = 0;
	serial_com_receiving_context_st.done_flag_ub = 0;
	serial_com_receiving_context_st.error_flag_ub = 0;
	serial_com_sending_context_st.sent_index_ub = 0;
	serial_com_sending_context_st.error_flag_ub = 0;
}
void serial_com_main(void){
	l_serial_com_requested_relay_uw = 0;
	l_serial_com_requested_relay_flag_b = 0;

	switch(serial_com_state){
	case SERIAL_COM_STATE_IDLE:
		//
		if (serial_com_receiving_context_st.error_flag_ub){
			serial_com_send_nok_v();
			serial_com_send_v();
			serial_com_receiving_context_st.error_flag_ub = 0;
		} else if(serial_com_receiving_context_st.done_flag_ub){
//			serial_com_send_ok_v();
//			serial_com_send_v();
			if (serial_com_receiving_context_st.data_ub[0] == 'r'){
				serial_com_set_relay_state_v();
				l_serial_com_send_status_flag_b = 1;
				serial_com_sm_idle_sending_v();
			}else if (serial_com_receiving_context_st.data_ub[0] == 's'){
				l_serial_com_send_status_flag_b = 1;
				serial_com_sm_idle_sending_v();
			}
			serial_com_receiving_context_st.done_flag_ub = 0;
		}
		//now we don't monitor tx time out
		break;
	case SERIAL_COM_STATE_RECEIVING:
		if ((tick_count - serial_com_receiving_context_st.timerstamp )>COM_SERIAL_RX_TIME_OUT){
			serial_com_receiving_context_st.error_flag_ub = 1; // time out
			serial_com_sm_receiving_idle_v();
		}
		break;
	case SERIAL_COM_STATE_SENDING:
		if ((tick_count - serial_com_sending_context_st.timerstamp )>COM_SERIAL_TX_TIME_OUT){
			serial_com_sending_context_st.error_flag_ub = 1; // time out
			serial_com_sm_sending_idle_v();
		} else {
			if (l_serial_com_send_status_flag_b){	//because it has to wait 1 cyclic in order to relay controller updates status
				serial_com_send_relay_state_v();
				l_serial_com_send_status_flag_b= 0;
			}
			serial_com_send_v();
			serial_com_sm_sending_idle_v();
		}
		break;
	default:
		serial_com_state = SERIAL_COM_STATE_IDLE;
		break;
	}

	serial_com_st.Requested_relay_st.Val_uw = l_serial_com_requested_relay_uw;
	serial_com_st.requested_flag_b = l_serial_com_requested_relay_flag_b;
}

void serial_com_isrq_hanlder(unsigned char p_data_ub){
	switch(serial_com_state){
	case SERIAL_COM_STATE_IDLE:
		if (COM_SERIAL_SPEC_CHAR_START == p_data_ub){
			serial_com_sm_idle_receiving_v();
		}
		break;
	case SERIAL_COM_STATE_RECEIVING:
		if (COM_SERIAL_SPEC_CHAR_END == p_data_ub){
			serial_com_receiving_context_st.done_flag_ub = 1;
			serial_com_sm_sending_idle_v();
		}else if ((tick_count - serial_com_receiving_context_st.timerstamp )>COM_SERIAL_RX_TIME_OUT){
			serial_com_receiving_context_st.error_flag_ub = 1; // time out
			serial_com_sm_sending_idle_v();
		} else {
			// buffer is overflow
			if (SERIAL_COM_MAX_RX_BF <= serial_com_receiving_context_st.sent_index_ub){
				serial_com_receiving_context_st.error_flag_ub = 1; // max buffer
				serial_com_sm_sending_idle_v();
			} else {
				serial_com_receiving_context_st.data_ub[serial_com_receiving_context_st.sent_index_ub] = p_data_ub;
                serial_com_receiving_context_st.sent_index_ub++;
			}
		}
		break;
	case SERIAL_COM_STATE_SENDING:
		//?? :D
		serial_com_state = SERIAL_COM_STATE_IDLE;
		break;
	default:
		serial_com_state = SERIAL_COM_STATE_IDLE;
		break;
	}

}

void serial_com_sm_receiving_idle_v(void){
//	if (SERIAL_COM_STATE_RECEIVING == serial_com_state){

	serial_com_sm_goto_idle_v();
//	}

}
void serial_com_sm_sending_idle_v(void){
//	if (SERIAL_COM_STATE_SENDING == serial_com_state){

	serial_com_sm_goto_idle_v();
//	}

}
void serial_com_sm_idle_receiving_v(void){
	if (SERIAL_COM_STATE_IDLE == serial_com_state){
		serial_com_state = SERIAL_COM_STATE_RECEIVING;
		serial_com_receiving_context_st.timerstamp = tick_count;
		serial_com_receiving_context_st.done_flag_ub = 0;
		serial_com_receiving_context_st.error_flag_ub = 0;
		serial_com_receiving_context_st.sent_index_ub = 0;
		serial_com_receiving_context_st.timerstamp = tick_count;
	} else {
		serial_com_sm_goto_idle_v();
	}

}
void serial_com_sm_idle_sending_v(void){
	if (SERIAL_COM_STATE_IDLE == serial_com_state){
		serial_com_state = SERIAL_COM_STATE_SENDING;
		serial_com_sending_context_st.timerstamp = tick_count;
		serial_com_sending_context_st.sent_index_ub = 0;
		serial_com_sending_context_st.error_flag_ub = 0;
		serial_com_sending_context_st.sent_length_ub = 0;
	} else {
		serial_com_sm_goto_idle_v();
	}

}

void serial_com_sm_goto_idle_v(void){
	serial_com_state = SERIAL_COM_STATE_IDLE;
	serial_com_receiving_context_st.sent_index_ub = 0;
	//serial_com_receiving_context_st.done_flag_ub = 0;
	//serial_com_receiving_context_st.error_flag_ub = 0;
	serial_com_sending_context_st.sent_index_ub = 0;
	//serial_com_sending_context_st.error_flag_ub = 0;

}
void serial_com_send_v(void){
	ConsolePutROMString((char *)serial_com_sending_context_st.data_ub);
}
