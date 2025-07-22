#include "Socket.hpp"

#include <iostream>
#include <cstring> // for memset() to clear memory

Socket::Socket() : _fd(-1) { // Initialize _fd to an invalid value
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd < 0) {
        throw std::runtime_error("Failed to create socket");
    }
}

Socket::~Socket() {
    if (_fd >= 0) { // Only close if it's a valid FD
        close(_fd);
    }
}

// Move constructor
Socket::Socket(Socket&& other) noexcept : _fd(other._fd) {
    other._fd = -1; // Invalidate the source object's FD
}

// Move assignment operator
Socket& Socket::operator=(Socket&& other) noexcept {
    if (this != &other) { // Handle self-assignment
        if (_fd >= 0) {
            close(_fd); // Close current FD if valid
        }
        _fd = other._fd;
        other._fd = -1; // Invalidate the source object's FD
    }
    return *this;
}

void Socket::set_reuse_address() {
    int opt = 1;
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        throw std::runtime_error("Failed to set socket options (SO_REUSEADDR/SO_REUSEPORT)");
    }
}

void Socket::bind(int port) {
    struct sockaddr_in address_s;
    memset(&address_s, 0, sizeof(address_s));
    address_s.sin_family = AF_INET;
    address_s.sin_addr.s_addr = INADDR_ANY;
    address_s.sin_port = htons(port);

    if (::bind(_fd, (struct sockaddr *)&address_s, sizeof(address_s)) < 0) { // Use ::bind to avoid name conflicts
        throw std::runtime_error("Failed to bind socket to port " + std::to_string(port));
    }
}

void Socket::listen(int backlog) {
    if (::listen(_fd, backlog) < 0) { 
        throw std::runtime_error("Failed to listen on socket");
    }
}

Socket Socket::accept() {
    struct sockaddr_in client_address_s;
    socklen_t client_addrlen = sizeof(client_address_s);
    int client_fd = ::accept(_fd, (struct sockaddr *)&client_address_s, &client_addrlen);
    if (client_fd < 0) {
        throw std::runtime_error("Failed to accept client connection");
    }
    Socket client_socket; // Create a new Socket object
    client_socket._fd = client_fd; // Assign the new FD directly
    return client_socket; // Return by value, relying on move constructor
}

ssize_t Socket::send(const std::string& data) {
    ssize_t bytes_sent = ::send(_fd, data.c_str(), data.length(), 0); 
    if (bytes_sent < 0) {
        throw std::runtime_error("Failed to send data");
    }
    return bytes_sent;
}

ssize_t Socket::recv(char* buffer, size_t buffer_size) {
    ssize_t bytes_received = ::recv(_fd, buffer, buffer_size, 0);
    if (bytes_received < 0) {
        throw std::runtime_error("Failed to receive data");
    }
    return bytes_received;
}