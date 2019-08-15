#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>

class Socket_server
{
  const char* path;
  int sock, conn;
  sockaddr_un saddr;
  socklen_t len;

public:

  Socket_server(const char* path);
  ~Socket_server();

  void write(unsigned char* data, int size);
};

#endif
