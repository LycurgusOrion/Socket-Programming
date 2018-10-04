/*
	TCP_CLIENT

		1.Write a Client Server program (TCP connection)  in which 
			a)A Client program connects to a Server Program
			b)Server sends the message “HELLO WORLD” to Client
			c)Client prints the message.

	./chat_app_client ip port_no
*/

#include "socket.h"

int main(int v, char * arg[])
{
	if(v != 3)
	{
		printf("usage : ./Q1_client ip port_no\n");
		exit(-1);
	}

	sa_in rs;
	int sock;
	int len;
	char input[BUFFER];
	char output[BUFFER];

	len = sizeof(sa_in);

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror("socket : ");
		exit(-1);
	}

	rs.sin_family 		= AF_INET;
	rs.sin_port 		= htons(atoi(arg[2]));
	rs.sin_addr.s_addr 	= inet_addr(arg[1]);
	bzero(&rs.sin_zero, 8);

	if((connect(sock, (sa *)&rs, len)) == ERROR)
	{
		perror("connect : ");
		exit(-1);
	}

	while(1)
	{
		fgets(input, BUFFER, stdin);
		send(sock, input, strlen(input), 0);

		if((len = recv(sock, output, BUFFER, 0)) == ERROR)
		{
			perror("recv : ");
			exit(-1);
		}
		output[len] = '\0';
		printf("\nRecieved data from server at IP %s:%d : \n\n%s\n", inet_ntoa(rs.sin_addr), ntohs(rs.sin_port), output);
	}

	close(sock);
}
