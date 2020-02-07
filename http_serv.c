#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080 // Where the clients can reach at
int main( int argc, char const *argv[])
{

    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);


    char *hello = "Hello from the server"; 
    
    // Creating socket file desriptor 
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0 )) == 0 )
    {
        perror("In socket");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero,'\0', sizeof(address.sin_zero));
    

    if( bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0)
    {
        perror("bind filed");
        exit(EXIT_FAILURE);
    }

    
    
    if (listen(server_fd, 10) < 0 )
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    return 0;
}