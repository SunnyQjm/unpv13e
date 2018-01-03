#include <unp.h>

int main(int argc, char** argv){
    int sockfd, n;                      //sockfd 套接字描述符，客户端通过该描述符与服务器进行通信（它指示一个与服务器的连接）
    char recvline[MAXLINE + 1];         //接收缓存
    struct sockaddr_in servaddr;        //服务器地址，用来保存服务器的地址信息（该结构体专门保存IPV4地址），包括ip和端口

    //如果输入参数不够，则报错并退出
    if(argc != 2)
        err_quit("usage: daytimecli <IPAddress>");

    //通过socket函数创建一个套接字，创建失败则退出
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0)
        err_sys("socket error");
    
    //清0
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;      //指定协议族为网际协议族
    servaddr.sin_port = htons(13);      //指定端口为13
    
    //将用户从命令行输入的IP存到servaddr中，如果用户输入的格式不正确
    //则该函数会返回小于0的错误信息，此时退出应用程序
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);  
    
    //连接到servaddr指向的服务器，连接失败则退出    
    if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    //读取服务器发回的信息
    while( (n = read(sockfd, recvline, MAXLINE)) > 0 ){
        recvline[n] = 0;

        //输出到控制台
        if(fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }

    if(n < 0)
        err_sys("read error");
    exit(0);
}
