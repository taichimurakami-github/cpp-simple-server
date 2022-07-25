#include "http1parser.h"

char *HTTP1_Parser::get_filename(const char *excutive_file)
{
  int length = strlen(excutive_file);
  static char buf[BUF_SIZE] = {};
  readlink("/proc/self/exe", buf, sizeof(buf) - 1);
  int buf_length = strlen(buf);

  for (int i = 0; i <= length; i++)
  {
    buf[buf_length - i - 1] = 0;
  }

  return buf;
}

std::string HTTP1_Parser::argv_path_analyzer(std::string request_path, const char *path, const char *executive_file)
{
  std::string path_string;
  // int strcmp(str1, str2): ２つの文字列の文字コードの差(str1 - str2)を整数値で返す
  // c言語では、２つの文字列が一致しているかどうかを判定するのによく用いる
  if (strcmp(path, "") == 0)
  {
    if (request_path == std::string("/"))
    {
      path_string = std::string(HTTP1_Parser::get_filename(executive_file)) + std::string("/index.html");
    }
    else
    {
      int judge = request_path.rfind(".", 20);
      if (judge >= 0)
      {
        path_string = std::string(HTTP1_Parser::get_filename(executive_file)) + request_path;
      }
      else
      {
        path_string = std::string(HTTP1_Parser::get_filename(executive_file)) + request_path + std::string("/index.html");
      }
    }
  }
  else
  {
    int judge = request_path.rfind(".", 20);
    if (judge >= 0)
    {
      path_string = std::string(path) + request_path;
    }
    else
    {
      path_string = std::string(path) + request_path + std::string("/index.html");
    }
  }

  return path_string;
}

std::string HTTP1_Parser::get_requestline_path(char _pbuf[BUF_SIZE])
{
  int space_num = 0;
  char path_buffer[32];
  int current_point = 0;
  std::string path_string;
  for (int i = 0; i < BUF_SIZE; i++)
  {
    if (space_num == 2)
    {
      path_buffer[current_point] = 0;
      path_string = std::string(path_buffer);
      return path_string;
    }
    if (space_num == 1)
    {
      if (_pbuf[i] == 1)
      {
        path_buffer[current_point++] = _pbuf[i];
      }
    }
    if (_pbuf[i] == ' ')
    {
      ++space_num;
    }
  }

  return "";
}