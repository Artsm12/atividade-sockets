#include "../../include/client.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

Client::~Client() { disconnect(); }

bool Client::connect_to_server() {
  _client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (_client_fd < 0) {
    std::cerr << "Erro ao criar socket do cliente.\n";
    return false;
  }

  sockaddr_in serv_addr{};
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(_port);

  if (inet_pton(AF_INET, _host.c_str(), &serv_addr.sin_addr) <= 0) {
    std::cerr << "Endereco IP invalido: " << _host << "\n";
    return false;
  }

  if (connect(_client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
      0) {
    std::cerr << "Falha ao conectar no servidor " << _host << ":" << _port
              << "\n";
    return false;
  }

  std::cout << "Conectado ao servidor " << _host << ":" << _port << "\n";
  std::cout << "Digite os comandos ('echo <frase>' ou 'quit'):\n";
  return true;
}

void Client::start() {
  if (_client_fd < 0)
    return;

  std::string input;
  char buffer[BUFFER_SIZE];

  while (true) {
    std::cout << "\n> " << std::flush;
    if (!std::getline(std::cin, input))
      break;

    if (input.empty())
      continue;

    std::string payload = input + "\n";
    int bytes_sent = send(_client_fd, payload.c_str(), payload.size(), 0);

    memset(buffer, 0, BUFFER_SIZE);
    int bytes_read = read(_client_fd, buffer, BUFFER_SIZE - 1);

    if (bytes_read > 0) {
      buffer[bytes_read] = '\0';
      std::cout << "Servidor: " << buffer << std::flush;
    }

    if (input == "quit") {
      break;
    }
  }
}

void Client::disconnect() {
  if (_client_fd >= 0) {
    close(_client_fd);
    _client_fd = -1;
  }
}