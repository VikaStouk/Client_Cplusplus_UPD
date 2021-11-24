#include "iostream"
#include "Display.h"

using namespace std;
int x = 690;
int main(int argc, char** argv) {
	char buffer[30];
	if (WSAStartup(0x202, (WSADATA*)&buffer[0]))
	{
		printf("WSAStartup error: %d\n", WSAGetLastError());
		return -1;
	}

	// открытие сокета
	SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (my_sock == INVALID_SOCKET)
	{
		printf("socket() error: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	Display display = Display(999, 999);
	std::cout << "width: " << display.getWidth() << " height: " << display.getHeight() << std::endl;

	


	/*display.fillRect(50, 100, 10, 10, RGB(255, 5, 5));
	cout << "Command 5" << endl;
	Sleep(500);
	display.fillRect(100, 100, 20, 20, RGB(0, 120, 74));
	cout << "Command 5" << endl;
	Sleep(500);*/
	display.fillRect(150, 100, 30, 30, RGB(0, 255, 0));
	cout << "Command 5" << endl;
	Sleep(500);
	
	/*display.drawLine(10, 150, 60, 150, RGB(0, 0, 0));
	cout << "Command 3" << endl;
	Sleep(500);
	display.drawLine(70, 150, 60, 150, RGB(0, 0, 0));
	cout << "Command 3" << endl;
	Sleep(500);
	display.drawLine(130, 150, 60, 150, RGB(0, 0, 0));
	cout << "Command 3" << endl;
	Sleep(500);
	display.drawLine(200, 150, 60, 150, RGB(0, 0, 0));
	cout << "Command 3" << endl;
	Sleep(500);

	display.drawEllipse(50, 190, 10, 10, RGB(1, 0, 0));
	cout << "Command 6" << endl;
	Sleep(500);
	display.drawEllipse(100, 180, 20, 20, RGB(0, 0, 0));
	cout << "Command 6" << endl;
	Sleep(500);
	display.drawEllipse(150, 170, 30, 30, RGB(0, 0, 0));
	cout << "Command 6" << endl;
	Sleep(500);

	display.fillEllipse(210, 120, 50, 50, RGB(0, 0, 0));
	cout << "Command 6" << endl;
	Sleep(500);
	display.drawEllipse(210, 115, 60, 60, RGB(0, 0, 0));
	cout << "Command 6" << endl;
	Sleep(500);


	display.drawText(10, 10, "Abstraction", RGB(0, 0, 0), RGB(0, 0, 0), 12);*/
	getchar();
	return 0;
}
