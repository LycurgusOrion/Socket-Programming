/*
	TCP_CLIENT

		3.Write a Client Server program (TCP connection) in which 
			a)Server sends the Date and Time to the client when a Client connects to it 
			b)The Client displays the message.

	./Q3_client ip port_no

*/

#include "socket.h"

int main(int v, char * arg[])
{
	if(v != 3)
	{
		printf("\nusage : ./Q3_client ip port_no\n");
		exit(-1);
	}

	sa_in server, client;
	
	int sock;
	int len = sizeof(sa_in);
	int new;
	int tm_size;

	char s[MAX_DATA], tm[MAX_DATA];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket : ");
		exit(-1);
	}

	server.sin_family		=	AF_INET;
	server.sin_port			=	htons(atoi(arg[2]));
	server.sin_addr.s_addr 	=	inet_addr(arg[1]);
	bzero(&server.sin_zero, 8);

	if((connect(sock, (sa *)&server, len)) == ERROR)
	{
		perror("connect : ");
		exit(-1);
	}

//	while(1)
//	{

		tm_size = recv(sock, tm, sizeof(tm), 0);

		if(tm_size == ERROR)
		{
			perror("recieve : ");
			exit(-1);
		}
		
		printf("\nRecieved message from server at %s:%d : \n\n%s\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port), tm);
//	}	
}