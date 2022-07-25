#ifndef _HTTP1_PARSER_H_
#define _HTTP1_PARSER_H_

#include <string>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "configure.h"

class HTTP1_Parser
{
public:
  // cppのstaticも他言語と同じく、インスタンスではなくクラス本体に属するメンバ変数宣言の挙動をする
  static char *get_filename(const char *excutive_file);
  static std::string argv_path_analyzer(std::string request_path, const char *path, const char *executive_file);
  static std::string get_requestline_path(char _pbuf[BUF_SIZE]);
};

#endif