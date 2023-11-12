// пример UDP-клиента
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <string>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define PORT 666
#define SERVERADDR "127.0.0.1" // IP-адрес сервера

int main()
{
    char buff[10 * 1014];
    cout << "UDP Demo Client\nType quit to quit \n";
    // Шаг 1 - иницилизация библиотеки Winsocks
    if (WSAStartup(0x202, (WSADATA*)&buff))
    {
        cout << "WSASTARTUP ERROR: " << WSAGetLastError() << "\n";
        return -1;
    }
    // Шаг 2 - открытие сокета
    SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (my_sock == INVALID_SOCKET) {
        cout << "SOCKET() ERROR: " << WSAGetLastError() << "\n";
        WSACleanup();
        return -1;
    }
    // Шаг 3 - обмен сообщений с сервером
    HOSTENT* hst;
    sockaddr_in Daddr;
    Daddr.sin_family = AF_INET;
    Daddr.sin_port = htons(PORT);
    // определение IP-адреса узла
    if (inet_addr(SERVERADDR))
        Daddr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else
        if (hst = gethostbyname(SERVERADDR))
            Daddr.sin_addr.s_addr = ((unsigned long**)
                hst->h_addr_list)[0][0];
        else {
            cout << "Unknown Host: " << WSAGetLastError() << "\n";
            closesocket(my_sock);
            WSACleanup();
            return -1;
        }
    while (1) {
        // чтение сообщения с клавиатуры
        cout << "S<=C:";
        string SS;
        getline(cin, SS);
        if (SS == "quit") break;

        // Передача сообщений на сервер
        sendto(my_sock, (char*)&SS[0], SS.size(), 0,
            (sockaddr*)&Daddr, sizeof(Daddr));
        // Прием сообщения с сервера
        sockaddr_in SRaddr;
        int SRaddr_size = sizeof(SRaddr);
        int n = recvfrom(my_sock, buff, sizeof(buff), 0,
            (sockaddr*)&SRaddr, &SRaddr_size);
        if (n == SOCKET_ERROR) {
            cout << "RECVFROM() ERROR:" << WSAGetLastError() << "\n";
            closesocket(my_sock);
            WSACleanup();  return -1;
        }
        buff[n] = '\0';
        // Вывод принятого с сервера сообщения на экран
        cout << "S=>C:" << buff << "\n";
    }
    // шаг последний - выход
    closesocket(my_sock);
    WSACleanup();     return 0;
}


