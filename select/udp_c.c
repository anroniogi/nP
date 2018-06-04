#include "headerFiles.h"

#define BUFF_SIZE 256
#define PORT_NUMBER 50000

int main(int argc, char **argv)
{
   int sock;
   int server_addr_size;

   struct sockaddr_in   server_addr;

   char buff_rcv[256];
   int test;
   char string[256];
   int run=1;

   sock  = socket( PF_INET, SOCK_DGRAM, 0);
   
   if( -1 == sock)
   {
      printf( "socket 생성 실패n");
      exit( 1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons(PORT_NUMBER);
   server_addr.sin_addr.s_addr= inet_addr("210.115.43.150");
   
   while(run){
       printf("\n전송할 문자열을 입력하세요 : ");
       gets(string);
       if(strcmp(string, "quit")==0)
           break;
       test = sendto( sock, string, strlen(string)+1, 0, ( struct sockaddr*)&server_addr, sizeof( server_addr));          

       server_addr_size  = sizeof( server_addr);
       recvfrom(sock, buff_rcv, BUFF_SIZE, 0, (struct sockaddr*)&server_addr, &server_addr_size);
       printf("receive: %s", buff_rcv);
   }
   close(sock);
   
   return 0;
}
