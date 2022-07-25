#include "socket.h"

void Socket::set_listenfd()
{
  this->listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->listenfd == -1)
  {
    std::cout << "socket() failed." << std::endl;
    exit(1);
  }
}

void Socket::set_sockaddr_in()
{
  // &this->serv_addrは&(this->serv_addrと同じ)
  // [C++ の組み込み演算子、優先順位、結合規則](https://docs.microsoft.com/ja-jp/cpp/cpp/cpp-built-in-operators-precedence-and-associativity?view=msvc-170)
  memset(&this->serv_addr, 0, sizeof(this->serv_addr));

  this->serv_addr.sin_family = AF_INET;
  this->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  this->serv_addr.sin_port = htons(this->port);
}

int Socket::set_socket()
{
  // Q:this->set_listenfd();あるいはset_listenfd();でも同じではないか？？
  Socket::set_listenfd();
  int optval = 1;
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
  {
    std::cout << "setsockopt() failed." << std::endl;
    close(listenfd);
    return -1;
  }

  Socket::set_sockaddr_in();
  //[アドレス演算子"&"は、そのオベランドへのアドレス（=ポインタ）が返される](https://docs.microsoft.com/ja-jp/cpp/cpp/address-of-operator-amp?view=msvc-170)
  if (bind(this->listenfd, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr)) == -1)
  {
    std::cout << "bind() failed.(" << errno << ")" << std::endl;
    close(this->listenfd);
    return -1;
  }

  if (listen(this->listenfd, SOMAXCONN) == -1)
  {
    std::cout << "listen() failed." << std::endl;
    close(this->listenfd);
    return -1;
  }

  return 0;
}