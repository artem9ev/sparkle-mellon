#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
// структура данных запроса клиента
struct Person
{
	char name[25];  //имя
	int height;		//рост
	int weight;		//вес
} A;
void connect(char* link) {
	const char* nameR = "F:/bread/in-class practice/networking/messages/request.bin"; //файл для запросов клиентов
	const char* nameA = "F:/bread/in-class practice/networking/messages/answer.bin"; //файл для ответов сервера
	ofstream out_REQ;
	ifstream in_ANS;
	long pred_size;
	int answer;
	while (true)
	{
		// передача данных от клиента серверу
		cout << "Введите запрос: Фамилия Рост Вес" << endl;
		cin >> A.name >> A.height >> A.weight;
		cout << A.name << A.height << A.weight;
		out_REQ.open(nameR, ios::app | ios::binary); //открытие файла REQUEST 
		out_REQ.write((char*)&A, sizeof(A)); //запись запроса в файл REQUEST
		out_REQ.close();

		// поступил ответ от сервера?
		in_ANS.open(nameA, ios::binary); //открытие файла ANSWER
		in_ANS.seekg(0, ios::end); //переход в конец файла ANSWER
		pred_size = in_ANS.tellg();
		while (pred_size >= in_ANS.tellg())
		{
			Sleep(100); // ждем и переходим в конец файла ANSWER
			in_ANS.seekg(0, ios::end);
		}
		// получение ответа от сервера	
		in_ANS.seekg(pred_size, ios::beg); // на начало нового ответа
		in_ANS.read((char*)&answer, sizeof(answer)); //считывание ответа
		in_ANS.close();

		// расшифровка ответа
		switch (answer) {
		case 0: {cout << "Недостаток веса\n"; break; }
		case 1: {cout << "Норма веса\n"; break; }
		case 2: {cout << "Избыток веса\n"; break; }
		}
	} //while
}

void main() {
	setlocale(LC_ALL, "rus");
	// фаил для записи имени (регистрация на сервере)
	string path = "F:/bread/in-class practice/networking/messages/";
	string nameR = path + "connection.bin";
	
	int name = (int)(&A);

	ofstream outConnect;
	outConnect.open(nameR, ios::app | ios::binary); //открытие файла REQUEST 
	outConnect.write((char*)&name, sizeof(name)); //запись запроса в файл REQUEST
	outConnect.close();
	
	cout << "name: " << (name) << endl;
}
