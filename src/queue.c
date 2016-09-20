/**消息队列的实现，用于接收串口的字符串**/
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

//messageQueue receiveMsg;

//队列的初始化
void msgQueueInit(messageQueue * receiveMsg)		
{
	receiveMsg->pIn = &receiveMsg->mText[0];
	receiveMsg->pOut = &receiveMsg->mText[0];
	receiveMsg->mNum = 0;
}

//入队
bool msgQueueIn(messageQueue * receiveMsg,char data)
{
	//如果队列已满，则入队失败
	if(MSG_Q_IS_FULL(receiveMsg))
	{
		return false;
	}
	else
	{
		* (receiveMsg->pIn) = data;
		//如果入队指针pIn指向末尾，就从头开始
		if(receiveMsg->pIn == &receiveMsg->mText[BUFFER_SIZE - 1])
		{
			receiveMsg->pIn = &receiveMsg->mText[0];
		}
		else	//否则pIn自加1
		{
			receiveMsg->pIn++;
		}
		receiveMsg->mNum++;
		return true;
	}
}

//出队
char msgQueueOut(messageQueue * receiveMsg)
{
	char ret;
	//如果队列已空，则出队失败
	if(MSG_Q_IS_EMPTY(receiveMsg))
	{
		return NULL;
	}
	else
	{
		ret = *(receiveMsg->pOut);
		//如果出队指针pOut指向末尾，就从头开始
		if(receiveMsg->pOut == &(receiveMsg->mText[BUFFER_SIZE - 1]))
		{
			receiveMsg->pOut = &(receiveMsg->mText[0]);
		}
		else	//否则pOut自加1
		{
			receiveMsg->pOut++;
		}
		receiveMsg->mNum--;
		return ret;
	}	
}

