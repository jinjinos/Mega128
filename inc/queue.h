#ifndef _QUEUE_H_
#define _QUEUE_H_

#define BUFFER_SIZE 50

typedef struct tagMESSAGE
{
	char * pIn;					//���ָ��
	char * pOut;				//����ָ��
	char mText[BUFFER_SIZE];	//���е������ַ���
	unsigned char mNum;			//��ǰ�������ж����ֽڵ�����
}messageQueue;

//�ж϶����Ƿ���
#define MSG_Q_IS_FULL(x)		(x->mNum >= BUFFER_SIZE?1:0)
//�ж϶����Ƿ�Ϊ��
#define MSG_Q_IS_EMPTY(x)		(x->mNum?0:1)


#endif