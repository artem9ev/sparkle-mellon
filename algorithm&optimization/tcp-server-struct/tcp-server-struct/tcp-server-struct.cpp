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

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Ошибка при привязке сокета" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Ошибка при прослушивании сокета" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Сервер запущен. Ожидание подключений..." << std::endl;

    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Ошибка при принятии подключения" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Подключение установлено" << std::endl;

    Data receivedData;
    recv(clientSocket, (char*)&receivedData, sizeof(receivedData), 0);

    std::cout << "Получены данные:" << std::endl;
    std::cout << "Число: " << receivedData.number << std::endl;
    std::cout << "Строка 1: " << receivedData.string1 << std::endl;
    std::cout << "Строка 2: " << receivedData.string2 << std::endl;

    send(clientSocket, (char*)&receivedData, sizeof(receivedData), 0);

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    std::cout << "Соединения закрыты" << std::endl;

    return 0;
}