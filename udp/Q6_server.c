/*
	UDP_SERVER

		5.Write a Client Server program (UDP connection)  in which 
			a)Client connects to a server
			b)Client sends a string to the server
			c)Server converts the string to upper  case and sends it back to the Client
			d)Client prints the received string.

	./Q6_server port_no
*/

#include "socket.h"

int main(int v, char * arg[])
{
	if(v != 2)
	{
		printf("usage : ./Q6_server port_no\n");
		exit(-1);
	}
	int sock;
	int len;
	int data_len;
	int i;
	char data[MAX_DATA];

	sa_in server;
	sa_in client;

	len = sizeof(sa_in);

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR)
	{
		perror("socket : ");
		exit(-1);
	}

	server.sin_family 		= 	AF_INET;
	server.sin_port 		= 	htons(atoi(arg[1]));
	server.sin_addr.s_addr 	= 	INADDR_ANY;
	bzero(&server.sin_zero, 8);

	if((bind(sock, (sa *)&server, len)) == ERROR)
	{
		perror("bind : ");
		exit(-1);
	}

	data_len = 1;
	while(data_len)
	{
		if((data_len = recvfrom(sock, data, MAX_DATA, 0, (sa *)&client, &len)) == ERROR)
		{
			perror("recieve : ");
			exit(-1);
		}

		printf("\nCLIENT Connected at %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		data[data_len] = '\0';
		for(i = 0 ; i < strlen(data) ; i++)
			if(islower(data[i]))
				data[i] = toupper(data[i]);

		if((data_len = sendto(sock, data, strlen(data), 0, (sa *)&client, len)) == ERROR)
		{
			perror("sendto : ");
			exit(-1);
		}
	}
}