#include <unp.h>

int main(int argc, char **argv){
    struct servent *sptr;
    char **sptrs;   

    if(argc != 3)
        err_quit("usgae: ./gsbn <servname> <protoname>");
    sptr = getservbyname(argv[1], argv[2]);
    if(sptr == NULL)
        err_quit("get error");
    printf("official name: %s\n", sptr->s_name);
    for(sptrs = sptr->s_aliases; *sptrs != NULL; sptrs++)
        printf("\t\talias: %s\n", *sptrs);
    printf("port: %d\n", sptr->s_port);
    printf("protocol: %s\n", sptr->s_proto);
}
