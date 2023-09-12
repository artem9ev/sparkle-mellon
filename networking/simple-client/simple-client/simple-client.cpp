#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
// структура данных запроса клиента
struct Person
{
	char name[25];  //имя
	int height;		//рост
	int weight;		//вес
} A;
void main() {
	setlocale(LC_ALL, "rus");

	const char* nameR = "F:/bread/in-class practice/networking/messages/request.bin"; //файл для запросов клиентов
	const char* nameA = "F:/bread/in-class practice/networking/messages/answer.bin"; //файл для ответов сервера
	ofstream f_REQ;
	ifstream f_ANS;
	long pred_size;
	int answer;
	while (true)
	{
		// передача данных от клиента серверу
		cout << "Введите запрос: Фамилия Рост Вес" << endl;
		cin >> A.name >> A.height >> A.weight;
		cout << A.name << A.height << A.weight;
		f_REQ.open(nameR, ios::app | ios::binary); //открытие файла REQUEST 
		f_REQ.write((char*)&A, sizeof(A)); //запись запроса в файл REQUEST
		f_REQ.close();

		// поступил ответ от сервера?
		f_ANS.open(nameA, ios::binary); //открытие файла ANSWER
		f_ANS.seekg(0, ios::end); //переход в конец файла ANSWER
		pred_size = f_ANS.tellg();
		while (pred_size >= f_ANS.tellg())
		{
			Sleep(100); // ждем и переходим в конец файла ANSWER
			f_ANS.seekg(0, ios::end);
		}
		// получение ответа от сервера	
		f_ANS.seekg(pred_size, ios::beg); // на начало нового ответа
		f_ANS.read((char*)&answer, sizeof(answer)); //считывание ответа
		f_ANS.close();

		// расшифровка ответа
		switch (answer) {
		case 0: {cout << "Недостаток веса\n"; break; }
		case 1: {cout << "Норма веса\n"; break; }
		case 2: {cout << "Избыток веса\n"; break; }
		}
	} //while
}
