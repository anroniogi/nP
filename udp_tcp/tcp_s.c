#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXBUF 1024
int main(int argc, char *argv[]) // char ** argv
{
    int server_sockfd, client_sockfd;
    int state, client_len;
    int pid;
    struct sockaddr_in clientaddr, serveraddr;
    char buf[MAXBUF];
    if (argc != 2){
	printf("Usage : %s [port]\n", argv[0]);
	return 1;
    }

    //create TCP socket
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sockfd < 0){
	perror("socket error : ");
	exit(0);
    }

    // 서버에서 받아들인 클라이언트 주소와 포트 주소를 설정
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(atoi(argv[1]));
    // 설정된 주소를 소켓에 연결
    state = bind(server_sockfd , (struct sockaddr *)&serveraddr,
    sizeof(serveraddr));
    if (state == -1) // 리턴 값의 상태 확인
    {
        perror("bind error : ");
        exit(0);
    }
    // 수신할 수 있는 클라이언트 연결 수가 5개로 설정
    state = listen(server_sockfd, 5);
    if (state == -1) // 리턴 값의 상태 확인
    {
        perror("listen error : ");
        exit(0);
    }
    // 다음장에 계속
    while(1)
    {
	printf("\n");
        // 클라이언트의 연결을 받아들임
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len);
        if (client_sockfd == -1)  // 항상 오류는 검사해주어야 함
        {
            perror("Accept error : ");
            exit(0);
        }
        // 클라이언트와 연결이 성공적이면 자식 프로세스를 하나 만듦
        pid = fork();
        if (pid == 0) // 자식 프로세스인 경우 다음 문장들을 수행하고, 부모인 경우 계속하여 while() 수행
        {
            printf("getchar : ");
            getchar();
            while(1)
            {
                printf("\n");
                memset(buf, 0, MAXBUF);
                if (read(client_sockfd, buf, MAXBUF-1) <= 0) // 데이터가 존재할 때까지 계속 읽음
                {
                    close(client_sockfd);
                    exit(0);
                }
            	printf("received : ");
                printf(" > %s", buf);
                fputs("\n", stdout);
                write(client_sockfd, buf, strlen(buf)); // echo
            }
        }
        if (pid == -1) // 항상 오류는 검사해주어야 함
        {
            perror("fork error : ");
            return 1;
        }
    }
    close(client_sockfd);
}
