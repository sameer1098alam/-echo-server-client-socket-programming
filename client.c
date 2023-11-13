#include<stdio.h>
#include<winsock.h>
#define PORT 5505
struct sockaddr_in srv;

int main()
{
	int n = 0;
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
	{
		printf("WSA failed to initialize");
		WSACleanup();
		return(EXIT_FAILURE);
	}
	else
	{
		printf("WSA initialized\n");
	}

	int nClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (nClientSocket < 0)
	{
		printf("Socket not opened");
		return -1;
	}
	else
	{
		printf("Socket opened successfully\n");
		printf("Socket ID is %d\n", nClientSocket);
	}
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");

	//srv.sin_addr.s_addr = inet_addr("10.1.62.102");
	memset(&(srv.sin_zero), 0, 8);
	
	n = connect(nClientSocket, (struct sockaddr *)&srv, sizeof(srv));
	if (n < 0)
	{
		printf("Connection failed.\n");
		return -1;
	}
	else
	{
		printf("Connected to the server\n");
	}
	
	while (1)
	{
		char buff[1024] = { 0, };
		fgets(buff, 1023,stdin);
		if (strcmp(buff, "exit\n") == 0)
		{
			break;
		}
		send(nClientSocket, buff, strlen(buff), 0);

		char buff1[1024] = { 0, };
		n = recv(nClientSocket, buff1, 1024, 0);
		printf("%s\n", buff1);
	}
	closesocket(nClientSocket);
	
	return 0;
}