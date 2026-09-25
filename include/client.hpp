#pragma once

#include <string>

class Client {

public:
  Client(std::string &host, int port)
      : _host(host), _port(port), _client_fd(-1) {}
  ~Client();

  bool connect_to_server();
  void start();
  void disconnect();

private:
  std::string _host;
  int _port;
  int _client_fd;
};