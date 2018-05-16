// TCP echo client
#include "headerFiles.h"
int main (int argc, char* argv[])
{
    //
    int s;
    int n;
    char* servName;
    int servPort;
    char* string;
    int len;
    int maxLen;
    char buffer[256+1];
    char* ptr = buffer;
    struct sockaddr_in servAddr;
    //
    
    if(argc !=4)
    {
        printf("ERROR : three arguments are needed");
        exit(1);
    }
   
    
    servName = argv[1];
    servPort = atoi(argv[2]);
    string = argv[3];
    /*
    servName = "210.115.43.150";
    servPort = atoi("50001");
    string = "send string";
    */
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET, servName, &servAddr.sin_addr);
    servAddr.sin_port = htons(servPort);
    s = socket(PF_INET, SOCK_STREAM, 0);
    if(s < 0)
    {
        perror("ERROR : socket creation failed");
        exit(1);
    }
    //
    if(connect(s, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
    {
        perror("ERROR : connection failed");
        exit(1);
    }
    //
    while(1){
        printf("보낼 문자열을 입력하세요 : ");
        gets(buffer);
        if(strcmp(string, "quit")==0)
            break;

        send(s, string, strlen(string), 0);
        while((n = recv(s, ptr, maxLen, 0)) > 0)
        {
            //ptr += n;
            //maxLen -= n;
            len += n;
        }
        //
        //buffer[len+1] = '/0';
        //printf("Echoed string received: ");
        fputs(buffer, stdout);
        printf("\n");
    }

//
    //printf("\n");
    close(s);
    //
    exit(0);
}
