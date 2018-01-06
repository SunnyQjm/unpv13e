#include <unp.h>

int main(int argc, char **argv){
    char *ptr, **pptr;
    struct hostent *hptr;
    char str[INET_ADDRSTRLEN];
    
    struct sockaddr_in ia;

    if(argc != 2)
        err_quit("usage: ./ghbn <IPAddress>");

    Inet_pton(AF_INET, argv[1], &ia.sin_addr);
    if( (hptr = gethostbyaddr(&ia.sin_addr, sizeof(ia.sin_addr), AF_INET)) == NULL){
        err_msg("get hostbyname error for host %s : %s", argv[1], hstrerror(h_errno));
    } else {
        printf("official hostname: %s\n", hptr->h_name);
        for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
            printf("\talist: %s\n", *pptr);
        for(pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
            printf("address: %s\n", Inet_ntop(AF_INET, *pptr, str, sizeof(str)));
    }


}

