// SERVER TCP 
#include <iostream>  
#include <winsock2.h> 
#include <windows.h> 
#include <string> 
#pragma comment (lib, "Ws2_32.lib")  
using namespace std;
#define SRV_PORT 1234 // сервер знает свой порт
#define BUF_SIZE 512  

struct Message {
	char text[512];
	int id = 0;
};

int main() {
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
	{
		cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка!
		return -1;
	}
	SOCKET s, s_new; // s - сокет сервера, s_new - сокет нового клиента
	int from_len = 0; //
	char buf[BUF_SIZE] = { 0 };
	sockaddr_in sin, from_sin; // 
	s = socket(AF_INET, SOCK_STREAM, 0); // создали сокет ()
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SRV_PORT);
	bind(s, (sockaddr*)&sin, sizeof(sin)); // добавляем установленную информацию сокету скрвера
	Message msg, clientMsg;
	listen(s, 3); // создаем очередь для принятия 3-х клиентов
	while (1) {
		from_len = sizeof(from_sin);
		s_new = accept(s, (sockaddr*)&from_sin, &from_len); // из очереди извлекает очередного клиента (from_sin - структура куда попадает инф о клиенте)
		cout << "new connected client! " << endl;
		//msg.text = "Hello!";
		strcpy_s(msg.text, "Hello!");
		while (1) {
			cout << "send-" << sizeof(msg) << endl;
			send(s_new, (char*)&msg, sizeof(msg), 0); // посылаем сообщение
			from_len = recv(s_new, (char*)buf, BUF_SIZE, 0);
			//buf[from_len] = 0;
			cout << "got ";
			clientMsg = *(Message*)buf;
			cout << sizeof(clientMsg);
			cout << " client: " << clientMsg.text << endl;
			if (clientMsg.text == "Bye") break; // прерываю диалог с этим клиентом
			cout << "input: ";
			cin.getline(msg.text, sizeof(msg.text));
		}
		cout << "client is lost";
		closesocket(s_new); // разрываем связь с отключенным клиентом
	}
	return 0;
}
