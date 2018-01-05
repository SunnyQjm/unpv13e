#include <unp.h>

void str_echo(int);

void sig_child(int signo);

int main(int argc, char** argv){
    int listenfd, connfd;
    pid_t pid;
    socklen_t clen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9748);

    //指定服务端socket的地址为通配地址
    //表示接收来自本机各个网络接口的连接请求
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    
    //设置信号处理函数，用于处理SIGCHLD信号
    signal(SIGCHLD, sig_child);
    for( ; ; ){
        clen = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *) &cliaddr, &clen);
        //接受到来自客户端的请求之后，fork一个进程，在子进程中为客户提供服务
        //父进程则关闭本进程内该已连接描述符（引用计数减1）
        //然后再返回继续accept，可以达到并发的效果
        if( (pid = Fork()) == 0 ){      //子进程执行
            Close(listenfd);
            str_echo(connfd);
            Close(connfd);
            exit(0);
        }
        Close(connfd);                  //父进程执行
    }
}


/**
 * 为客户端提供服务
 * 从客户端接收一个字符串，并将字符串回射回客户端
 */
void str_echo(int connfd){
    ssize_t n;
    char buf[MAXLINE];

again:
    while((n = read(connfd, buf, MAXLINE)) > 0)
        Writen(connfd, buf, n);
    if(n < 0 && errno == EINTR)
        goto again;
    else if(n < 0)
        err_sys("str_echo: read error");
}


/**
 * 下面是自定义的信号处理函数，用于处理僵死进程
 */
void sig_child(int signo){
    pid_t pid;
    int stat;
    pid = wait(&stat);
    printf("child %d terminated\n", pid);
    return;
}
