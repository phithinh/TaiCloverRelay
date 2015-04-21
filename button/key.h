#ifndef __KEY_LEDB_H
#define __KEY_LEDB_H

#define REMOTE1	(!Button1)
#define REMOTE2	(!Button2)
#define REMOTE3	(!Button3)
#define REMOTE4	(!Button4)


//@matrix key
//
#define BUTTON_MODE	1
#define BUTTON_UP	2
#define BUTTON_DOWN	3
#define BUTTON_NEXT	4

typedef struct __QBuff
{  
	char Data;
    struct __QBuff *pbuffNext;
}
tQBuff;
unsigned char QBuff_RCnt(void);
void QBuff_Init(void);
void QBuff_Add(tQBuff *queue ,unsigned char data);
tQBuff* QBuff_Read(void);
void QBuff_Del(void);

void Key_init(void);

void Key_Task(void);

char Key_Get(void);

#endif
