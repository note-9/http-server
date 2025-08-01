# http-server

A lightweight, efficient HTTP server implemented in C++ by [note-9](https://github.com/note-9).

## Overview

http-server is a robust HTTP server designed for performance and reliability. Suitable for hosting static files, acting as a backend for web applications, or serving as a foundation for more complex network services, this project emphasizes modularity, security, and standards compliance.

## Features

- **HTTP/1.1 Support:** Handles GET, POST, and other common HTTP methods.
- **Static File Serving:** Efficiently serves static content from a user-defined directory.
- **Configurable Routing:** Custom route handlers can be added for dynamic responses.
- **Multithreaded Design:** Utilizes thread pools for handling multiple concurrent connections.
- **Logging:** Access and error logging for monitoring server activity.
- **Security:** Basic input validation and protection against common HTTP vulnerabilities.
- **Extensible:** Easily extendable for HTTPS, authentication, or REST APIs.

## Technologies Used

- **Language:** C++
- **Networking:** Boost.Asio / std::net (specify which library is used)
- **Build System:** CMake or Makefile (specify which is used)
- **Testing:** Google Test or Catch2 (specify which is used)

## Getting Started

### Prerequisites

- C++17 or higher
- CMake 3.10+ or GNU Make
- Boost libraries (if applicable)

### Building

1. Clone the repository:
    ```bash
    git clone https://github.com/note-9/http-server.git
    cd http-server
    ```
2. Build the project:
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

### Running

```bash
./http-server --port 8080 --www-root /path/to/serve
```

## Contributing

Contributions are encouraged! Please fork the repository and submit a pull request.

## License

This project is not currently licensed. Please contact the repository owner for permission to use or modify this server.

---

[View on GitHub](https://github.com/note-9/http-server)
