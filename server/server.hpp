#pragma once

class Echo_server {
public:
    Echo_server(int port, int backlog) : _port(port), _backlog(backlog), _server_fd(-1), _is_running(false) {}
    ~Echo_server();

    Echo_server& operator=(Echo_server& other) = delete;

    void start();

private:
    int _server_fd;
    int _backlog;
    int _port;
    bool _is_running;

    void stop();
    void handle_client(int client_fd);
};