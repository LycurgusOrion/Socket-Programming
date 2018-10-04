/*
	UDP_SERVER

		3.Write a Client Server program (UDP connection) in which 
			a)Server sends the Date and Time to the client when a Client connects to it 
			b)The Client displays the message.

	./Q4_server.c port_no
*/

#include "socket.h"

int main(int v, char * arg[])
{
	if(v != 2)
	{
		printf("usage : ./Q4_server port_no\n");
		exit(-1);
	}
	int sock;
	int len;
	int data_len;
	char data[MAX_DATA], s[MAX_DATA];

	sa_in server;
	sa_in client;

	time_t t;

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

	while(1)
	{
		if((data_len = recvfrom(sock, data, MAX_DATA, 0, (sa *)&client, &len)) == ERROR)
		{
			perror("recieve : ");
			exit(-1);
		}

		printf("\nNew CLIENT Connected at %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		t = time(NULL);
		snprintf(s, sizeof(s), "%s", ctime(&t));

		if((data_len = sendto(sock, s, strlen(s), 0, (sa *)&client, len)) == ERROR)
		{
			perror("sendto : ");
			exit(-1);
		}
	}
}