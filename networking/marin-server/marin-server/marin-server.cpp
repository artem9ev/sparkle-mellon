#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
}B;

struct data_clients
{
	string address; //_.bin
	int sizee; //продыдущий записаный размер
};

int Checking_ratings(Person B)
{	//обработка данных об экзаменах
	if (B.oznka1 == 2 || B.oznka2 == 2 || B.oznka3 == 2 || B.oznka4 == 2) return 2; //задолжность	
	if (B.oznka1 == 3 || B.oznka2 == 3 || B.oznka3 == 3 || B.oznka4 == 3) return 3; //обычная степендия
	if (B.oznka1 == 4 || B.oznka2 == 4 || B.oznka3 == 4 || B.oznka4 == 4) return 4;
	return 5; //нет степендии
}

int main()
{
	setlocale(LC_ALL, "rus");
	string way_address = "F:/bread/in-class practice/networking/messages/"; //путь к файлам
	int answer;

	ifstream con1;
	con1.open(way_address + "connection.bin", ios::binary);
	con1.seekg(0, ios::end);
	long size_pred_con = con1.tellg();
	con1.close();
	cout << "Server is working" << endl;
	vector <data_clients> list_clients;

	while (true) // начало работы сервера
	{
		ifstream con;
		string new_client_address = "";
		con.open(way_address + "connection.bin", ios::binary);
		con.seekg(0, ios::end);
		if (size_pred_con < con.tellg()) //если добавилось название нового клиента
		{
			
			ifstream new_clients_file;
			con.seekg(size_pred_con, ios::beg);
			con.read((char*)&new_client_address, sizeof(new_client_address));
			new_client_address += ".bin";
			cout << "client: " << new_client_address << endl;

			new_clients_file.open(way_address + new_client_address, ios::binary);
			data_clients new_client;
			new_client.address = new_client_address;
			new_client.sizee = new_clients_file.tellg();
			list_clients.push_back(new_client);

			con.seekg(0, ios::end);
			size_pred_con = con.tellg();
		}
		con.close();

		for (int i = 0; i < list_clients.size(); i++) //проверка и ответ на запросы всех клиентов
		{
			ifstream current_client_request; //открыли файл клиента для чтения

			current_client_request.open(way_address + list_clients[i].address, ios::binary);
			current_client_request.seekg(0, ios::end);
			if (list_clients[i].sizee < current_client_request.tellg()) //если появился запрос
			{
				current_client_request.seekg(list_clients[i].sizee, ios::beg);	//переход к началу полученного запроса
				current_client_request.read((char*)&B, sizeof(B));	//считывание данных клиента с позиции размером
				list_clients[i].sizee = current_client_request.tellg();	// на конец обработанных данных
				current_client_request.close();

				answer = Checking_ratings(B); //обработка запроса клиента

				ofstream current_client_answer; //открыли файл клиента для записи
				current_client_answer.open(way_address + list_clients[i].address, ios::binary | ios::app);
				current_client_answer.write((char*)&answer, sizeof(answer)); //запись ответа
				current_client_answer.seekp(0, ios::end);
				list_clients[i].sizee = current_client_answer.tellp();
				current_client_answer.close();
			}
		}
		//ожидание, перестановка указателя и снова проверка на появление нового клиента
		Sleep(400);
	}
}