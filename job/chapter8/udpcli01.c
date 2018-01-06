#include <unp.h>

void dg_cli_my(FILE *fp, int sockfd, SA *servaddr, socklen_t len);

int main(int argc, char **argv){
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc != 2)
        err_quit("usage: ./udpcli01 <IPAddress>\n");

    //创建一个UDP套接字
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9748);
    
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    dg_cli_my(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));
}

void dg_cli_my(FILE* fp, int sockfd, SA *servaddr, socklen_t len){
    int n;
    char sendline[MAXLINE], recvline[MAXLINE];

    //从控制台接收用户输入，并发送给服务器
    //接着接收服务器回射的消息，并输出到控制台
    while( (Fgets(sendline, MAXLINE, fp)) != NULL){
        Sendto(sockfd, sendline, strlen(sendline), 0, servaddr, len);
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }

}
