#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#include "socket.cpp"

class Socket_server
{
  const char* path;
  int sock, conn;
  sockaddr_un saddr;
  socklen_t len;

public:
  Socket_server(const char* path);
  ~Socket_server();

  void write(char* arr, size_t size);

  friend class Socket_client;
};

#endif
