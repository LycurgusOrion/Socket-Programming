/*
	TCP_SERVER

		3.Write a Client Server program (TCP connection) in which 
			a)Server sends the Date and Time to the client when a Client connects to it 
			b)The Client displays the message.
	
	./Q3_server port_no

*/

#include "socket.h"

int main(int v, char * arg[])
{
	sa_in server, client;
	int sock, len, st, new, tm_len;
	char tm[MAX_DATA];

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

		printf("\nNew CLIENT Connected at %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		t = time(NULL);
		snprintf(tm, sizeof(tm), "%s", ctime(&t));		//ctime returns a string having system day date and time

		tm_len = send(new, tm, sizeof(tm), 0);
		if(tm_len == ERROR)
		{
			perror("send : ");
			exit(-1);
		}

		printf("\nClient disconnected!\n");
		close(new);

	}	
}
