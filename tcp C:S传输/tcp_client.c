#include "func.h"

int main(int argc,char *argv[])
{
	args_check(argc,3);//传第一个是ip,第二个端口号
	int socketfd=socket(AF_INET,SOCK_STREAM,0);
	if(socketfd==-1)
	{
		perror("socket");
		return -1;
	}
	printf("socket=%d\n",socketfd);
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));//先把ser清空
	ser.sin_family=AF_INET;//把ser初始化,告诉别人我是ipv4
	ser.sin_port=htons(atoi(argv[2]));//转成整型数
	ser.sin_addr.s_addr=inet_addr(argv[1]);//把ip转成32位网络字节
	int ret;
	ret=connect(socketfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("connect");
		return -1;
	}
	send(socketfd,"hello",5,0);
	char buf[128]={0};
	recv(socketfd,buf,sizeof(buf),0);
	printf("I am client %s\n",buf);
	close(socketfd);
	return 0;
}
