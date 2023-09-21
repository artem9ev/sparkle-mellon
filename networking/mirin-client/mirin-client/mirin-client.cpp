#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

//СЕРВЕР

struct Person
{
	char name[25];  //имя
	int oznka1;		//оценки
	int oznka2;
	int oznka3;
	int oznka4;
}A;

int main()
{
	setlocale(LC_ALL, "rus");
	string way_address = "F:/bread/in-class practice/networking/messages/";

	srand(time(NULL)); //генерация рандомного названия
	string client = to_string(rand() % 1000 + 1000);
	string full_client = way_address + client + ".bin";

	ofstream gg(full_client, ios::binary | ios::app);
	gg.close();

	//передача серверу названия нового клиента через файл connection.bin
	ofstream con;
	con.open(way_address + "connection.bin", ios::binary | ios::app);
	con.write((char*)&client, sizeof(client));
	//con << client; // вписывает из этой переменной, столько битов
	con.close();

	int answer;
	int pred_size;
	while (true)
	{
		// передача данных от клиента серверу
		cout << "Введите запрос: Фамилия и 4 оценки за экзамены" << endl;
		cin >> A.name >> A.oznka1 >> A.oznka2 >> A.oznka3 >> A.oznka4;

		ofstream file_client_request; //создание файла для записи с сгенерированным названием
		file_client_request.open(full_client, ios::app | ios::binary);
		file_client_request.write((char*)&A, sizeof(A));
		pred_size = file_client_request.tellp();
		file_client_request.close();

		ifstream file_client_answer; //файл уже с ответом для чтения
		file_client_answer.open(full_client, ios::binary); //открытие файла 
		file_client_answer.seekg(0, ios::end); //переход в конец файла 
		while (pred_size >= file_client_answer.tellg())
		{
			Sleep(100);
			file_client_answer.seekg(0, ios::end);
		}

		file_client_answer.seekg(pred_size, ios::beg);		// на начало нового ответа
		file_client_answer.read((char*)&answer, sizeof(answer));//считывание ответа
		file_client_answer.close();

		// расшифровка ответа
		switch (answer)
		{
		case 2: {cout << " - имеется задолжность\n"; break; }
		case 3: {cout << " - степендии нет\n"; break; }
		case 4: {cout << " - обычная степендия\n"; break; }
		case 5: {cout << " - повышенная степендия\n"; break; }
		}
	}
}