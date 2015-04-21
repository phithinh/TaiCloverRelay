/*
 * pic30_serial_com_cfg.h
 *
 *  Created on: Mar 29, 2015
 *      Author: phi thinh
 */

#ifndef PIC30_SERIAL_COM_CFG_H_
#define PIC30_SERIAL_COM_CFG_H_

#include "serial_com_appl.h"

#define ISR_Serial_v(data)	serial_com_isrq_hanlder(data)
//todo: serial interrupt routine

#endif /* PIC30_SERIAL_COM_CFG_H_ */
