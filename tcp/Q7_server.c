/*
	TCP_SERVER

		7.Write a Client Server Program (TCP connection) in which
			a)Client sends a File name to the server
			b)The server reads the name of the file, retrieves its contents and sends them to the Client
			c)The Client displays the contents.

	./Q7_server port_no
*/

#include "socket.h"

int main(int v, char * arg[])
{
	if(v != 2)
	{
		printf("\nusage : ./Q7_server port_no\n");
		exit(-1);
	}

	int sock;
	int len;
	int new;
	int data_len;
	int fname_len;
	char fname[MAX_DATA];
	char data[MAX_DATA];
	char ch = ' ';

	sa_in server;
	sa_in client;

	len = sizeof(sa_in);

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror("socket : ");
		exit(-1);
	}

	server.sin_family 		= AF_INET;
	server.sin_port			= htons(atoi(arg[1]));
	server.sin_addr.s_addr 	= INADDR_ANY;
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

		printf("\nNew CLIENT connected at IP %s and PORT %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		
		data_len = 1;

		while(data_len)
		{
			if((fname_len = recv(new, fname, MAX_DATA, 0)) == ERROR)
			{
				perror("recv : ");
				exit(-1);
			}

			fname[fname_len] = '\0';
			printf("\nFile name recieved : %s\n", fname);

			FILE *fp = fopen(fname, "r");
			if(fp == NULL)
			{
				perror("fopen : ");
				data[0] = EOF;
				send(new, data, 1, 0);
				continue;
			} 

			ch = ' ';
			while(ch != EOF)
			{
				if((ch = fgetc(fp)) == EOF)
					data[0] = (char)27;  				//Sending ESC to client in case of EOF
				else
					data[0] = ch;
				if((data_len = send(new, data, 1, 0)) == ERROR)
				{
					perror("send : ");
					exit(-1);
				}
			}
		}

		printf("\nClient Disconnected!\n");
		close(new);
	}
}