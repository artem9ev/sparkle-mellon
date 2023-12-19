// UDP-эхо сервер
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define PORT 666    // порт сервера
#define sHELLO "Hello, STUDENT\n"
int main() {
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
        buff[bsize] = '\0';              // добавление завершающего нуля
        cout << "C=>S:" << buff << '\n';        // Вывод на экран 
        // посылка датаграммы клиенту
        sendto(Lsock, &buff[0], bsize, 0, (sockaddr*)&Caddr, sizeof(Caddr));
    }      return 0;
}
