#include <iomanip>
#include <iostream>
#include <string>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

std::pair<double, double> receive(int socket)
{
    const size_t buffer_size = 256;
    char buffer[buffer_size]{};

    read(socket, buffer, buffer_size);
    std::string message(buffer, buffer_size);
    auto space = message.find(" ");
    return {std::stod(message.substr(0, space)), std::stod(message.substr(space, message.npos))};
}

int main()
{
    std::cout << std::setprecision(10);

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(1234);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    close(sockfd);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);

    while (true)
    {
        int new_sockfd = accept(sockfd, nullptr, nullptr);
        auto [min, max] = receive(new_sockfd);
        std::cout << min << " " << max << std::endl;
        close(new_sockfd);
    }

    return 0;
}
