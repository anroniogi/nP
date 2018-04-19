// TCP echo server
#include "headerFiles.h"
#define SERVER_PORT 50000
int main()
{
    int test;
    int ls;
    int s;
    char buffer[256];
    char* ptr = buffer;
    int len=0;
    int maxLen = sizeof(buffer);
    int n=0;
    int waitSize = 16;
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    int clntAddrlen;
    //
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(SERVER_PORT);
    ls = socket(PF_INET, SOCK_STREAM, 0);
    if(ls<0)
    {
        perror("ERROR : Listen socket failed");
        exit(1);
    }
    //test = bind(ls, (struct sockaddr*)&servAddr, sizeof(servAddr));
    if(bind(ls, (struct sockaddr*)&servAddr, sizeof(servAddr))<0)
    {
        perror("ERROR : binding failed");
        exit(1);
    }

    if(listen(ls, waitSize)<0)
    {
        perror("ERROR : listening failed");
        exit(1);
    }
    clntAddrlen = sizeof(clntAddr);
    //
    for(;;)
    {
	printf("\n");
        //
        if((s=accept(ls, &clntAddr, &clntAddrlen))<0)
        {
            perror("ERROR : accepting failed");
            exit(1);
        }
        //
        while((n = recv(s, ptr, maxLen,0)) > 0)
        {
	    printf("received : ");
            //ptr += n;
            //maxLen -= n;
            len += n;
	    fputs(buffer, stdout);
	    test = send(s, ptr, len, 0);
	    printf("\n send = %d",test);
        }
        //send(s, ptr, len, 0);
        //
        close(s);
    }
}
