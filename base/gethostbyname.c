#include "func.h"

int main(int argc,char* argv[])
{
	args_check(argc,2);
	struct hostent *p;
	p=gethostbyname(argv[1]);
	printf("%s\n",p->h_name);//域名对应的ip地址
	int i;
	for(i=0;p->h_aliases[i]!=NULL;i++)  //字符指针数组最后一个成员为NULL就结束
	{
		printf("%s\n",p->h_aliases[i]);//打印每个成员
	}
	printf("addrtype=%d\n",p->h_addrtype);//地址类型
	printf("length=%d\n",p->h_length);//地址长度
	char ip[16]={0};
	for(i=0;p->h_addr_list[i]!=NULL;i++)
	{
		memset(ip,0,sizeof(ip));
		printf("%s\n",inet_ntop(p->h_addrtype,p->h_addr_list[i],ip,sizeof(ip)));//转换成网络字节序才能正确打印
	}
	return 0;
}
