

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

WSADATA wsa;
SOCKET recver, sender;
SOCKADDR_IN friendaddr,friendaddr2, thisaddr;

DWORD WINAPI RecverThread(LPVOID);
int main()
{
	WSAStartup(MAKEWORD(2, 2), &wsa);
	recver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	thisaddr.sin_addr.s_addr = htonl(ADDR_ANY);
	thisaddr.sin_family = AF_INET;
	thisaddr.sin_port = htons(8000);
	bind(recver, (SOCKADDR*)& thisaddr, sizeof(SOCKADDR));
	CreateThread(0, 0, RecverThread, &recver, 0, 0);

	friendaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	friendaddr.sin_family = AF_INET;
	friendaddr.sin_port = htons(9000);

	char buff[1024];
	int len = sizeof(friendaddr);

	while (true) {
		printf("geting...!\n");
		gets_s(buff, sizeof(buff));
		sendto(recver, buff, strlen(buff), 0, (SOCKADDR*)&friendaddr, len);
	}

	closesocket(recver);
	closesocket(sender);
	WSACleanup();
}
DWORD WINAPI RecverThread(LPVOID lpParam) {
	SOCKET recver = *(SOCKET*)lpParam;
	char buff[1024];
	int ret;
	int len2 = sizeof(friendaddr2);

	while (true) {
		printf("recving...\n");
		ret = recvfrom(recver, buff, sizeof(buff), 0, NULL, NULL);
		if (ret < 0) continue;
		buff[ret] = 0;
		printf("%s\n", buff);
	}
}

//TODO: check form recvFrom and sendTO