#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Person // структура данных запроса клиента
{
	char name[25];  //имя
	int grade[4];
} A;

void main() {
	setlocale(LC_ALL, "rus");

	int seed = time(NULL);
	srand(time(NULL));

	bool isWaiting = false;
	long fileSize = 0;
	int answer = 0;

	string path = "F:/bread/in-class practice/networking/messages/";
	string registrationFile = path + "connection.bin";
	string clientName = to_string(rand() * (int)(sin(time(NULL)) + 2)); // имя клиента

	ofstream outConnect;
	ofstream outFile;
	ifstream inFile;

	outFile.open(path + clientName + ".bin", ios::app | ios::binary);
	outFile.close();

	outConnect.open(registrationFile, ios::app | ios::binary); //открытие файла connection.bin
	outConnect.write((char*)&clientName, sizeof(clientName)); // отписался серверу для подключения
	outConnect.close();
	cout << "client name: " << (clientName) << endl;

	cout << "Файл создан" << endl;
	cout << "Начало работы" << endl;
	while (true)
	{
		if (isWaiting == false) // если не в режиме ожидания, то отправляем запрос
		{
			cout << "Введите ФИО и 4 оценки студента:" << endl;
			cin >> A.name >> A.grade[0] >> A.grade[1] >> A.grade[2] >> A.grade[3]; // Ввод

			outFile.open(path + clientName + ".bin", ios::app | ios::binary);
			outFile.write((char*)&A, sizeof(A));
			outFile.seekp(0, ios::end);
			fileSize = outFile.tellp();
			outFile.close();
			isWaiting = true;
		}
		else // иначе ожидаем ответ
		{
			inFile.open(path + clientName + ".bin", ios::binary);
			inFile.seekg(fileSize, ios::beg);
			inFile.read((char*)&answer, sizeof(answer));
			//long oldSize = fileSize;
			fileSize = inFile.tellg();
			inFile.close();
			//cout << "old: " << oldSize << " new: " << fileSize << endl;
			switch (answer)
			{
			case 2:
				cout << "У " << A.name << " имеется задолжность!" << endl;
				break;
			case 3:
				cout << "У " << A.name << " нет стипендии!" << endl;
				break;
			case 4:
				cout << "У " << A.name << " обычная стипендия!" << endl;
				break;
			case 5:
				cout << "У " << A.name << " повышенная стипендия!" << endl;
				break;
			case 500:
				cout << "Ошибка! Недопустимый ввод в запросе!" << endl;
				break;
			default:
				cout << "Ошибка! Недопустимый ответ сервера: " << answer << endl;
				break;
			}
			cout << endl;
			isWaiting = false;
		}
		Sleep(100);
	}
}