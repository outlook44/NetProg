#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <IP_адрес> <порт>\n";
        return 1;
    }

    const char* ip = argv[1];
    int port = std::atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Не удалось создать сокет\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        std::cerr << "Неверный IP-адрес\n";
        close(sock);
        return 1;
    }

    if (sendto(sock, "", 0, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка отправки\n";
        close(sock);
        return 1;
    }
    
    char buffer[1024];
    socklen_t addr_len = sizeof(server_addr);
    ssize_t n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr*)&server_addr, &addr_len);

    if (n > 0) {
        buffer[n] = '\0';
        std::cout << "Время с сервера: " << buffer;
    } else if (n == 0) {
        std::cout << "Получен пустой ответ\n";
    } else {
        std::cerr << "Сервер не ответил (таймаут или ошибка)\n";
    }

    close(sock);
    return 0;
}
