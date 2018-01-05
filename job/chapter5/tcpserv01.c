#include <unp.h>

void str_echo(int);

int main(int argc, char** argv){
    int listenfd, connfd;
    pid_t pid;
    socklen_t clen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9748);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    for( ; ; ){
        clen = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *) &cliaddr, &clen);
        if( (pid = Fork()) == 0 ){      //子进程执行
            Close(listenfd);
            str_echo(connfd);
            Close(connfd);
            exit(0);
        }
        Close(connfd);                  //父进程执行
    }
}


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
