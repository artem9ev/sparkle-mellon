#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
struct Person
{
	char name[25];	 //имя 
	int height;		//рост
	int weight;		//вес
}B;
int answer;
long size_pred;

void 

int main() {
	ifstream fR;
	ofstream fA;
	setlocale(LC_ALL, "rus");
	const char* nameR = "F:/bread/in-class practice/networking/messages/request.bin"; //файл запросов клиентов
	const char* nameA = "F:/bread/in-class practice/networking/messages/answer.bin"; //файл ответов сервера
	cout << "server is working" << endl;
	// начальные установки
	fR.open(nameR, ios::binary); //открытие файла REQUEST
	fR.seekg(0, ios::end);
	size_pred = fR.tellg(); //стартовая позиция сервера в файле REQUEST
	fR.close();

	// начало работы сервера
	while (true)
	{
		fR.open(nameR, ios::binary); //открытие файла REQUEST
		fR.seekg(0, ios::end); //переход в конец файла REQUEST
		// есть новые запросы от клиентов? 
		while (size_pred >= fR.tellg())
		{
			Sleep(100); fR.seekg(0, ios::end);
		}
		// получен новый запрос 
		fR.seekg(size_pred, ios::beg); //переход к началу полученного запроса
		fR.read((char*)&B, sizeof(B)); //считывание данных клиента
		size_pred = fR.tellg(); // на конец обработанных данных
		fR.close();
		// определение индекса массы	
		double IMT = B.weight / (0.01 * B.height) / (0.01 * B.height);
		if (18.5 <= IMT && IMT < 25) answer = 1;
		if (18.5 > IMT) answer = 0;
		if (IMT >= 25)answer = 2;

		// передача ответа клиенту
		fA.open(nameA, ios::binary | ios::app); //открытие файла ANSWER
		fA.write((char*)&answer, sizeof(answer)); //запись ответа клиенту
		fA.close();
	}// while
}
