#include "func.h"

int main(int argc,char* argv[])
{
	args_check(argc,2);
	int ret;
	struct in_addr addr; //存放ip数值
	ret=inet_aton(argv[1],&addr);//inet_aton将十进制ip转化二进制,argv[1]代表传入的第一个参数,就是ip地址,addr就是新的ip地址结构
	printf("%x\n",addr.s_addr);
	return 0;
}

