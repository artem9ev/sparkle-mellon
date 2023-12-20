// UDP-эхо сервер
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <time.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define PORT 666    // порт сервера

enum Cell {
    EMPTY = 0,
    MISS = 1,
    SHIP = 2,
    DESTROYD = 3,
};

struct Field {
    Cell field[10][10];
};

Field GenerateField() { // 4-1 2-3 3-2 4-1
    Field F;
    bool isEmpty[10][10];
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 10; k++) {

            F.field[i][k] = EMPTY;
            isEmpty[i][k] = true;
        }
    }
    // ставлю 4 клеточный
    bool isPlaced = false;
    for (int shipSize = 4; shipSize > 0; shipSize--)
    {
        for (int countShips = 0; countShips < 5 - shipSize; countShips++)
        {
            isPlaced = false;
            while (!isPlaced) {

                bool canPlace = true;
                bool orient = (bool)(rand() % 2);
                int mainAxis = rand() % 10;
                int secondAxis = rand() % (10 - shipSize + 1);
                for (int i = secondAxis; i < secondAxis + shipSize; i++) {
                    if (isEmpty[orient * mainAxis + !orient * i][!orient * mainAxis + orient * i] == false)
                    {
                        canPlace = false;
                        break;
                    }
                }
                if (canPlace == true)
                {
                    for (int i = secondAxis; i < secondAxis + shipSize; i++) {
                        F.field[orient * mainAxis + !orient * i][!orient * mainAxis + orient * i] = SHIP;
                    }
                    for (int k = mainAxis - 1; k <= mainAxis + 1; k++)
                    {
                        for (int i = secondAxis - 1; i < secondAxis + shipSize + 1; i++)
                        {
                            if (k > 0 && k < 10 && i > 0 && i < 10)
                            {
                                isEmpty[orient * k + !orient * i][!orient * k + orient * i] = false;
                            }
                        }
                    }
                    isPlaced = true;
                }
            }
        }
    }

    return F;
}

void printField(Field F) {
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            cout << F.field[i][k] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    char buff[1024];
    cout << "UDP DEMO ECHO-SERVER\n";
    // шаг 1 - подключение библиотеки 
    if (WSAStartup(0x202, (WSADATA*)&buff[0]))
    {
        cout << "WSAStartup error: " << WSAGetLastError();
        return -1;
    }
    // шаг 2 - создание сокета
    SOCKET Lsock;
    Lsock = socket(AF_INET, SOCK_DGRAM, 0);
    if (Lsock == INVALID_SOCKET) {
        cout << "SOCKET() ERROR: " << WSAGetLastError();
        WSACleanup();
        return -1;
    }
    // шаг 3 - связывание сокета с локальным адресом 
    sockaddr_in Laddr;
    Laddr.sin_family = AF_INET;
    Laddr.sin_addr.s_addr = INADDR_ANY;   // или 0 (любой IP адрес)
    Laddr.sin_port = htons(PORT);
    if (bind(Lsock, (sockaddr*)&Laddr, sizeof(Laddr)))
    {
        cout << "BIND ERROR:" << WSAGetLastError();
        closesocket(Lsock);
        WSACleanup();
        return -1;
    }// шаг 4 обработка пакетов, присланных клиентами
    while (1) {
        sockaddr_in Caddr;
        int Caddr_size = sizeof(Caddr);
        int bsize = recvfrom(Lsock, &buff[0], sizeof(buff) - 1, 0,
            (sockaddr*)&Caddr, &Caddr_size);
        if (bsize == SOCKET_ERROR)
            cout << "RECVFROM() ERROR:" << WSAGetLastError();
        // Определяем IP-адрес клиента и прочие атрибуты
        HOSTENT* hst;
        hst = gethostbyaddr((char*)&Caddr.sin_addr, 4, AF_INET);
        cout << "NEW DATAGRAM!\n" <<
            ((hst) ? hst->h_name : "Unknown host") << "/n" <<
            inet_ntoa(Caddr.sin_addr) << "/n" << ntohs(Caddr.sin_port) << '\n';
        //buff[bsize] = '\0';              // добавление завершающего нуля
        cout << "C=>S:" << buff << '\n';        // Вывод на экран 
        // посылка датаграммы клиенту
        Field F = GenerateField();
        cout << "generated: " << sizeof(F) << endl;
        printField(F);
        sendto(Lsock, (char*)&F, sizeof(F), 0, (sockaddr*)&Caddr, sizeof(Caddr));
    }      return 0;
}
