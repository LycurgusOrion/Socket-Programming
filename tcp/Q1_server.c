/* 
	TCP_SERVER

		1.Write a Client Server program (TCP connection)  in which 
			a)A Client program connects to a Server Program
			b)Server sends the message “HELLO WORLD” to Client
			c)Client prints the message.

	./Q1_server port_no
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

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)			//Socket Created
	{
		perror("socket : ");
		exit(-1);
	}

	//Filling Server structure

	server.sin_family 		= AF_INET;								//Family type
	server.sin_port 		= htons(atoi(arg[1]));					//Port taken from the user
	server.sin_addr.s_addr 	= INADDR_ANY;							//To listen for clients on any ip adress
	bzero(&server.sin_zero, 8);										//Initializing padding string

	len = sizeof(sa_in);

	if((bind(sock, (sa *)&server, len)) == ERROR)					//Binding the server to the socket
	{
		perror("bind : ");
		exit(-1);
	}

	if((listen(sock, MAX_CLIENTS)) == ERROR)					//Listening for clients
	{
		perror("listen : ");
		exit(-1);
	}

	while(strcmp(data, EXIT) != 0)
	{
		if((new = accept(sock, (sa *)&client, &len)) == ERROR)	//Connecting to a client
		{
			perror("accept : ");
			exit(-1);
		}

		printf("\nNew Client connected at %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		data_len = 1;

		while(strcmp(data, EXIT) != 0)
		{
			//data_len = recv(new, data, MAX_DATA, 0);
			//data[data_len - 1] = '\0';

			//printf("\n%d %d %s %s\n", cmp, strcmp(data, EXIT), EXIT, data);
			//if(strcmp(data, EXIT) == 0)
			//	break;

			//if(data_len)	
			//{
			//	data[data_len] = '\0';
			//	printf("\n%s\n", data);
			//}

			fgets(data, MAX_DATA, stdin);
			data[strlen(data) - 1] = '\0';						
			//printf("\n%d\n", strcmp(data, EXIT));

			data_len = strlen(data);							

			if(data_len)
				send(new, data, data_len, 0);					//Sending entered string to the client
			
			if(strcmp(data, EXIT) == 0)
			{
				//printf("\nClient Disconnected!\n");
				//close(new);
				break;		
			}	
		}

		printf("\nClient Disconnected!\n");
		close(new);												//Disconnecting the client
		
		fgets(data, MAX_DATA, stdin);
		data[strlen(data) - 1] = '\0';
		if(strcmp(data, EXIT) == 0)
			break;
	}

}