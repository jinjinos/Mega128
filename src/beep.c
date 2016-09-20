//蜂鸣器的驱动文件

#include <iom128a.h>
#include "beep.h"
#include "delay.h"

/*蜂鸣器初始化，配置PD6端口为输出模式*/
void beepInit(void)
{
	DDRD  |= 1 << 6;		//将DDRD的DDD6位置1，配置为输出模式
	BEEP1;					//关闭蜂鸣器  
}



void beepBeep(unsigned int time)
{
	BEEP0;
	delay_ms(time);
	BEEP1;	
}

