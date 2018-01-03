#include <unp.h>
#include <time.h>

int main(int argc, int argv){
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    //调用包裹函数，创建一个socket
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);

    //指定socket的地址为INADDR_ANY，标识监听来自所有地址的请求
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //将socket绑定到指定的端口，只在指定的端口监听来自客户端的请求
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    //调用Lisen可将socket转换成一个监听套接字，监听套接字可用于监听其他客户端的请求
    Listen(listenfd, LISTENQ);

    for( ; ; ){
        //accpet函数是一个阻塞函数，死等一个连接请求。
        //当监听到一个请求，就返回一个已连接描述符（该描述符用于与新连接的那个客户端通信）
        connfd = Accept(listenfd, (SA *) NULL, NULL);
        
        //获取当前系统的时间
        ticks = time(NULL);

        //将当前时间输出到buff数组中
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        //将buff中的数据发给客户端
        Write(connfd, buff, strlen(buff));

        //关闭socket连接
        Close(connfd);
    }
}

