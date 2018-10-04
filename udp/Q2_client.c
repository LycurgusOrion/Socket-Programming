/*
	UDP_CLIENT

		1.Write a Client Server program (UDP connection)  in which 
			a)A Client program connects to a Server Program
			b)Server sends the message “HELLO WORLD” to Client
			c)Client prints the message.

	./Q2_client ip port_no
*/

#include "socket.h"

int main(int v, char * arg[])
{
	if(v != 3)
	{
		printf("usage : ./Q1_client ip port_no\n");
		exit(-1);
	}

	int sock;
	int len;
	int data_len;
	char data[MAX_DATA];
	sa_in server;
	sa_in client;

	len = sizeof(sa_in);
	
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR)
	{
		perror("socket : ");
		exit(-1);
	}

	server.sin_family 		= AF_INET;
	server.sin_port			= htons(atoi(arg[2]));
	server.sin_addr.s_addr 	= inet_addr(arg[1]);
	bzero(&server.sin_zero, 8);

	while(1)
	{
//		fgets(data, MAX_DATA, stdin);
		strcpy(data, "\nClient connected!\n");
		data_len = sendto(sock, data, strlen(data), 0, (sa *)&server, len);
		if(data_len == ERROR)
		{
			perror("sendto : ");
			exit(-1);
		}

		data_len = recvfrom(sock, data, MAX_DATA, 0, (sa *)&server, &len);

		if(data_len == ERROR)
		{
			perror("recvfrom : ");
			exit(-1);
		}
		data[data_len] = '\0';
		printf("\nRecieved data from server at IP %s:%d : \n\n%s\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port), data);

	}


}