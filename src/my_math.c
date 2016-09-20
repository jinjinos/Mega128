

/*����һ������������������λ��*/
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


/*����һ������������һ���ַ���*/
char* itoa(unsigned long int num,char* str,int radix)
{/*������*/
	char index[]="0123456789ABCDEF";
	unsigned long int unum;/*�м����*/
	char temp;
	int i=0,j,k;
	unum = num;/*�������*/
	/*ת��*/
	do{
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
	}while(unum);
	str[i]='\0';
	/*����*/
	if(str[0]=='-')
		k=1;/*ʮ���Ƹ���*/
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



//ԭ�溯��
//char* itoa(int num,char* str,int radix)
//{/*������*/
//	char index[]="0123456789ABCDEF";
//	unsigned unum;/*�м����*/
//	char temp;
//	int i=0,j,k;
//	/*ȷ��unum��ֵ*/
//	if(radix == 10 && num < 0)/*ʮ���Ƹ���*/
//	{
//		unum=(unsigned)-num;
//		str[i++]='-';
//	}
//	else 
//		unum=(unsigned)num;/*�������*/
//	/*ת��*/
//	do{
//		str[i++] = index[unum % (unsigned)radix];
//		unum /= radix;
//	}while(unum);
//	str[i]='\0';
//	/*����*/
//	if(str[0]=='-')
//		k=1;/*ʮ���Ƹ���*/
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

