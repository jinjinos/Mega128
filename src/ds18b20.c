/*DS18B20连接在芯片的PE4管脚*/
#include <iom128a.h>
#include <stdbool.h>
#include "delay.h"
#include "ds18b20.h"

/*DS18B20初始化，检测18B20是否存在*/
unsigned int DS18B20_Init(void)
{
	unsigned char i;
	DQ_OUT;				//配置单总线PE4为输出模式
	/*控制器发送复位脉冲 480us - 960us */
	DQ_CLR;				//将DQ清0，发送复位脉冲，保持480us到960us之间
	_delay_us(500);		//延时500us
	DQ_SET;				//将DQ置1
	DQ_IN;				//配置总线PE4位输入模式,利用下边的延时从输出转换到输入模式
	_delay_us(50);		//15-60us之后，接收DS18B20的存在脉冲
	/*控制器接收存在脉冲  60us - 240us*/
	i = DQ_R;			//读取存在脉冲
	_delay_us(500);		//延时450us,接收保持大于480us		
	
	if(!i)
	{
		return 1;		//如果DQ_R存在脉冲为低电平，则DS18B20已准备就绪
	}
	else 
	{
		return 0;		//否则DS18B20不存在，没准备好
	}
}

/*从DS18B20中读取一个字节*/
unsigned char ds18b20_read_byte(void)
{
	unsigned char i;
	unsigned char dat = 0;
	
	//循环八次，读取一个字节数据
	for(i = 8;i != 0;i--)
	{
		dat >>= 1;		//值右移一位
		
		DQ_OUT;			//输出模式
		DQ_CLR;			//输出低电平
		_delay_us(4);		
		DQ_SET;			//拉高电平
		
		DQ_IN;			//输入模式
		_delay_us(10);	//延时10us
		
		if(DQ_R)		//如果PINE4为高电平，将dat的最高位置1。否则为0
		{
			dat |= 0x80;	
		}
		_delay_us(60);
	}
	return dat;
}


/*向DS18B20中写入一个字节的数据*/
void ds18b20_write_byte(unsigned char dat)
{
	unsigned char i;
	
	for(i = 8; i != 0; i--)
	{
		DQ_OUT;			//配置为输出模式并输出低电平
		DQ_CLR;
		_delay_us(4);
		
		if(dat & 0x01)	//如果dat的最低位为1，就拉高电平
		{
			DQ_SET;
		}
		
		_delay_us(45);		//延时45us
		
		DQ_SET;			//位结束，无论输出的是0或1最后都要拉高电平
		dat >>= 1;		//要写入的数据dat右移一位
		
	}
}


/*从DS18B20中读取温度   0x44命令 */
unsigned int ds18b20_read_temperature(void)
{
	unsigned char temp_low = 0;
	unsigned int temp = 0,i = 7;
	//检测DS18B20是否存在，使其准备好并开始工作
		
		DS18B20_Init();
		//启动DS18B20温度转换
		ds18b20_write_byte(0xCC);		//单总线共一个设备，忽略地址
		ds18b20_write_byte(0x44);		//启动转换
		_delay_us(10);					
		
		DS18B20_Init();
		//读取寄存器数据
		ds18b20_write_byte(0xCC);		//忽略地址
		ds18b20_write_byte(0xBE);		//读取温度寄存器，可读9个字节
		
		temp_low = ds18b20_read_byte();	//温度低字节
		temp	 = ds18b20_read_byte();	//温度高字节
		
		while(i--)
		{
			ds18b20_read_byte();		//将剩余的戚歌字节读出来
		}
			
//		temp &= 0x01;
		temp <<= 8;			//高字节左移八位
		temp  |= temp_low;	//高位和地位组合
		return temp;
}












