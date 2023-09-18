#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <random>

using namespace std;
// структура данных запроса клиента
struct Person
{
	char name[25];  //имя
	int grade[4];
} A;

void main() {
	setlocale(LC_ALL, "rus");

	int seed = time(NULL);
	srand(time(NULL));

	// фаил для записи имени (регистрация на сервере)
	string path = "F:/bread/in-class practice/networking/messages/";
	string registrationFile = path + "connection.bin";
	
	// запандомил имя клиента
	string clientName = to_string(rand() * (int)(sin(time(NULL)) + 2));

	// зарегался на сервере
	ofstream outConnect;
	outConnect.open(registrationFile, ios::app | ios::binary); //открытие файла connection.bin
	outConnect << clientName;
	outConnect.close();
	cout << "client name: " << (clientName) << endl;

	cout << "Файл создан" << endl;
	cout << "Начало работы" << endl;
	// клиент начинает работу
	bool isWaiting = false;
	long fileSize = 0;
	int answer = 0;
	ofstream outFile;
	ifstream inFile;
	while (true)
	{
		if (isWaiting == false)
		{
			cout << "Введите ФИО и 4 оценки студента:" << endl;
			cin >> A.name >> A.grade[0] >> A.grade[1] >> A.grade[2] >> A.grade[3];
			
			outFile.open(path + clientName + ".bin", ios::app | ios::binary);
			outFile.write((char*)&A, sizeof(A));
			outFile.seekp(0, ios::end);
			long oldSize = fileSize;
			fileSize = outFile.tellp();
			outFile.close();
			//cout << "old: " << oldSize << " new: " << fileSize << endl;
			isWaiting = true;
		}
		else
		{
			inFile.open(path + clientName + ".bin", ios::binary);
			inFile.seekg(fileSize, ios::beg);
			inFile.read((char*)&answer, sizeof(answer));
			inFile.clear();
			inFile.seekg(0, ios::end);
			long oldSize = fileSize;
			fileSize = inFile.tellg();
			inFile.close();
			//cout << "old: " << oldSize << " new: " << fileSize << endl;

			switch (answer)
			{
			case 1:
				cout << "У " << A.name << " имеется задолжность!" << endl;
				break;
			case 2:
				cout << "У " << A.name << " нет стипендии!" << endl;
				break;
			case 3:
				cout << "У " << A.name << " обычная стипендия!" << endl;
				break;
			case 4:
				cout << "У " << A.name << " повышенная стипендия!" << endl;
				break;
			default:
				cout << "Ошибка! (Недопустимый ответ сервера) " << answer << endl;
				break;
			}
			isWaiting = false;
		}
		Sleep(500);
	}
}
