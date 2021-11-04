#ifndef Display_h
#define Display_h

#define PORT 15000
#define SERVERADDR "127.0.0.1"



#ifndef R_RGB
#define R_RGB(r) ((r&0xF800) >> 8) //R_RGB565: 5 red | 6 green | 5 blue
#endif

#ifndef G_RGB
#define G_RGB(g) ((g&0x7E0) >> 3) //G_RGB565: 5 red | 6 green | 5 blue
#endif

#ifndef B_RGB
#define B_RGB(b) ((b&0x1F) << 3) //B_RGB565: 5 red | 6 green | 5 blue
#endif



#include <iostream>
#include "stdio.h"
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <string>
#include <sstream>
#include "GraphicsLib.h"

#pragma warning (disable:4996)
#pragma comment (lib, "ws2_32.lib")

using namespace std;


class Display : public GraphicsLib
{
public:
	Display(uint_least16_t w, uint_least16_t h) : GraphicsLib(w, h)
	{

		// открытие сокета
		my_sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (my_sock == INVALID_SOCKET)
		{
			printf("socket() error: %d\n", WSAGetLastError());
			WSACleanup();
		}
		// обмен сообщений с сервером
		HOSTENT* hst;

		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(PORT);

		// определение IP-адреса узла
		if (inet_addr(SERVERADDR))
			dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
		else
			if (hst = gethostbyname(SERVERADDR))
				dest_addr.sin_addr.s_addr = ((unsigned long**)hst->h_addr_list)[0][0];
			else
			{
				printf("Unknown host: %d\n", WSAGetLastError());
				closesocket(my_sock);
				WSACleanup();
			}
	};

	void fillScreen(uint_least16_t color) {
		snprintf(buffer, buffer_length, "#1#0x%06x$", color);
		sendCommand(buffer);
	};

	void drawPixel(int_least16_t x0, int_least16_t y0, uint_least16_t color) {
		snprintf(buffer, buffer_length, "#2#%03d%03d%03d%03d%03d$", x0, y0, R_RGB(color), G_RGB(color), B_RGB(color));
		sendCommand(buffer);
	};

	void drawLine(int_least16_t x0, int_least16_t y0, int_least16_t x1, int_least16_t y1, uint_least16_t color) {
		snprintf(
			buffer, buffer_length, "#3#%03d%03d%03d%03d%03d%03d%03d$", x0, y0, x1, y1, R_RGB(color), G_RGB(color), B_RGB(color)
		);
		sendCommand(buffer);
	};

	void drawRect(int_least16_t x0, int_least16_t y0, int_least16_t w, int_least16_t h, uint_least16_t color) {
		snprintf(
			buffer, buffer_length, "#4#%03d%03d%03d%03d%03d%03d%03d$", x0, y0, w, h, R_RGB(color), G_RGB(color), B_RGB(color)
		);
		sendCommand(buffer);
	};

	void fillRect(int_least16_t x0, int_least16_t y0, int_least16_t w, int_least16_t h, uint_least16_t color) {
		snprintf(
			buffer, buffer_length, "#5#%03d%03d%03d%03d%03d%03d%03d$", x0, y0, w, h, R_RGB(color), G_RGB(color), B_RGB(color)
		);
		sendCommand(buffer);
	};

	void drawEllipse(int_least16_t x0, int_least16_t y0, int_least16_t r_x, int_least16_t r_y, uint_least16_t color) {
		snprintf(
			buffer, buffer_length, "#6#%03d%03d%03d%03d%03d%03d%03d$", x0, y0, r_x, r_y, R_RGB(color), G_RGB(color), B_RGB(color)
		);
		sendCommand(buffer);
	};

	void fillEllipse(int_least16_t x0, int_least16_t y0, int_least16_t r_x, int_least16_t r_y, uint_least16_t color) {
		snprintf(
			buffer, buffer_length, "#7#%03d%03d%03d%03d%03d%03d%03d$", x0, y0, r_x, r_y, R_RGB(color), G_RGB(color), B_RGB(color)
		);

		sendCommand(buffer);
	};

	int_least16_t drawChar(int_least16_t x, int_least16_t y, char c, uint_least16_t color, uint_least16_t bg, uint_least8_t size) {
		snprintf(
			buffer, buffer_length, "#8#%03d%03d%03d%03d%03d%03d%03d$", x, y, size, c, R_RGB(color), G_RGB(color), B_RGB(color)
		);
		sendCommand(buffer);
		return x + 1.5 * size;
	}

	int_least16_t drawChar(int_least16_t x, int_least16_t y, unsigned char c, uint_least16_t color, uint_least16_t bg, uint_least8_t size) {
		return drawChar(x, y, (char)c, color, bg, size);
	}

	int_least16_t drawText(int_least16_t x, int_least16_t y, const char* s, uint_least16_t color, uint_least16_t bg, uint_least8_t size) {
		while (*s != 0) {
			x = drawChar(x, y, (char)*s++, color, bg, size);
			if (x > getWidth()) {
				break;
			}
		}
		return x;
	}

private:
	static const unsigned char buffer_length = 80;
	char buffer[buffer_length];
	sockaddr_in dest_addr;
	SOCKET my_sock;

	void sendCommand(const char* command) {
		std::cout << command << std::endl;
		sendto(my_sock, &command[0], strlen(&command[0]), 0, (sockaddr*)&dest_addr, sizeof(dest_addr));
	}
};

#endif //Display_h
