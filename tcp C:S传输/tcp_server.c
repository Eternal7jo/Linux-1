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
	ret=bind(socketfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	listen(socketfd,10);//数字运维会说
	int new_fd;//通过new_fd与客户端发送与接收数据
	struct sockaddr_in client;//客户端
	memset(&client,0,sizeof(client));
	socklen_t addrlen=sizeof(client);
	new_fd=accept(socketfd,(struct sockaddr*)&client,&addrlen);
	if(-1==new_fd)
	{
		perror("accept");
		return -1;
	}
	char buf[128]={0};
	ret=recv(new_fd,buf,sizeof(buf),0);
	if(ret==-1)
	{
		perror("recv");
		return -1;
	}
	printf("I am server,I recv %s\n",buf);
	send(new_fd,"world",5,0);
	close(new_fd);//四次挥手
	close(socketfd);//不允许客户端连接,我不再监听
	return 0;
}
