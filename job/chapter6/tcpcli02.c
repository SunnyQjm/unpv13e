#include <unp.h>

void str_cli(FILE*, int);

int main(int argc, char** argv){
    int i, sockfd[5];
    struct sockaddr_in servaddr;

    if(argc != 2)
        err_quit("usage: ./tcpserv01 <IPAddress>");
    for(i = 0; i < 5; i++){
        sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);
    
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_port = htons(9748);
        servaddr.sin_family = AF_INET;

        //调用inet_pton函数将用户输入的点分十进制串转化成网络字节序的32为IPv4地址
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

        Connect(sockfd[i], (SA *) &servaddr, sizeof(servaddr));
    }
    str_cli(stdin, sockfd[0]);
    exit(0);
}

/**
 * 改进后的str_cli函数，可以在服务器停止后马上返回
 */
void str_cli(FILE* fp, int sockfd){
    int     maxfdpl;
    fd_set  rset;
    char    sendline[MAXLINE], recvline[MAXLINE];

    //首先清0
    FD_ZERO(&rset);
    for( ; ; ){
        //在调用select之前，设置监听集，告知select感兴趣的描述符
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);

        //待测试的描述符数应该比我们要监听的最大描述符要大1（因为c语言数组是从0开始计的）
        maxfdpl = max(fileno(fp), sockfd) + 1;

        //一直阻塞，直至上述两个描述符至少其中一个可读（没有指定超时时间，所以会一直等待）
        Select(maxfdpl, &rset, NULL, NULL, NULL);

        if(FD_ISSET(sockfd, &rset)){        //socket 可读
            if(Readline(sockfd, recvline, MAXLINE) == 0)
                err_quit("str_cli: server terminated prematurely");
            Fputs(recvline, stdout);
        }

        if(FD_ISSET(fileno(fp), &rset)){    //用户从控制台输入了数据
            if(Fgets(sendline, MAXLINE, fp) == NULL)
                return;
            Writen(sockfd, sendline, strlen(sendline));
        }
    }
}
