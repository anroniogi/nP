// UDP/TCP echo client
#include "headerFiles.h"

#define BUFF_SIZE 256
int main (int argc, char* argv[])
{
    //
    int tcp_s;
    int udp_s;
    int n;
    char* servName;
    int tcp_servPort;
    int udp_servPort;
    //char* string;
    char string[256];
    int len;
    int maxLen=256;
    char buffer[256+1];
    char* ptr = buffer;

    int server_addr_size;
    char buff_rcv[256];
    int this;
    //tcp
    struct sockaddr_in servAddr;

    //udp
    struct sockaddr_in server_addr;
    //
    /*
    if(argc !=4)
    {
        printf("ERROR : three arguments are needed");
        exit(1);
    }
        
    servName = argv[1];
    servPort = atoi(argv[2]);
    string = argv[3];
    */
    servName = "127.0.0.1";
    tcp_servPort = 50000;
    udp_servPort = 50001;
    //string = "test";
   
    //tcp 설정
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET, servName, &servAddr.sin_addr);
    servAddr.sin_port = htons(tcp_servPort);
 
    //UDP socket 생성
    udp_s = socket(PF_INET, SOCK_DGRAM, 0);
   
    //udp 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(udp_servPort);
    server_addr.sin_addr.s_addr = inet_addr(servName);


    //TCP socket 생성
    tcp_s = socket(PF_INET, SOCK_STREAM, 0);
    /*
    //UDP socket 생성
    udp_s = socket(PF_INET, SOCK_DGRAM, 0);
    */

    //TCP socket error check
    if(tcp_s < 0){
        perror("ERROR : TCP socket creation failed");
        exit(1);
    }

    //UDP socket error ckeck
    if(udp_s <0){
        perror("ERROR : UDP socket creation failed!");
        exit(1);
    }
    
    //
    if(connect(tcp_s, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
    {
        perror("ERROR : TCP connection failed");
        exit(1);
    }
    while(1){
	printf("\n전송할 문자열을 입력하세요 : ");
	gets(string);
	if(strcmp(string, "quit")==0)
	    break;

        //TCP send
        send(tcp_s, string, strlen(string), 0);
        printf("TCP send 성공");
        while((n = recv(tcp_s, ptr, maxLen, 0)) < 0)
        {
            //ptr += n;
            //maxLen -= n;
            len += n;
        }
        printf("TCP recv 성공");
        //UDP send
        sendto(udp_s, string, strlen(string)+1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        server_addr_size = sizeof(server_addr);
        this = recvfrom(udp_s, buff_rcv, BUFF_SIZE, 0, (struct sockaddr*)&server_addr, &server_addr_size);

        buff_rcv[this] = '\0';
        printf("%s", buff_rcv);


        //
        printf("\n Echoed string received: ");
        fputs(buffer, stdout);
        //printf("%c", ptr);
        //
        //printf("\n");
    }
    close(tcp_s);
    close(udp_s);
    //
    exit(0);
}
