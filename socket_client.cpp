#ifndef __SOCKET_CLIENT_CPP__
#define __SOCKET_CLIENT_CPP__

#include <exception>
#include "socket_client.h"

Socket_client::Socket_client(Socket_server& socket_server)
  : socket_server(socket_server)
{
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }
}

char* Socket_client::read(size_t size)
{

  if (connect(sock, (struct sockaddr*)&socket_server.saddr,
      socket_server.len) < 0) {
    perror("connect");
    throw std::exception();
  }

  char* buf = new char[size];
  ::read(sock, buf, size);
  return buf;
}

#endif
