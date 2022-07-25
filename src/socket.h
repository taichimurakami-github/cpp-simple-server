#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "configure.h"

class Socket
{
  int listenfd;
  int port;
  /**
   * 参照：[sockaddr_in構造体](http://www.fos.kuis.kyoto-u.ac.jp/le2soft/siryo-html/node16.html)
   *  struct in_addr {
   *    u_int32_t s_addr;
   *  };
   *
   *  struct sockaddr_in {
   *    u_char  sin_len;    （このメンバは古いOSでは存在しない）
   *    u_char  sin_family;    （アドレスファミリ．今回はAF_INETで固定）
   *    u_short sin_port;    （ポート番号）
   *    struct  in_addr sin_addr;    （IPアドレス）
   *    char    sin_zero[8];    （無視してもよい．「詰め物」のようなもの）
   *  };
   */
  struct sockaddr_in serv_addr;

  explicit Socket(int port_) : port{port_} {}
  void set_listenfd();
  void set_sockaddr_in();
  int set_socket();

  int get_listenfd() const { return this->listenfd; }
};

#endif