#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main( int argc, char const *argv[])
{

    int server_fd, new_socket; long alread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0 )) < 0)
    {
        perror("Cannot create socket");
        return 0;
    }

   
    const int PORT = 8080; // Where the clients can reach at 

    memset((char*)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY); // convert a long integer to a network representatnion 
    address.sin_port = htons(PORT); // converts a short integer to a network representatnio

    if( bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0)
    {
        perror("bind filed");
        return 0;
    }

    int listen(int socket, int backlog); // backlog defines the max number of pending connection that can be queued up before connection are refused

    if (listen(server_fd, 3 ) < 0 )
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("In accept");
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = {0};

    int valred = read(new_socket, buffer , 1024);
    printf("%s\n", buffer);

    if(valred<0)
    {
        printf("No bytes are there to read");
    }

    char *hello = "Hello from the server"; 
    write(new_socket,hello,strlen(hello));

    close(new_socket);





    

}