#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <stdexcept> // for throwing std exceptions
#include <string> // for using std::string
#include <sys/socket.h> 
#include <netinet/in.h> // for sockaddr_in structure and internet addresses
#include <unistd.h> // for close function

class Socket {
private:
    int _fd;

public:
    Socket(); // Constructor
    ~Socket(); // Destructor

    // Sockets are unique resources so disable copying
    Socket(const Socket&) = delete;
    Socket& operator = (const Socket&) = delete;
    
    // Enable moving (ttansfer ownership)
    Socket(Socket&& other) noexcept;
    Socket& operator = (Socket&& other) noexcept;

    void set_reuse_address();
    void bind(int port);
    void listen(int backlog = 10);
    Socket accept(); // returns a new socket object for the client
    ssize_t send(const std::string& data);
    ssize_t recv(char* buffer, size_t buffer_size);

    int get_fd() const { return _fd; } // Inline for simple getter

};

#endif