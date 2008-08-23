#ifndef PRINTLOGGER_H
#define PRINTLOGGER_H

#include <tpproto/logger.h>

class PrintLogger : public TPProto::Logger{
 public:
  PrintLogger();
  virtual ~PrintLogger();

  void error(const char* mesg, ...);
  void warning(const char* mesg, ...);
  void info(const char* mesg, ...);
  void debug(const char* mesg, ...);

};

#endif
