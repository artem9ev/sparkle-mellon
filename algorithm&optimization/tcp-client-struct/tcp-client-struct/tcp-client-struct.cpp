#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

struct Data {
    int number;
    char string1[50];
    char string2[50];
};

int main() {
    setlocale(LC_ALL, "RUS");
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Ошибка при инициализации Winsock" << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Ошибка при создании сокета" << std::endl;\
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("localhost");

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Ошибка при подключении к серверу" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Подключение установлено" << std::endl;

    Data sendData;
    sendData.number = 42;
    strncpy_s(sendData.string1, sizeof(sendData.string1), "Привет", _TRUNCATE);
    strncpy_s(sendData.string2, sizeof(sendData.string2), "Мир", _TRUNCATE);

    send(clientSocket, (char*)&sendData, sizeof(sendData), 0);

    std::cout << "Данные отправлены" << std::endl;

    Data receivedData;
    recv(clientSocket, (char*)&receivedData, sizeof(receivedData), 0);

    std::cout << "Получены данные от сервера:" << std::endl;
    std::cout << "Число: " << receivedData.number << std::endl;
    std::cout << "Строка 1: " << receivedData.string1 << std::endl;
    std::cout << "Строка 2: " << receivedData.string2 << std::endl;

    closesocket(clientSocket);
    WSACleanup();

    std::cout << "Соединение закрыто" << std::endl;

    return 0;
}