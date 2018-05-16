#include "headerFiles.h"

#define BUFF_SIZE 256
#define PORT_NUMBER 50000

int   main( void)
{
   int   sock;
   int   client_addr_size;

   struct sockaddr_in   server_addr;
   struct sockaddr_in   client_addr;

   char   buff_rcv[BUFF_SIZE+1];

   sock  = socket( PF_INET, SOCK_DGRAM, 0);
   
   if( -1 == sock)
   {
      printf( "socket 생성 실패\n");
      exit( 1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons(PORT_NUMBER);
   server_addr.sin_addr.s_addr= htonl(INADDR_ANY);

   if( -1 == bind( sock, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
   {
      printf( "bind() 실행 에러\n");
      exit( 1);
   }
   client_addr_size  = sizeof( client_addr);

   while( 1)
   {
      printf("\n");
      recvfrom( sock, buff_rcv, BUFF_SIZE, 0 , (struct sockaddr*)&client_addr, &client_addr_size);
      printf( "receive: %s", buff_rcv);
      
      sendto(sock, buff_rcv, strlen(buff_rcv)+1, 0, (struct sockaddr*)&client_addr, sizeof( client_addr)); 
   }
}
