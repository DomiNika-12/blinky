#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

struct sockaddr_in serv;
socklen_t iServSize;
int iSocketFd = 0;

int CreateConnection()
{
    int iError = 0;
    int iOpt = 0;

    // Create socket: IPv4 domain, TCP, TCP protocol
    iSocketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (iSocketFd == -1)
    {
        printf("Error while creating socket (%d) %s \n", errno, strerror(errno));
        iError = iSocketFd;
        return iError;
    }

//    iOpt = 1;
//    setsockopt(iSocketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &iOpt, sizeof(iOpt));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(2390);
    serv.sin_addr.s_addr = inet_addr("192.168.0.196");

    //inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    iError = connect(iSocketFd, (struct sockaddr *) &serv, sizeof(serv));
    if (iError < 0)
    {
        printf("Error while connecting to the socket (%d) %s \n", errno, strerror(errno));
        return iError;
    }
    printf("Client running\n");
    printf("Port:       %d (network byte order)\n", serv.sin_port);
    printf("            %d (hostorder)\n", 2390);
    printf("Domain:     AF_INET\n");
    printf("Protocol:   UDP\n\n");

    return iError;
}

int SendMsg(int i)
{
    int iError = 0;

    char number[8];
    sprintf(number, "%d",i);
    iError = send(iSocketFd, number, sizeof(number), 0);
    if (iError < 0)
    {
        printf("Message not sent, errno (%d) %d, %s\n", iError, errno, strerror(errno));
        return iError;
    }

    return iError;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    CreateConnection();
    int i = 0;
    while (1)
    {
        if (i == 3)
        {
            i = 0;
        }
        std::cout << "Sending message" << std::endl;
        SendMsg(i);
        i++;
        sleep(2);
    }
    return 0;
}

