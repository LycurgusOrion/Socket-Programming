/* 
	TCP_SERVER

		1.Write a Client Server program (TCP connection)  in which 
			a)A Client program connects to a Server Program
			b)Server sends the message “HELLO WORLD” to Client
			c)Client prints the message.

	./chat_app_server port_no
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
	int new;
	int data_len;
	char data[MAX_DATA];
	sa_in server;
	sa_in client;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
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

	if((listen(sock, MAX_CLIENTS)) == ERROR)
	{
		perror("listen : ");
		exit(-1);
	}

	while(1)
	{
		if((new = accept(sock, (sa *)&client, &len)) == ERROR)
		{
			perror("accept : ");
			exit(-1);
		}

		printf("\nNew Client connected at %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		data_len = 1;

		while(data_len)
		{
			data_len = recv(new, data, MAX_DATA, 0);

			if(data_len)	
			{
				data[data_len] = '\0';
				printf("\nRecieved data from client at IP %s:%d : \n\n%s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), data);
			}

			fgets(data, MAX_DATA, stdin);
			data_len = strlen(data);

			if(data_len)
				send(new, data, data_len, 0);

		}

		printf("\nClient Disconnected!\n");

		close(new);
	}

}