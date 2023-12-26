
// Client Chat
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

SOCKET Connection;
enum Packet // Допустимые типы пакетов
{
	Pack,
	Test
};

// Дополнительный поток клиента для отправки сообщений
DWORD WINAPI ClientThread(LPVOID sock)
{
	SOCKET Con = ((SOCKET*)sock)[0];
	Packet packettype;
	// Получение пакетов от сервера
	while (1)
	{
		recv(Con, (char*)&packettype, sizeof(Packet), NULL);
		// Прием типа пакета
		if (packettype == Pack)
		{
			cout << "полученный пакет PACK" << endl;
			int msg_size;
			recv(Con, (char*)&msg_size, sizeof(int), NULL);
			char* msg = new char[msg_size + 1];
			msg[msg_size] = '\0';
			// Приём данных пакета
			recv(Con, msg, msg_size, NULL);
			cout << msg << endl;
			delete[]msg;
		}
		else
		{
			if (packettype == Test)
				// Приём сигнального пакета от сервера
				cout << "Test packet.\n";
			else
			{
				// Тип сокета не определен
				cout << "Неопределенный пакет: " << packettype << endl;
				break;
			}
		}

	}
	closesocket(Connection);
	return 0;
}

int main()// Основной поток
{
	setlocale(LC_ALL, "Rus");
	WSAData wsaData;
	WORD Ver = MAKEWORD(2, 1);
	if (WSAStartup(Ver, &wsaData) != 0)
	{
		cout << "Ошибка" << endl;
		exit(1);
	}
	// Определение параметров сервера
	sockaddr_in addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// Обратная петля(направить трафик самому себе)
	addr.sin_port = htons(123);
	addr.sin_family = AF_INET;
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	// Соединенине с сервером
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Ошибка: Неправильное подключение к серверу.\n";
		return 1;
	}
	cout << "Подключён!\n";
	// Создание дочернего потока для приема сообщений от сервера
	CreateThread(NULL, NULL, ClientThread, &Connection, NULL, NULL);
	// Отправка данных серверу в основном потоке
	string msg1;
	while(true)
	{
		getline(cin, msg1);
		int msg_size = msg1.size();
		// Передача информационного пакета
		Packet packettype = Pack;
		send(Connection, (char*)&packettype, sizeof(Packet), NULL);
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, (char*)&msg1[0], msg_size, NULL);
		Sleep(100);
	}
	system("pause");
	return 0;
}