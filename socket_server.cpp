#ifndef __SOCKET_SERVER_CPP__
#define __SOCKET_SERVER_CPP__

#include <exception>
#include "socket_server.h"

Socket_server::Socket_server(const char* path)
  : path(path)
{
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    throw std::exception();
  }

  saddr.sun_family = AF_UNIX;
  strcpy(saddr.sun_path, path);
  unlink(path);
  len = strlen(path) + sizeof(saddr.sun_family);
  if (bind(sock, (struct sockaddr*)&saddr, len) < 0) {
    perror("bind");
    throw std::exception();
  }

  listen(sock, 10);
}

Socket_server::~Socket_server()
{
  close(conn);
  unlink(path);
}

void Socket_server::write(unsigned char* data, size_t size)
{
  if ((conn = accept(sock, NULL, NULL)) < 0) {
    perror("accept");
    throw std::exception();
  }

  t_size = size;
  int total = 0, n;
  while(total < len) {
    n = send(conn, data + total, size - total, 0);
    if (n == -1) {
      break;
    }
    total += n;
  }

  close(conn);
}

#endif
