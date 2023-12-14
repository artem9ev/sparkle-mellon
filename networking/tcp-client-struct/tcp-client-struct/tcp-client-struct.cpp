//#include <stdafx.h> // CLIENT TCP
#include <iostream>  
#define _WINSOCK_DEPRECATED_NO_WARNINGS  
// подавление предупреждений библиотеки winsock2
#include <winsock2.h> 
#include <string>
#include <windows.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable: 4996)  // подавление предупреждения 4996 
using namespace std;
#define SRV_HOST "localhost"  
#define SRV_PORT 1234 
#define CLNT_PORT 1235  
#define BUF_SIZE 512 // размер буффера памяти для обмена сообщениями

struct Message {
	char text[512];
	int id = 0;
} message;

int main() {
	char buff[1024]; // массив занимающий 1кб
	if (WSAStartup(0x0202, (WSADATA*)&buff[0])) { // подключаем библиотеку версии ..
		cout << "Error WSAStartup \n" << WSAGetLastError();  // Ошибка!
		return -1;
	}
	SOCKET s; // указатель на сруктуру сокета
	int from_len; // длина какой-то  там памяти
	char buf[BUF_SIZE] = { 0 }; //
	hostent* hp; // справочная структура какая-то..
	sockaddr_in clnt_sin, srv_sin; // структура для инф сокета клиента и структура для инф сокета сервера
	s = socket(AF_INET, SOCK_STREAM, 0); // 1 - домен, 2 - потоковое соеденение, 3 - 0 => tcp
	clnt_sin.sin_family = AF_INET; // домен
	clnt_sin.sin_addr.s_addr = 0; // кладем адрес текущего компьютера (значение 0 - автоматически заставляет определить его)
	clnt_sin.sin_port = htons(CLNT_PORT); // задаем порт сокету
	bind(s, (sockaddr*)&clnt_sin, sizeof(clnt_sin)); // кладет всю инф из clnr_sin в s
	hp = gethostbyname(SRV_HOST); // получили хост сервера по имени
	srv_sin.sin_port = htons(SRV_PORT); // помещаем порт
	srv_sin.sin_family = AF_INET; // домен
	((unsigned long*)&srv_sin.sin_addr)[0] =
		((unsigned long**)hp->h_addr_list)[0][0]; // поместили адремм
	connect(s, (sockaddr*)&srv_sin, sizeof(srv_sin)); // клиент связывается с сервером
	Message serv_msg;
	// общение
	do {
		cout << "got ";
		from_len = recv(s, (char*)&buf, BUF_SIZE, 0); // ждет получения данных в буффер от сервера (2-ой параметр указывает куда сохр)
		//buf[from_len] = 0; // закрываем буффер с помощью 0
		cout << "- " << ((*(Message*)buf).text != string()) << " - ";
		serv_msg = *(Message*)*buf;
		cout << sizeof(serv_msg.text);
		cout << " serv: " << serv_msg.id << " - " << serv_msg.text << endl;
		cout << "input: ";
		cin.getline(message.text, sizeof(message.text)); // считываем ответ клиента с клавиатуры
		message.id++;
		int msg_size = sizeof(message);
		cout << "message size: " << msg_size << endl;
		cout << "text size: " << sizeof(message.text) << endl;
		send(s, (char*)&message, msg_size, 0); // посылаем ответ серверу
	} while (message.text != "Bye");
	cout << "exit to infinity" << endl;
	cin.get();    closesocket(s);
	return 0;
}
