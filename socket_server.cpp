#ifndef __SOCKET_SERVER_CPP__
#define __SOCKET_SERVER_CPP__

#include <exception>
#include "socket_server.h"

Socket_server::Socket_server(const char* path)
  : path(path)
{
  saddr.sun_family = AF_UNIX;
  strcpy(saddr.sun_path, path);
  len = strlen(path) + sizeof(saddr.sun_family);
}

Socket_server::~Socket_server()
{
  unlink(path);
}

void Socket_server::write(unsigned char* data, int size)
{
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    throw std::exception();
  }

  unlink(path);
  if (bind(sock, (struct sockaddr*)&saddr, len) < 0) {
    perror("bind");
    throw std::exception();
  }

  listen(sock, 10);

  if ((conn = accept(sock, NULL, NULL)) < 0) {
    perror("accept");
    throw std::exception();
  }

  while(!send(conn, &size, sizeof(size), 0));

  int total = 0, n;
  while(total < size) {
    n = send(conn, data + total, size - total, 0);
    if (n == -1) {
      break;
    }
    total += n;
  }

  close(conn);
  close(sock);
}

#endif
