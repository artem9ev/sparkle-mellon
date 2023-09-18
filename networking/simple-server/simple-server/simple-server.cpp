#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

using namespace std;
struct Person
{
	char name[25];
	int grade[4];
}B;

struct ClientData
{
	string name;
	int size;
};
int answer;
long size_pred;

int getStipendia() {
	for (int i = 0; i < 4; i++)
	{
		if (B.grade[i] <= 2)
		{
			cout << "1" << endl;
			return 1;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (B.grade[i] == 3)
		{
			cout << "2" << endl;
			return 2;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (B.grade[i] == 4)
		{
			cout << "3" << endl;
			return 3;
		}
	}
	cout << "4" << endl;
	return 4;
}

int main() {
	setlocale(LC_ALL, "rus");

	long sizeConnections;

	ifstream inputConnection;
	ifstream newClientFile;

	string path = "F:/bread/in-class practice/networking/messages/";
	string fileName = path + "connection.bin";
	string newClientName;
	// ----- начальные установки -----
	inputConnection.open(fileName, ios::binary); //открытие файла connection.txt
	inputConnection.seekg(0, ios::end);
	sizeConnections = inputConnection.tellg();
	inputConnection.close();

	vector<ClientData> client;

	cout << "Сервер работает" << endl;
	cout << "Размер файла подключений: " << sizeConnections << endl;
	
	while (true) // начало работы сервера
	{
		// проверка наличия новых клиентов
		inputConnection.open(fileName, ios::binary); //открытие файла connection.bin
		inputConnection.seekg(0, ios::end); //переход в конец файла connection.txt
		//while (sizeConnections >= inputConnection.tellg()) // есть новые запросы от клиентов?
		//{
		//	cout << ". ";
		//	Sleep(500); 
		//	inputConnection.seekg(0, ios::end);
		//}
		if (sizeConnections < inputConnection.tellg())
		{
			// найден новый клиент
			inputConnection.seekg(sizeConnections, ios::beg);
			inputConnection >> newClientName;

			ClientData newClientData;
			newClientFile.open(path + newClientName + ".bin");
			//newClientFile.clear();         НЕ РАБОТАЕТ
			//newClientFile.seekg(0, ios::end); Всегда дает -1
			newClientData.name = newClientName;
			newClientData.size = 0;
			client.push_back(newClientData);

			inputConnection.seekg(0, ios::end);
			sizeConnections = inputConnection.tellg();
			
			cout << endl << "Новый клиент: " << newClientName << endl;
			cout << "Размер файла подключений: " << sizeConnections << endl;
			//cout << "Указатель в клиенте: " << newClientData.size << endl;
		}
		inputConnection.close();

		// Обход текущих клиентов
		bool haveNewInput = false;
		int answer = 9;
		ofstream outFile;
		ifstream inFile;
		for (int i = 0; i < client.size(); i++)
		{
			inFile.open(path + client[i].name + ".bin", ios::binary);
			inFile.clear();
			inFile.seekg(0, ios::end);
			if (client[i].size < inFile.tellg())
			{
				inFile.seekg(client[i].size, ios::beg);
				inFile.read((char*)&B, sizeof(B));
				haveNewInput = true;
				cout << endl << "Запрос получен: " << B.name << " ";
				for (int i = 0; i < 4; i++)
				{
					cout << B.grade[i] << " ";
				}
				cout << endl;
				//cout << "old: " << client[i].size << " new: " << inFile.tellg() << endl;
			}
			inFile.close();

			if (haveNewInput)
			{
				cout << endl << "Ответ отправлен: ";
				outFile.open(path + client[i].name + ".bin", ios::app | ios::binary);
				answer = getStipendia();
				outFile.write((char*)&answer, sizeof(answer));
				outFile.seekp(0, ios::end);
				long oldSize = client[i].size;
				client[i].size = outFile.tellp();
				outFile.close();
				//cout << "old: " << oldSize << " new: " << client[i].size << endl;
			}
			haveNewInput = false;
		}

		cout << ". ";
		Sleep(500);
	}
}
