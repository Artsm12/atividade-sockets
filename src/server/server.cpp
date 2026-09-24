#include "../../include/server.hpp"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

const int BUFFER_SIZE = 1024;

Echo_server::~Echo_server() { stop(); }

void Echo_server::start() {
  this->_server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (this->_server_fd < 0) {
    std::cerr << "Erro ao iniciar socket \n";
    return;
  }

  int opt = 1;
  setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(_port);

  if (bind(this->_server_fd, (sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    std::cerr << "Erro ao iniciar a porta \n";
    return;
  }

  if (listen(this->_server_fd, BACKLOG) < 0) {
    std::cerr << "Erro ao iniciar a conexão \n";
    return;
  }

  this->_is_running = true;
  std::cout << "Servidor rodando na porta: " << _port << std::endl;

  while (this->_is_running) {
    sockaddr_in client_addr{};
    socklen_t addr_len = sizeof(client_addr);

    int client_fd =
        accept(this->_server_fd, (struct sockaddr *)&client_addr, &addr_len);

    if (client_fd < 0) {
      if (!this->_is_running)
        break;
      std::cerr << "Erro ao aceitar a conexão com o cliente \n";
      continue;
    }

    this->_pool.enqueue(
        [this, client_fd]() { this->handle_client(client_fd); });
  }
}

void Echo_server::handle_client(int client_fd) {
  char buffer[BUFFER_SIZE] = {0};
  int bytes_read;

  while ((bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1)) > 0) {
    buffer[bytes_read] = '\0';

    std::string input(buffer);

    while (!input.empty() && (input.back() == '\r' || input.back() == '\n')) {
      input.pop_back();
    }

    if (input == "quit") {
      std::string s = "Encerrando o servidor...\n";
      send(client_fd, s.c_str(), s.size(), 0);

      close(client_fd);
      stop();
      return;
    }

    else if (input.rfind("echo ", 0) == 0) {
      std::string s = input.substr(5) + "\n";
      send(client_fd, s.c_str(), s.size(), 0);
    }

    else if (input == "echo") {
      std::string s = "\n";
      send(client_fd, s.c_str(), s.size(), 0);
    } else {
      std::string s = "Comando invalido. Use: 'echo <frase>' ou 'quit'\n";
      send(client_fd, s.c_str(), s.size(), 0);
    }

    memset(buffer, 0, BUFFER_SIZE);
  }

  close(client_fd);
}

void Echo_server::stop() {
  if (this->_is_running) {
    this->_is_running = false;
    if (this->_server_fd >= 0) {
      close(this->_server_fd);
      this->_server_fd = -1;
    }
  }
}
