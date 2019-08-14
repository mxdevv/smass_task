#ifndef __SOCKET_CLIENT_CPP__
#define __SOCKET_CLIENT_CPP__

#include <exception>
#include "socket_client.h"

Socket_client::Socket_client(Socket_server& socket_server)
  : socket_server(socket_server)
{ }

unsigned char* Socket_client::read()
{
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    throw std::exception();
  }

  if (connect(sock, (struct sockaddr*)&socket_server.saddr,
      socket_server.len) < 0) {
    perror("connect");
    throw std::exception();
  }

  unsigned char* buf = new unsigned char[socket_server.t_size];
  int total = 0, n;
  while(total < socket_server.t_size) {
    n = recv(sock, buf + total, socket_server.t_size - total, 0);
    if (n == -1) {
      break;
    }
    total += n;
  }

  close(sock);

  return buf;
}

#endif
