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

    int opt = 1; // option value
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, addrlen);
    address.sin_family = AF_INET; // for ipv4
    address.sin_addr.s_addr = INADDR_ANY; // to listen to all available network interfaces
    address.sin_port = htons(PORT); // for network byte order (host to network short)

    if (bind(server_fd, (struct sockaddr *)&address, addrlen)) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 10)) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if(new_socket == -1) {
            perror("accept failed");
            continue;
        }
        std::cout << "New connection accepted!" << std::endl;

        char buffer[1024];
        ssize_t bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read == -1) {
            perror("read failed");
            close(new_socket);
            continue;
        }
        buffer[bytes_read] = '\0';
        std::cout << buffer << std::endl;

        std::string html_content = "<h1>Hello from my C++ HTTP Server!</h1>";
        std::string http_response;
        http_response += "HTTP/1.1 200 OK\r\n";
        http_response += "Content-Type: text/html\r\n";
        http_response += "Content-Length: " + std::to_string(html_content.length()) + "\r\n\r\n";
        http_response += html_content;

        ssize_t bytes_sent = write(new_socket, http_response.c_str(), http_response.length()); 
        if (bytes_sent == -1) {
            perror("write failed");
        }
        close(new_socket);
        std::cout << "Response sent and connection closed." << std::endl;

    }

    return 0;
}
