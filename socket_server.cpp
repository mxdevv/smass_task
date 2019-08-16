#ifndef __SOCKET_SERVER_CPP__
#define __SOCKET_SERVER_CPP__

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

int Socket_server::write(unsigned char* data, int size)
{
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    // все ошибки выводим, если не надо перенаправляем в log файл или /dev/null
    std::cerr << "Socket_server::write(): "; perror("socket");
    close(sock);
    return 0;
  }

  unlink(path);
  if (bind(sock, (struct sockaddr*)&saddr, len) < 0) {
    // все ошибки выводим, если не надо перенаправляем в log файл или /dev/null
    std::cerr << "Socket_server::write(): "; perror("bind");
    close(sock);
    return 0;
  }

  listen(sock, 10);

  if ((conn = accept(sock, NULL, NULL)) < 0) {
    // все ошибки выводим, если не надо перенаправляем в log файл или /dev/null
    std::cerr << "Socket_server::write(): "; perror("accept");
    close(conn);
    close(sock);
    return 0;
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

  return total;
}

#endif
