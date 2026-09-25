#include "../../include/client.hpp"
#include <string>

int main() {
  std::string host = "127.0.0.1";
  Client client(host, 4444);

  if (client.connect_to_server()) {
    client.start();
  }
}