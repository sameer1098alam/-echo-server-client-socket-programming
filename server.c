
#include<stdio.h>
#include<winsock.h>
#define PORT 5505
struct sockaddr_in server_address;

int main()
{
	int n=0;
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
	{
		printf("WSA failed to initialize:%d\n",errno);
		return -1;
	}
	else
	{
		printf("WSA initialized\n");
	}

	int nSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (nSocket < 0)
	{
		printf("Socket not opened:%d",errno);
		return -1;
		
	}
	else
	{
		printf("Socket opened successfully\n");
		printf("Socket ID is %d\n", nSocket);
	}
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	memset(&(server_address.sin_zero), 0, 8);
	n = bind(nSocket, (struct sockaddr *)&server_address, sizeof(server_address));
	if (n < 0)
	{
		printf("Failed to bind to local port:%d\n",errno);
		return -1;
	}
	else {
		printf("Successfully bind to local port\n");
	}

	n = listen(nSocket, 5);
	if (n < 0)
	{
		printf("Fail to start listen to local port:%d\n",errno);
		return -1;
	}
	else {
		printf("Started listening to local port\n");
	}
	

	int nLen = sizeof(server_address);
	int nClientSocket = accept(nSocket, (struct sockaddr*)&server_address, &nLen);
	if (nClientSocket < 0)
	{
		printf("Cannot accept client at port:%d\n", errno);
		return -1;
	}

	while (1)
	{
		char buff[1024] = { 0, };
		n = recv(nClientSocket, buff, 1024, 0);
		if (n < 0)
		{
			printf("Cannot receive messsgae:%d", errno);
			break;
		}
		printf("%s\n", buff);

		char buff1[1024] = { 0, };
		fgets(buff1, 1023, stdin);
		send(nClientSocket, buff1, strlen(buff1), 0);
	}
	closesocket(nSocket);
		
	return 0;
}
