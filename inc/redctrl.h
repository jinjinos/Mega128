//����ң�ؿ���ͷ�ļ�

#ifndef _RED_CTRL_H_
#define _RED_CTRL_H_


//����ң��������
#define KEY_0		0x16
#define KEY_1		0x0C
#define KEY_2		0x18
#define KEY_3		0x5E
#define KEY_4   	0x08
#define KEY_5  	0x1C
#define KEY_6   	0x5A
#define KEY_7   	0x42
#define KEY_8   	0x52
#define KEY_9   	0x4A

//�������ͷ���ӵ�IO�� �궨��
//�������ͷ���ӵ�Ƭ����PE3��
#define RED_IN		DDRE  &= ~(1 << 3)		//��������ģʽ	
#define RED_OUT		DDRE  |=  (1 << 3)		//�������ģʽ
#define RED_CLR		PORTE &= ~(1 << 3)		//PE3�õ͵�ƽ
#define RED_SET		PORTE |=  (1 << 3)		//PE3�øߵ�ƽ
#define RED_R		(PINE & (1 << 3))		//��ȡPE3�������ƽ

extern void redCtrlInit(void);
extern unsigned char key_Icode(unsigned char key_code);
extern unsigned char redCodeReceice(void);


//����ң�صĲ��Ժ���
extern void redCtrlTest(void);

#endif

