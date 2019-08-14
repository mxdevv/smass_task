#include <iostream>
#include <functional>
#include <thread>
#include "socket_server.cpp"
#include "socket_client.cpp"

int main()
{
  Socket_server socket_server("/tmp/socket.opencv.smass");
  std::thread([&] {
    char* str = "Hello socket!";
    std::cout << "server run" << std::endl;
    socket_server.write(str, strlen(str));
  }).detach();

  sleep(1);

  Socket_client socket_client(socket_server);
  std::thread([&] {
    char* ret_str = nullptr;
    std::cout << "client run" << std::endl;
    ret_str = socket_client.read(256);
    std::cout << "ret_str: " << ret_str << std::endl;
  }).detach();

  sleep(1);
}
