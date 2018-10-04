/*
	TCP_SERVER

		5.Write a Client Server program (TCP connection)  in which 
			a)Client connects to a server
			b)Client sends a string to the server
			c)Server converts the string to upper  case and sends it back to the Client
			d)Client prints the received string.

	./Q5_server port_no
*/

#include "socket.h"

int main(int v, char * arg[])
{
	if(v != 2)
	{
		printf("usage : ./Q5_server port_no\n");
		exit(-1);
	}

	sa_in server, client;
	int sock, len, st, new, data_len, i;
	char data[MAX_DATA];

	len = sizeof(sa_in);
	
	time_t t;
	//struct tm *tm = localtime(&t);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket : ");
		exit(-1);
	}

	server.sin_family		=	AF_INET;
	server.sin_port			=	htons(atoi(arg[1]));
	server.sin_addr.s_addr 	=	INADDR_ANY;
	bzero(&server.sin_zero, 8);

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

		printf("\nNew CLIENT connected at %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		data_len = 1;
		
		while(data_len)
		{
			if((data_len = recv(new, data, MAX_DATA, 0)) == ERROR)
			{
				perror("recv : ");
				exit(-1);
			}

			data[data_len] = '\0';
			for(i = 0 ; i < strlen(data) ; i++)
				if(islower(data[i]))
					data[i] = toupper(data[i]);

			if((data_len = send(new, data, strlen(data), 0)) == ERROR)
			{
				perror("send : ");
				exit(-1);
			}
	
		}
		
		printf("\nClient disconnected!\n");
		close(new);
	}
}