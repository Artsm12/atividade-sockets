#include <iostream>
#include "./server.hpp"

int main() {
    Echo_server server(4444, 5);

    std::cout << "Iniciando servidor de echo..." << std::endl;

    server.start();
}