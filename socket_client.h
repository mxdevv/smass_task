#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "socket_server.h"

class Socket_client
{
  const char* path;
  int sock;
  sockaddr_un saddr;                                                            
  socklen_t len;                                                                

public:
  Socket_client(const char* path);

  int read(unsigned char*& data);
};

#endif
