#include <unp.h>

void str_cli(FILE*, int);

int main(int argc, char** argv){
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc != 2)
        err_quit("usage: ./tcpserv01 <IPAddress>");
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_port = htons(9748);
    servaddr.sin_family = AF_INET;

    //调用inet_pton函数将用户输入的点分十进制串转化成网络字节序的32为IPv4地址
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);
    Close(sockfd);
}

/**
 * 用fgets读取用户的一行输入，发送给服务器，再从服务器接收一行回复并打印到控制台
 */
void str_cli(FILE* fp, int sockfd){
    char sendbuf[MAXLINE], recvline[MAXLINE];
    while(Fgets(sendbuf, MAXLINE, fp) != NULL){
        Writen(sockfd, sendbuf, strlen(sendbuf));
        if(Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");
        Fputs(recvline, stdout);
    }
}
