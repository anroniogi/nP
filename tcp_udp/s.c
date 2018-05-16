#include "headerfiles.h"

#define MAXBUF 1024
#define 



int main(int argc, char *argv[]){
    
    int server_sockfd, client_sockfd;
    int state, client_len;
    int pid;
    struct sockaddr_in clientaddr, serveraddr;
    char buf[MAXBUF];
    char tcp[] = "TCP : "
    char buff_snd[MAXBUF];


    //TCP SOCKET 생성
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sockfd < 0){
        perror("socket error : ");
        exit(0);
    }

    //서버에서 받을 클라이언트 주소, 포트주소 설정




    return 0;
}
