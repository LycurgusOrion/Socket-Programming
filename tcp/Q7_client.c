/*
	TCP_CLIENT

		7.Write a Client Server Program (TCP connection) in which
			a)Client sends a File name to the server
			b)The server reads the name of the file, retrieves its contents and sends them to the Client
			c)The Client displays the contents.

	./Q7_client ip port_no
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

	char data[MAX_DATA], fname[MAX_DATA], ch = ' ';

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
		printf("\n\nEnter the filename : ");
		fgets(fname, MAX_DATA, stdin);

		fname[strlen(fname) - 1] = '\0';

		printf("\nFile Name Entered : %s\n", fname);

		if((data_len = send(sock, fname, strlen(fname) + 1, 0)) == ERROR)
		{
			perror("send : ");
			exit(-1);
		}

		printf("\nThe content of %s are : \n", fname);
		
		ch = ' ';
		while(ch != EOF)
		{			
			if((data_len = recv(sock, data, 1, 0)) == ERROR)
			{
				perror("recv : ");
				exit(-1);
			}
			ch = data[0];
			if(ch == EOF)
				break;
			else
				printf("%c", ch);
		}
	}	
}