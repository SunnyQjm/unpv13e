#include <unp.h>

void dg_echo(int sockfd, SA *cliaddr, socklen_t clilen);

int main(int argc, char **argv){
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    //第二个参数指定为SOCK_DGRAM，标识创建一个UDP套接字
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9748);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //为套接字绑定众所周知的端口号，以及指定接收哪些网络接口的请求
    Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));
    
    dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
}

void dg_echo(int sockfd, SA *cliaddr, socklen_t clilen){
    int n;
    socklen_t len;
    char mesg[MAXLINE];

    for( ; ; ){
        len = clilen;
        //接收客户号段发送的消息
        n = Recvfrom(sockfd, mesg, MAXLINE, 0, cliaddr, &len);

        //回射
        Sendto(sockfd, mesg, n, 0, cliaddr, len);
    }
}
