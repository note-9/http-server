#include <iostream> // For ip/op operations
#include <string> // for using std::string
#include <stdexcept> // for throwing std exceptions
#include <sstream> // for string stream operations
#include <map> // for storing key value pairs

// C - style headers for low level socket programming
#include <sys/socket.h> 
#include <netinet/in.h> // for sockaddr_in structure and internet addresses
#include <unistd.h> // for close function
#include <thread> // to handle multiple clients
#include <cstring> // for memset() to clear memory

int main(){
    const int PORT = 8080;

    int server_fd; // server socket file descriptor
    
    struct sockaddr_in address;
    
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    

    return 0;
}
