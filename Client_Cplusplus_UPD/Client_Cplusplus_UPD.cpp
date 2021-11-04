//#include <iostream>
//#include <string.h>
//#include <winsock2.h>
//#include <windows.h>
//#include "GraphicsLib.h"
//
//#pragma warning (disable:4996)
//#pragma comment (lib, "ws2_32.lib")
//
//using namespace std;
//
//#define PORT 15000
//#define SERVERADDR "127.0.0.1"
//
//int main(int argc, char* argv[])
//{
//	string input;
//	char buff[30];
//	printf("UDP Client\n");
//
//	// иницилизация библиотеки Winsocks
//	if (WSAStartup(0x202, (WSADATA*)&buff[0]))
//	{
//		printf("WSAStartup error: %d\n", WSAGetLastError());
//		return -1;
//	}
//
//	// открытие сокета
//	SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
//	if (my_sock == INVALID_SOCKET)
//	{
//		printf("socket() error: %d\n", WSAGetLastError());
//		WSACleanup();
//		return -1;
//	}
//
//	// обмен сообщений с сервером
//	HOSTENT* hst;
//	sockaddr_in dest_addr;
//
//	dest_addr.sin_family = AF_INET;
//	dest_addr.sin_port = htons(PORT);
//
//	// определение IP-адреса узла
//	if (inet_addr(SERVERADDR))
//		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
//	else
//		if (hst = gethostbyname(SERVERADDR))
//			dest_addr.sin_addr.s_addr = ((unsigned long**)hst->h_addr_list)[0][0];
//		else
//		{
//			printf("Unknown host: %d\n", WSAGetLastError());
//			closesocket(my_sock);
//			WSACleanup();
//			return -1;
//		}
//
//	while (1)
//	{
//		// чтение сообщения с клавиатуры
//		printf("S<=C:");
//		cin >> &buff[0];
//		cin.ignore(32767, '\n');
//		if (!strcmp(&buff[0], "quit\n")) break;
//
//		// Передача сообщений на сервер
//		sendto(my_sock, &buff[0], strlen(&buff[0]), 0, (sockaddr*)&dest_addr, sizeof(dest_addr));
//
//	}
//
//	// выход
//	closesocket(my_sock);
//	WSACleanup();
//
//	return 0;
//}