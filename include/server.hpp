#pragma once

#include "./thread_pool.hpp"

#define BACKLOG 5
#define POOL_SIZE 5

class Echo_server {
public:
  Echo_server(int port)
      : _port(port), _server_fd(-1), _is_running(false), _pool(POOL_SIZE) {}
  ~Echo_server();

  Echo_server &operator=(Echo_server &other) = delete;

  void start();

private:
  int _server_fd;
  int _port;
  bool _is_running;
  Thread_pool _pool;

  void stop();
  void handle_client(int client_fd);
};