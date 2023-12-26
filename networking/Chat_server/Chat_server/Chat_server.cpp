#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

SOCKET Connections[100]; // Массив сокетов активных клиентов
int Count_of_live_clients = 0; // Число активных клиентов
enum Packet // Допустимые типы пакетов
{
	Pack,
	Test
};

// Функционал потока отдельного клиента
DWORD WINAPI ServerThread(LPVOID number)
{
	Packet packettype;
	// Определение номера сокета клиента
	int index = ((int*)number)[0];
	cout << "Номер сокета= " << index << endl;
	SOCKET Con = Connections[index];
	// Начало общения с клиентом
	while (true)
	{
		//Получение информации от клиента
		recv(Con, (char*)&packettype, sizeof(Packet), NULL);
		// определение типа полученного пакета
		if (packettype == Pack)
		{
			cout << "полученный пакет PACK" << endl;
			int msg_size;
			// Определение объема пакета
			recv(Con, (char*)&msg_size, sizeof(int), NULL);
			//Резервирование буфера нужного размера для принятия пакета
			char* msg = new char[msg_size + 1];
			msg[msg_size] = 0;
			// Получение пакета
			recv(Con, msg, msg_size, NULL);
			cout << msg << endl;
			// Передача полученного сообщения другим участникам чата
			for (int i = 0; i < Count_of_live_clients; i++)
			{
				if (i == index) continue;
				Packet msgtype = Pack;
				//Передача типа, объема и содержания информационного пакета
				send(Connections[i], (char*)&msgtype, sizeof(Packet), NULL);// Передача типа
				send(Connections[i], (char*)&msg_size, sizeof(int), NULL);// Передача объема
				send(Connections[i], msg, msg_size, NULL);// Передача содержания
			}
			delete[]msg;
		}
		else
		{
			// Получен неопознанный пакет
			cout << "Неопознанный пакет: " << packettype << endl;
			break;
		}
	}
	closesocket(Con);
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	// Инициализация Sinsock
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Ошибка" << endl;
		exit(1);
	}
	//сохранение в слушающем сокете информации о сервере
	sockaddr_in addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(123);
	addr.sin_family = AF_INET;
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	// Режим прослушивания, организация очереди
	listen(sListen, 10);
	SOCKET newConnection;
	for (int i = 0; i < 10; i++)
	{
		// Извлечение запросов из очереди
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0)
		{
			cout << "Error #2\n";// Ошибка подключения
		}
		else
		{
			// Приветствие нового подключившегося клиента
			cout << "Новый подключившийся клиент\n";
			string msg = "Добро пожаловать в чат!";
			int msg_size = msg.size();
			// Передача клиенту пакета типа Pack
			Packet msgtype = Pack;
			send(newConnection, (char*)&msgtype, sizeof(Packet), NULL);// Передача типа
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);// Передача объема
			send(newConnection, (char*)&msg[0],msg_size, NULL);// Передача содержания
			// Сохранение сокета клиента в массиве участников чата
			Connections[i] = newConnection;
			Count_of_live_clients++;
			// количество участников учеличивается
			cout << "Количество= " << Count_of_live_clients << endl;

			// Создание нового потока для обслуживания клиента
			CreateThread(NULL, NULL, ServerThread, &i, NULL, NULL);
			Sleep(100);
			// Передача клиенту сигнального сообщения
			Packet testpacket = Test;
			cout << "Тип пакета=TEST" << endl;
			send(newConnection, (char*)&testpacket, sizeof(Packet),NULL);
		}
	}
	system("pause");
	return 0;
}