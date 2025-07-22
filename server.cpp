#include <iostream> // For ip/op operations
#include <string>
// #include <thread> // to handle multiple clients
#include <stdexcept>
#include <cstdlib>

#include "Socket.hpp"

int main(){
    const int PORT = 8080;

    try {
        Socket server_socket;

        server_socket.set_reuse_address();
        
        server_socket.bind(PORT);
        
        server_socket.listen(10);
        std::cout << "Server listening on port " << PORT << std::endl;

        while (true) {
            try {
                Socket client_socket = server_socket.accept();
                std::cout << "New connection accepted!" << std::endl;

                char buffer[1024] = {0};
                ssize_t bytes_read = client_socket.recv(buffer, sizeof(buffer) - 1);

                if (bytes_read == 0) {
                    // Client disconnected gracefully before sending data
                    std::cout << "Client disconnected gracefully without sending data." << std::endl;
                    continue; // Move to the next loop iteration to accept new clients
                } else if (bytes_read < 0) {
                    std::cerr << "Error reading from client socket." << std::endl;
                    continue; 
                }

                buffer[bytes_read] = '\0';
                std::cout << "Recieved request:\n" << buffer << std::endl;

                std::string html_content = "<h1>Hello from my C++ HTTP Server!</h1>";
                std::string http_response;
                http_response += "HTTP/1.1 200 OK\r\n";
                http_response += "Content-Type: text/html\r\n";
                http_response += "Content-Length: " + std::to_string(html_content.length()) + "\r\n\r\n";
                http_response += html_content;
                
                client_socket.send(http_response);
                
                std::cout << "Response sent and connection closed." << std::endl;
            } catch(const std::runtime_error& e) {
                std::cerr << "Client Handling Error: " << e.what() << std::endl;
            }
        }
            

    } catch (const std::runtime_error& e) {
        std::cerr << "Server Critical Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;

}