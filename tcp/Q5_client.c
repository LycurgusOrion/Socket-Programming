/*
	TCP_CLIENT

		5.Write a Client Server program (TCP connection)  in which 
			a)Client connects to a server
			b)Client sends a string to the server
			c)Server converts the string to upper  case and sends it back to the Client
			d)Client prints the received string.

	./Q5_client ip port_no
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
	int len;
	int new;
	int data_len;

	char data[MAX_DATA];

	len = sizeof(sa_in);

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

	while(1)
	{
		printf("\nEnter the string : ");
		fgets(data, MAX_DATA, stdin);

		if((data_len = send(sock, data, strlen(data), 0)) == ERROR)
		{
			perror("send : ");
			exit(-1);
		}

		bzero(data, MAX_DATA);

		if((data_len = recv(sock, data, MAX_DATA, 0)) == ERROR)
		{
			perror("recv : ");
			exit(-1);
		}
		
		printf("\nRecieved message from server at %s:%d : \n\n%s\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port), data);
	}	
}