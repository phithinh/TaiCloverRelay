
#include "../INCLUDE/system.h" 
#include "key.h"

//extern short g_sTick;

tQBuff g_tButSta[20] ;
unsigned char g_ucButQCnt = 0;
unsigned char	g_usQBuff_count;
tQBuff* pQBuff_front;
tQBuff* pQBuff_rear;

enum{
	KEY_NO1 =0,
	KEY_NO2,
	KEY_NO3,
	KEY_NO4,
	NUM_KEY,
}key_idx;

unsigned char QBuff_RCnt(void)
{
	return(g_usQBuff_count);
}

void QBuff_Init(void)
{
	g_usQBuff_count = 0;	//null value
	pQBuff_front = 0;	//null value
	pQBuff_rear  = 0;	//null value
}
void QBuff_Add(tQBuff *queue ,unsigned char data)
{
	queue->Data = data;
	if(g_usQBuff_count == 0){				//if add queue at fist
		pQBuff_rear = queue;			//get next queue
		pQBuff_front = pQBuff_rear;
		pQBuff_rear->pbuffNext = 0;	//null
	}
	else{
		pQBuff_rear->pbuffNext = queue;	//set next queue for current queue
		pQBuff_rear = queue;			//get next queue
	}
	pQBuff_rear->pbuffNext = 0;		//null value
	g_usQBuff_count++;
}
tQBuff* QBuff_Read(void)
{
	return(pQBuff_front);
}
void QBuff_Del(void)
{
	g_usQBuff_count--;
	if(g_usQBuff_count == 0){
		pQBuff_front = 0;	//null value
		pQBuff_rear = 0;		//null value
	}
	else
		pQBuff_front = pQBuff_front->pbuffNext;
}

void Key_init(void)
{
//	ANSEL = 0;
//	ANSELH = 0;
//	TRIS_KEY_COL1 = 0;
//	TRIS_KEY_COL2 = 0;
//	TRIS_KEY_COL3 = 0;
//	TRIS_KEY_COL4 = 0;
//
//	KEY_COL1 = 1;
//	KEY_COL2 = 1;
//	KEY_COL3 = 1;
//	KEY_COL4 = 1;
//
//	TRIS_KEY_ROW1 = 1;
//	TRIS_KEY_ROW2 = 1;
//	TRIS_KEY_ROW3 = 1;
//	TRIS_KEY_ROW4 = 1;
//
//
//	TRIS_REMOTE1 = 1;
//	TRIS_REMOTE2 = 1;
//	TRIS_REMOTE3 = 1;
//	TRIS_REMOTE4 = 1;
//	TRIS_BUZZ = 0;
//	BUZZ = 1;
}

unsigned char ar_ucKeyStatus[NUM_KEY];
unsigned char Key_index = 0;
extern signed long tick_count;
signed long sKey_tick = 0;
void Key_Task(void)
{

	unsigned char i;
	switch(Key_index){
		case 0:
			//wait for 1000 tick
			//
			if((tick_count - sKey_tick)>800){//fix time
				sKey_tick = tick_count;
				Key_index = 1;
			}
			return;
		case 1:
			//!check key
			//

//			//collum 1
//			KEY_COL1 = 0;
//			if(KEY_ROW1)
//				ar_ucKeyStatus[0] = 0;
//			else
//				ar_ucKeyStatus[0]++;
//			if(KEY_ROW2)
//				ar_ucKeyStatus[1] = 0;
//			else
//				ar_ucKeyStatus[1]++;
//			if(KEY_ROW3)
//				ar_ucKeyStatus[2] = 0;
//			else
//				ar_ucKeyStatus[2]++;
//			if(KEY_ROW4 )
//				ar_ucKeyStatus[3] = 0;
//			else
//				ar_ucKeyStatus[3]++;
//			KEY_COL1 = 1;
//			//collum 2
//			KEY_COL2 = 0;
//			if(KEY_ROW1)
//				ar_ucKeyStatus[4] = 0;
//			else
//				ar_ucKeyStatus[4]++;
//			if(KEY_ROW2)
//				ar_ucKeyStatus[5] = 0;
//			else
//				ar_ucKeyStatus[5]++;
//			if(KEY_ROW3)
//				ar_ucKeyStatus[6] = 0;
//			else
//				ar_ucKeyStatus[6]++;
//			if(KEY_ROW4 )
//				ar_ucKeyStatus[7] = 0;
//			else
//				ar_ucKeyStatus[7]++;
//			KEY_COL2 = 1;
//			//collum 3
//			KEY_COL3 = 0;
//			if(KEY_ROW1)
//				ar_ucKeyStatus[8] = 0;
//			else
//				ar_ucKeyStatus[8]++;
//			if(KEY_ROW2)
//				ar_ucKeyStatus[9] = 0;
//			else
//				ar_ucKeyStatus[9]++;
//			if(KEY_ROW3)
//				ar_ucKeyStatus[10] = 0;
//			else
//				ar_ucKeyStatus[10]++;
//			if(KEY_ROW4 )
//				ar_ucKeyStatus[11] = 0;
//			else
//				ar_ucKeyStatus[11]++;
//			KEY_COL3 = 1;
//			//collum 4
//			KEY_COL4 = 0;
//			if(KEY_ROW1)
//				ar_ucKeyStatus[12] = 0;
//			else
//				ar_ucKeyStatus[12]++;
//			if(KEY_ROW2)
//				ar_ucKeyStatus[13] = 0;
//			else
//				ar_ucKeyStatus[13]++;
//			if(KEY_ROW3)
//				ar_ucKeyStatus[14] = 0;
//			else
//				ar_ucKeyStatus[14]++;
//			if(KEY_ROW4)
//				ar_ucKeyStatus[15] = 0;
//			else
//				ar_ucKeyStatus[15]++;
//			KEY_COL4 = 1;


			//
			//
			if(REMOTE1)
				ar_ucKeyStatus[KEY_NO1]++;
			else
				ar_ucKeyStatus[KEY_NO1] = 0;	
			if(REMOTE2)
				ar_ucKeyStatus[KEY_NO2]++;
			else
				ar_ucKeyStatus[KEY_NO2] = 0;

			if(REMOTE3)
				ar_ucKeyStatus[KEY_NO3]++;
			else
				ar_ucKeyStatus[KEY_NO3] = 0;

			if(REMOTE4)
				ar_ucKeyStatus[KEY_NO4]++;
			else
				ar_ucKeyStatus[KEY_NO4] = 0;

				
			for(i = 0;i<NUM_KEY;i++){
				if(ar_ucKeyStatus[i] == 2){
					if(QBuff_RCnt()<19){
						g_ucButQCnt++;
						if(g_ucButQCnt>19)
							g_ucButQCnt = 0;
						QBuff_Add(&g_tButSta[g_ucButQCnt], i+1);
					}
				}
				if((i == KEY_NO2)||(i==KEY_NO3)){
					if((ar_ucKeyStatus[i] >= 10)&&(ar_ucKeyStatus[i]%5)){
						if(QBuff_RCnt()<19){
							g_ucButQCnt++;
							if(g_ucButQCnt>19)
								g_ucButQCnt = 0;
							QBuff_Add(&g_tButSta[g_ucButQCnt], i+1);
						}
					}
				}
			}
			Key_index = 0;
			return;
	}
}

char Key_Get(void)
{
	tQBuff* stKey;
	if(QBuff_RCnt()){
		stKey = QBuff_Read();
		QBuff_Del();
		return(stKey->Data);
	}
	else
		return(0);
}
