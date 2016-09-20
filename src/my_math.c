

/*给定一个正整数，求整数的位数*/
int getNumberLen(unsigned int num)
{
	int num_len = 0;
	unsigned int tnum = num;
	do
	{
		tnum = tnum/10;
		num_len++;
	}while(tnum);
	return num_len;
}


/*给定一个整数，返回一个字符串*/
char* itoa(unsigned long int num,char* str,int radix)
{/*索引表*/
	char index[]="0123456789ABCDEF";
	unsigned long int unum;/*中间变量*/
	char temp;
	int i=0,j,k;
	unum = num;/*其他情况*/
	/*转换*/
	do{
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
	}while(unum);
	str[i]='\0';
	/*逆序*/
	if(str[0]=='-')
		k=1;/*十进制负数*/
	else 
		k=0;
	
	for(j=k;j<=(i-1)/2;j++)
	{
		temp=str[j];
		str[j]=str[i-1+k-j];
		str[i-1+k-j]=temp;
	}
	return str;
}



//原版函数
//char* itoa(int num,char* str,int radix)
//{/*索引表*/
//	char index[]="0123456789ABCDEF";
//	unsigned unum;/*中间变量*/
//	char temp;
//	int i=0,j,k;
//	/*确定unum的值*/
//	if(radix == 10 && num < 0)/*十进制负数*/
//	{
//		unum=(unsigned)-num;
//		str[i++]='-';
//	}
//	else 
//		unum=(unsigned)num;/*其他情况*/
//	/*转换*/
//	do{
//		str[i++] = index[unum % (unsigned)radix];
//		unum /= radix;
//	}while(unum);
//	str[i]='\0';
//	/*逆序*/
//	if(str[0]=='-')
//		k=1;/*十进制负数*/
//	else 
//		k=0;
//	
//	for(j=k;j<=(i-1)/2;j++)
//	{
//		temp=str[j];
//		str[j]=str[i-1+k-j];
//		str[i-1+k-j]=temp;
//	}
//	return str;
//}

