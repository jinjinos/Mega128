/**��Ϣ���е�ʵ�֣����ڽ��մ��ڵ��ַ���**/
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

//messageQueue receiveMsg;

//���еĳ�ʼ��
void msgQueueInit(messageQueue * receiveMsg)		
{
	receiveMsg->pIn = &receiveMsg->mText[0];
	receiveMsg->pOut = &receiveMsg->mText[0];
	receiveMsg->mNum = 0;
}

//���
bool msgQueueIn(messageQueue * receiveMsg,char data)
{
	//������������������ʧ��
	if(MSG_Q_IS_FULL(receiveMsg))
	{
		return false;
	}
	else
	{
		* (receiveMsg->pIn) = data;
		//������ָ��pInָ��ĩβ���ʹ�ͷ��ʼ
		if(receiveMsg->pIn == &receiveMsg->mText[BUFFER_SIZE - 1])
		{
			receiveMsg->pIn = &receiveMsg->mText[0];
		}
		else	//����pIn�Լ�1
		{
			receiveMsg->pIn++;
		}
		receiveMsg->mNum++;
		return true;
	}
}

//����
char msgQueueOut(messageQueue * receiveMsg)
{
	char ret;
	//��������ѿգ������ʧ��
	if(MSG_Q_IS_EMPTY(receiveMsg))
	{
		return NULL;
	}
	else
	{
		ret = *(receiveMsg->pOut);
		//�������ָ��pOutָ��ĩβ���ʹ�ͷ��ʼ
		if(receiveMsg->pOut == &(receiveMsg->mText[BUFFER_SIZE - 1]))
		{
			receiveMsg->pOut = &(receiveMsg->mText[0]);
		}
		else	//����pOut�Լ�1
		{
			receiveMsg->pOut++;
		}
		receiveMsg->mNum--;
		return ret;
	}	
}

