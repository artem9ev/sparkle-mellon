// SERVER TCP 
#include <iostream>  
#include <fstream>
#include <winsock2.h> 
#include <windows.h> 
#include <string> 
#pragma comment (lib, "Ws2_32.lib")  
using namespace std;
#define SRV_PORT 1234 // сервер знает свой порт
#define BUF_SIZE 512  

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

int main() {
	setlocale(LC_ALL, "RUS");
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
	{
		cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка!
		return -1;
	}
	int from_len;
	char buf[BUF_SIZE] = { 0 };

	SOCKET s, s_new; // s - сокет сервера, s_new - сокет нового клиента

	sockaddr_in sin, from_sin;
	s = socket(AF_INET, SOCK_STREAM, 0); // создали сокет ()
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SRV_PORT);
	bind(s, (sockaddr*)&sin, sizeof(sin)); // добавляем установленную информацию сокету скрвера
	listen(s, 3); // создаем очередь для принятия 3-х клиентов

	cout << "starting..." << endl;

	Action action;
	bool isConnected;
	char* fileData1 = nullptr, *fileData2 = nullptr;
	ifstream inFile;
	int filePointer = 0;
	ofstream outFile("list.bin", ios::binary | ios::app);
	outFile.close();
	while (1) {
		from_len = sizeof(from_sin);
		s_new = accept(s, (sockaddr*)&from_sin, &from_len); // из очереди извлекает очередного клиента (from_sin - структура куда попадает инф о клиенте)
		isConnected = true;
		cout << "new connected client! " << endl;
		while (isConnected) {

			int result = recv(s_new, (char*)buf, BUF_SIZE, 0);
			if (result == 0)
			{
				isConnected = false;
				break;
			}
			action = *(Action*)buf;
			cout << "----------------------------------------------" << endl;
			float sum = 0;
			int fileSize;
			switch (action)
			{
			case STOP_SESSION:
				cout << "Отключение клиента" << endl;
				isConnected = false;
				break;
			case ADD_STUDENT:
				cout << "Запрос на добавление студента" << endl;
				recv(s_new, (char*)buf, BUF_SIZE, 0);
				newStudent = *(NewStudent*)buf;
				cout << "Добавление студента: " << endl << newStudent.name << endl << newStudent.kurs << " курс" << endl << "Оценки:";
				for (int i = 0; i < 4; i++)
				{
					cout << " " << newStudent.grade[i];
				}
				cout << endl;
				strcpy_s(student.name, newStudent.name);
				cout << "added: " << student.name << endl;
				student.kurs = newStudent.kurs;
				sum = 0;
				student.hasStipendia = true;
				for (int i = 0; i < 4; i++)
				{
					student.grade[i] = newStudent.grade[i];
					sum += student.grade[i];
					if (student.grade[i] <= 3)
					{
						student.hasStipendia = false;
					}
				}
				student.averageGrade = sum / 4.0f;
				outFile.open("list.bin", ios::binary | ios::app);
				outFile.write((char*)&student, sizeof(student));
				outFile.close();
				break;
			case DELETE_STUDENT:
				cout << "Запрос на удаление студента" << endl;
				recv(s_new, (char*)buf, BUF_SIZE, 0);
				requestStudent = *(RequestStudent*)buf;
				inFile.open("list.bin", ios::binary); //открытие файла connection.bin //inFile.seekg(client[i].size, ios::beg);// inFile.read((char*)&B, sizeof(B));
				inFile.seekg(0, ios::end);
				fileSize = inFile.tellg();
				filePointer = 0;
				inFile.seekg(0, ios::beg);
				while (filePointer < fileSize) {
					inFile.read((char*)&student, sizeof(student));
					filePointer = inFile.tellg();
					cout << endl << "Имя: " << student.name << " " << requestStudent.name << endl << "Курс: " << student.kurs << endl << "Ср. балл: " << student.averageGrade << endl;
					cout << (strcmp(student.name, requestStudent.name) == 0) << " " << (student.kurs == requestStudent.kurs) << endl;
					if (strcmp(student.name, requestStudent.name) == 0 && student.kurs == requestStudent.kurs)
					{
						fileData1 = new char[(fileSize - filePointer)];
						fileData2 = new char[(filePointer - sizeof(student))];
						cout << "Начал считывание" << endl;
						inFile.read(fileData2, (fileSize - filePointer));
						inFile.seekg(0, ios::beg);
						inFile.read(fileData1, (filePointer - sizeof(student)));
						inFile.close();
						cout << "Считал все остальное" << endl;
						outFile.open("list.bin", ios::binary | ios::trunc);
						outFile.write(fileData1, (filePointer - sizeof(student)));
						outFile.write(fileData2, (fileSize - filePointer));
						outFile.close();
						break;
					}
				}
				cout << "Конец!" << endl;
				inFile.close();
				break;
			case GIVE_STUDENT:
				cout << "Запрос на получение данных о студенте" << endl;
				recv(s_new, (char*)buf, BUF_SIZE, 0);
				requestStudent = *(RequestStudent*)buf;
				inFile.open("list.bin", ios::binary); //открытие файла connection.bin //inFile.seekg(client[i].size, ios::beg);// inFile.read((char*)&B, sizeof(B));
				inFile.seekg(0, ios::end);
				fileSize = inFile.tellg();
				filePointer = 0;
				inFile.seekg(0, ios::beg);
				while (filePointer < fileSize) {
					inFile.read((char*)&student, sizeof(student));
					filePointer = inFile.tellg();
					cout << endl << "Имя: " << student.name << " " << requestStudent.name << endl << "Курс: " << student.kurs << endl << "Ср. балл: " << student.averageGrade << endl;
					if (strcmp(student.name, requestStudent.name) == 0 && student.kurs == requestStudent.kurs)
					{
						send(s_new, (char*)&student, sizeof(Student), 0);
						break;
					}
				}
				inFile.close();
				break;
			}
		}
		cout << "client is lost";
		closesocket(s_new); // разрываем связь с отключенным клиентом
	}
	return 0;
}
