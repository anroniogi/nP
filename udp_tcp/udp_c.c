#include "headerfiles.h"

#define BUF_LEN 128


int main(int argc, char *argv[])
{
        int s, n, len_out, addrsize;

        struct sockaddr_in server_addr;

        char *haddr;
        char buf[BUF_LEN + 1];


        if(argc != 3){
                printf("usage : %s ip_address port_number \n", argv[0]);
                exit(0);
        }


        haddr = argv[1];


        if((s = socket(PF_INET, SOCK_DGRAM, 0)) &lt; 0){
                printf("can`t create socket\n");
                exit(0);
        }


        /* echo 서버의 소켓주소 구조체 작성 */

        bzero((char *)&amp;server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(haddr);
        server_addr.sin_port = htons(atoi(argv[2]));


        /*구조체의 크기를 구한다 */

        addrsize = sizeof(struct sockaddr);

        /* 키보드 입력을 받음 */

        printf("Input any string : ");
        if(fgets(buf, BUF_LEN, stdin)){
                buf[BUF_LEN] =  '\0';
                len_out = strlen(buf);

        }else{
                printf("fgets error \n");
                exit(0);

        }


        /* echo 서버로 메세지 송신 */
        if(sendto(s, buf, len_out, 0, (struct sockaddr *)&amp;server_addr, sizeof(struct sockaddr))&lt;0)
        {
                printf("sendto error!\n");
                exit(0);
        }


        /* 수신된 echo 메세지 화면 출력 */

        printf("Echoed setring : ");
        if(recvfrom(s, buf, BUF_LEN, 0, (struct sockaddr *)&amp;server_addr, &amp;addrsize)){
                printf("recvfrom error \n");
                exit(0);
        }


        printf("%s", buf);
        close(s);

        return 0;


}
