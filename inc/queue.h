#ifndef _QUEUE_H_
#define _QUEUE_H_

#define BUFFER_SIZE 50

typedef struct tagMESSAGE
{
	char * pIn;					//入队指针
	char * pOut;				//出队指针
	char mText[BUFFER_SIZE];	//队列的数剧字符串
	unsigned char mNum;			//当前队列中有多少字节的数据
}messageQueue;

//判断队列是否满
#define MSG_Q_IS_FULL(x)		(x->mNum >= BUFFER_SIZE?1:0)
//判断队列是否为空
#define MSG_Q_IS_EMPTY(x)		(x->mNum?0:1)


#endif