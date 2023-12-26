#include <iostream>
#include <sstream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

// Для использования новых интерфейсных функций
#pragma comment(lib,"Ws2_32.lib")
using std::cerr;

int main()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        cerr << "WSAStartap failed: " << result << "\n";
        return result;
    }

    // Создание сокета
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket == INVALID_SOCKET)
    {
        cerr << "Error at socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // Привязываем сокет к IP-адресу
    result = bind(listen_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (result == SOCKET_ERROR)
    {
        cerr << "bind failed with error: " << WSAGetLastError() << "\n";
        closesocket(listen_socket);
        WSACleanup();
        return -1;
    }

    // Инициализируем слушающий сокет
    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        cerr << "listen failed with error: " << WSAGetLastError() << "\n";
        closesocket(listen_socket);
        WSACleanup();
        return -1;
    }

    const int max_client_buffer_size = 1024;
    char buf[max_client_buffer_size];
    int client_socket = INVALID_SOCKET;

    //Принимаем входящие соединения
    for (;;)
    {
        client_socket = accept(listen_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET)
        {
            cerr << "accept failed: " << WSAGetLastError() << "\n";
            closesocket(listen_socket);
            WSACleanup();
            return 1;
        }

        std::stringstream response; // Для ответа клиенту
        std::stringstream response_body; // Тело ответа
        result = recv(client_socket, buf, max_client_buffer_size, 0);
        if (result == SOCKET_ERROR)
        {
            // Ошибка получения данных
            cerr << "recv failed: " << result << "\n";
            closesocket(client_socket);
        }
        else if (result == 0)
        {
            // Соединение закрыто клиентом
            cerr << "connection closed...\n";
        }
        else if (result > 0)
        {
            // Данные запроса успешно получены
            buf[result] = '\0';
            // Формируем тело ответа (HTML)
            response_body << "<title>Test C++ HTTP Server</title>\n"
                << "<h1>Test page</h1>\n"
                << "<p>This is body of the test page...</p>\n"
                << "<h2>Request headers<\h2>\n"
                << "<pre>" << buf << "<\pre>\n"
                // включаем в ответ полученный запрос
                << "<em><small>Test C++ Http Server</small><\em>\n";
            // Формируем весь ответ вместе с заголовками
            response << "HTTP/1.1 200 OK\r\n" << "Version: HTTP/1.1\r\n"
                << "Content-Type: text/html; charset=utf-8\r\n"
                << "Content-Length: " << response_body.str().length() << "\r\n\r\n" << response_body.str();
            // Отправляем ответ клиенту
            result = send(client_socket, response.str().c_str(), response.str().length(), 0);
            if (result == SOCKET_ERROR)
            {
                // Ошибка при отправке данных
                cerr << "send failed: " << WSAGetLastError() << "\n";
            }
            closesocket(client_socket);
        }
    }

    closesocket(listen_socket);
    WSACleanup();
    return 0;
}
