#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#pragma comment(lib,"Ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;
#define request "GET/ HTTP/1,1\r\n Host: localhost \r\n\r\n"
//html запрос
#define max_packet_size 65535
// "GET/ HTTP/1.1\r\n HOST: www.json.org \r\n\r\n" port = 80 host_name = "www.json.org"

int main()
{
	WSADATA ws;
	SOCKET s;
	sockaddr_in adr;
	HOSTENT* hn;
	char buff[max_packet_size];
	// Инициализация
	if (WSAStartup(0x0202, &ws) != 0)
	{
		return -1;// ERROR
	}
	// Создаём сокет
	if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_STREAM, 0)))
	{
		return -1;// ERROR
	}
	// Получаем адрес
	if (NULL == (hn = gethostbyname("localhost")))
	{
		return -1;// ERROR
	}
	// Заполняем поля структуры adr для использования её в connect
	adr.sin_family = AF_INET;
	((unsigned long*)&adr.sin_addr)[0] = ((unsigned long**)hn->h_addr_list)[0][0];
	adr.sin_port = htons(8000);
	//устанавливаем соединение с сервером
	if (SOCKET_ERROR == connect(s, (sockaddr*)&adr, sizeof(adr)))
	{
		int res=WSAGetLastError();// ERROR
			return -1;
	}
	if (SOCKET_ERROR == send(s, (char*)&request, sizeof(request), 0))
	{
		int res = WSAGetLastError();// ERROR
		return -1;
	}
	// Ждём ответа
	int len = 0;
	do {
		if (SOCKET_ERROR == (len = recv(s, (char*)&buff, max_packet_size, 0)))
		{
			int res = WSAGetLastError();
			return -1;
		}
		buff[len] = 0;
		cout << buff;
	} while (len != 0);
	// Получаем данные по частям, пока не len != 0
	// Закрываем соединение
	if (SOCKET_ERROR == closesocket(s))
	{
		return -1; // ERROR
		return 0;
	}
}
