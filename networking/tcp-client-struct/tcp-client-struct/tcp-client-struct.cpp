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
#define SRV_HOST "192.168.0.13"  
#define SRV_PORT 1234 
#define CLNT_PORT 1235  
#define BUF_SIZE 512 // размер буффера памяти для обмена сообщениями

enum Action {
	STOP_SESSION = 0,
	ADD_STUDENT = 1,
    DELETE_STUDENT = 2,
	GIVE_STUDENT = 3,
};

struct NewStudent {
	char name[64];
	int kurs;
	int grade[4];
} newStudent;

struct RequestStudent {
	char name[64];
	int kurs;
} requestStudent;

struct Student {
	char name[64];
	int kurs;
	int grade[4];
	float averageGrade;
	bool hasStipendia;
} student;

int main(){;
    setlocale(LC_ALL, "RUS");

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
	cout << "Подключен к серверу" << endl;
	
	Action action = STOP_SESSION;

	cout << "Доступные действия:\n0. Отключиться\n1. Добавить студента в список\n2. Удалить студента из списка\n3. Запросить данные о студенте" << endl;
	// общение
	do {
		int inputAction;
		cout << endl << "Введите действие: ";
		cin >> inputAction;
		action = (Action)inputAction;
		switch (action)
		{
		case STOP_SESSION:
			break;
		case ADD_STUDENT:
			cout << "Введите имя студента: "; cin >> newStudent.name;
			newStudent.name[63] = '\0';
			cout << "Введите курс: "; cin >> newStudent.kurs;
			cout << "Введите его оценки: " << endl;
			for (int i = 0; i < 4; i++)
			{
				cout << i << ": ";
				cin >> newStudent.grade[i];
				if (newStudent.grade[i] > 5 || newStudent.grade[i] < 2)
				{
					cout << "Недопустиммые данные! Введите заново: " << endl;
					i--;
				}
			}
			send(s, (char*)&action, sizeof(action), 0);
			send(s, (char*)&newStudent, sizeof(newStudent), 0);
			break;
		case DELETE_STUDENT:
			cout << "Введите имя студента: "; cin >> requestStudent.name;
			requestStudent.name[63] = '\0';
			cout << "Введите курс: "; cin >> requestStudent.kurs;
			send(s, (char*)&action, sizeof(action), 0);
			send(s, (char*)&requestStudent, sizeof(requestStudent), 0);
			break;
		case GIVE_STUDENT:
			cout << "Введите имя студента: "; cin >> requestStudent.name;
			requestStudent.name[63] = '\0';
			cout << "Введите курс: "; cin >> requestStudent.kurs;
			send(s, (char*)&action, sizeof(action), 0);
			send(s, (char*)&requestStudent, sizeof(requestStudent), 0);
			recv(s, (char*)buf, BUF_SIZE, 0);
			student = *(Student*)buf;
			cout << endl << "Студент: " << student.name << endl << "Курс: " << student.kurs << endl << "Оценки: " << student.grade[0] << " " <<
				student.grade[1] << " " << student.grade[2] << " " << student.grade[3] << endl << "Ср. балл: " << student.averageGrade << endl <<
				(student.hasStipendia ? "Есть стипендия" : "Нет стипендии") << endl;
			break;
		}
	} while (action != STOP_SESSION);
	cout << "exit to infinity" << endl;
	cin.get();    
	closesocket(s);
	return 0;
}
