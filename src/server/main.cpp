#include "../../include/server.hpp"
#include <iostream>

int main() {
  Echo_server server(4444);

  std::cout << "Iniciando servidor de echo..." << std::endl;

  server.start();
}