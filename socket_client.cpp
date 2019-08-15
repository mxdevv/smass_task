#ifndef __SOCKET_CLIENT_CPP__
#define __SOCKET_CLIENT_CPP__

#include "socket_client.h"

Socket_client::Socket_client(const char* path)
  : path(path)
{
  saddr.sun_family = AF_UNIX;                                                   
  strcpy(saddr.sun_path, path);                                                 
  len = strlen(path) + sizeof(saddr.sun_family);                                
}

int Socket_client::read(unsigned char*& data)
{
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    /*perror("socket");
    throw std::exception();*/
    close(sock);
    return 0;
  }

  if (connect(sock, (struct sockaddr*)&saddr, len) < 0) {
    /*perror("connect");
    throw std::exception();*/
    close(sock);
    return 0;
  }

  int size = 0;
  while(!recv(sock, &size, sizeof(size), 0));

  unsigned char* buf = new unsigned char[size];
  int total = 0, n;
  while(total < size) {
    n = recv(sock, buf + total, size - total, 0);
    if (n == -1) {
      break;
    }
    total += n;
  }

  close(sock);

  data = buf;

  return total;
}

#endif
