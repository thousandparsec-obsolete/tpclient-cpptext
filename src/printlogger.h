#ifndef PRINTLOGGER_H
#define PRINTLOGGER_H

#include <tpproto/logger.h>

class PrintLogger : public TPProto::Logger{
 public:
  PrintLogger();
  virtual ~PrintLogger();

  void error(char* mesg, ...);
  void warning(char* mesg, ...);
  void info(char* mesg, ...);
  void debug(char* mesg, ...);

};

#endif
