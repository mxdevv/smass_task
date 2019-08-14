#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__

#include "socket_server.h"
#include "socket.cpp"

class Socket_client
{
  Socket_server& socket_server;
  int sock;

public:
  Socket_client(Socket_server& socket_server);

  char* read(size_t size);
};

#endif
