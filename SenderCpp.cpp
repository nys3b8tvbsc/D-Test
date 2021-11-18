#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

std::vector<double> readNumbers()
{
    std::ifstream numbersFile("input.txt");
    std::vector<double> result;

    double temp;
    while (numbersFile >> temp)
    {
        result.push_back(temp);
    }

    return result;
}

void sendNumbers(const std::pair<double, double> &minmax)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    hostent *server = gethostbyname("localhost");

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    bcopy(reinterpret_cast<char *>(server->h_addr),
          reinterpret_cast<char *>(&serv_addr.sin_addr.s_addr),
          static_cast<size_t>(server->h_length));
    serv_addr.sin_port = htons(static_cast<uint16_t>(1234));

    if (connect(sockfd, reinterpret_cast<sockaddr *>(&serv_addr), sizeof(serv_addr)) < 0)
    {

        std::cout << "Connection Error" << std::endl;
    }

    std::string buffer;
    buffer = std::to_string(minmax.first) + " " + std::to_string(minmax.second);
    write(sockfd, buffer.c_str(), buffer.size());

    close(sockfd);
}

int main()
{
    auto numbers = readNumbers();

    auto [minIt, maxIt] = std::minmax_element(numbers.begin(), numbers.end());

    sendNumbers({*minIt, *maxIt});

    return 0;
}
