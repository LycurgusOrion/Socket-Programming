/* 
	UDP_SERVER

		1.Write a Client Server program (UDP connection)  in which 
			a)A Client program connects to a Server Program
			b)Server sends the message “HELLO WORLD” to Client
			c)Client prints the message.

	./Q2 port_no
*/

#include "socket.h"

int main(int v, char * arg[])
{
	if(v != 2)
	{
		printf("usage : ./Q1_server port_no\n");
		exit(-1);
	}

	int sock;
	int len;
	int data_len;
	char data[MAX_DATA];
	sa_in server;
	sa_in client;

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR)
	{
		perror("socket : ");
		exit(-1);
	}

	server.sin_family 		= AF_INET;
	server.sin_port 		= htons(atoi(arg[1]));
	server.sin_addr.s_addr 	= INADDR_ANY;
	bzero(&server.sin_zero, 8);

	len = sizeof(sa_in);

	if((bind(sock, (sa *)&server, len)) == ERROR)
	{
		perror("bind : ");
		exit(-1);
	}

	while(1)
	{

		data_len = recvfrom(sock, data, MAX_DATA, 0, (sa *)&client, &len);

		if(data_len == ERROR)
		{
			perror("recieve : ");
			exit(-1);
		}

		printf("\nClient connected at %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

//		data[data_len] = '\0';
//		printf("\nRecieved message from client at port %d and IP %s\t:\t\n%s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr), data);


		fgets(data, MAX_DATA, stdin);

		data_len = sendto(sock, data, strlen(data), 0, (sa *)&client, len);

		if(data_len == ERROR)
		{
			perror("sendto : ");
			exit(0);
		}
	}

}