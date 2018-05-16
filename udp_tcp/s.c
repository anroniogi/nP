#include "headerfiles.h"

#define BUF_LEN 128


int main(int argc, char *argv[])
{

        struct sockaddr_in server_addr, client_addr;

        int s;
        int len, msg_size;

        char buf[BUF_LEN+1];

        if(argc != 2){
                printf("usage: %s port\n", argv[0]);
                exit(0);
        }

        /* 소켓 생성 */
        if((s = socket(PF_INET, SOCK_DGRAM, 0))&lt;0){
                printf("server : Can`t open stream socket. ");
                exit(0);
        }


        /* server_addr을 NULL으로 초기화 */
        bzero((char *)&amp;server_addr, sizeof(server_addr));
        bzero((char *)&amp;client_addr, sizeof(client_addr));

        /*server_addr 세팅 */
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(atoi(argv[1]));

        /* bind() 호출 */
        if(bind(s, (struct sockaddr *)&amp;server_addr, sizeof(server_addr)) &lt; 0){
                printf("Server : Can,t bind local address. \n");
                exit(1);
        }


        len = sizeof(struct sockaddr);


        /* iterative echo 서비스 수행 */

        while(1){
                printf("Server : wating request.\n");

                /* 연결요청을 기다림 */

                if(msg_size = recvfrom(s, buf, BUF_LEN, 0 , (struct sockaddr *)&amp;client_addr, &amp;len) == -1){
                        printf("recvfrom error\n");
                        exit(0);
                }

                printf("server : A client data received. \n");

                if(sendto(s, buf, msg_size, 0,  (struct sockaddr *)&amp;client_addr, len) &lt; 0){
                        exit(0);
                }

                printf("sendto complete\n");

        }


        return 0;

}
