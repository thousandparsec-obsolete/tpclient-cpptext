
#include <iostream>
#include <stdarg.h>

#include "printlogger.h"

PrintLogger::PrintLogger(){
}

PrintLogger::~PrintLogger(){
}

void PrintLogger::error(char* mesg, ...){
  char* fmsg = new char[100];
  va_list ap;
  va_start(ap, mesg);
  int reallen = vsnprintf(fmsg, 100, mesg, ap);
  if(reallen > 100){
    delete[] fmsg;
    fmsg = new char[reallen + 1];
    vsnprintf(fmsg, reallen, mesg, ap);
  }
  va_end(ap);
  std::cout << "Error: " << fmsg << std::endl;
  delete[] fmsg;
}

void PrintLogger::warning(char* mesg, ...){
  char* fmsg = new char[100];
  va_list ap;
  va_start(ap, mesg);
  int reallen = vsnprintf(fmsg, 100, mesg, ap);
  if(reallen > 100){
    delete[] fmsg;
    fmsg = new char[reallen + 1];
    vsnprintf(fmsg, reallen, mesg, ap);
  }
  va_end(ap);
  std::cout << "Warning: " << fmsg << std::endl;
  delete[] fmsg;
}

void PrintLogger::info(char* mesg, ...){
  char* fmsg = new char[100];
  va_list ap;
  va_start(ap, mesg);
  int reallen = vsnprintf(fmsg, 100, mesg, ap);
  if(reallen > 100){
    delete[] fmsg;
    fmsg = new char[reallen + 1];
    vsnprintf(fmsg, reallen, mesg, ap);
  }
  va_end(ap);
  std::cout << "Info: " << fmsg << std::endl;
  delete[] fmsg;
}

void PrintLogger::debug(char* mesg, ...){
  char* fmsg = new char[100];
  va_list ap;
  va_start(ap, mesg);
  int reallen = vsnprintf(fmsg, 100, mesg, ap);
  if(reallen > 100){
    delete[] fmsg;
    fmsg = new char[reallen + 1];
    vsnprintf(fmsg, reallen, mesg, ap);
  }
  va_end(ap);
  std::cout << "Debug: " << fmsg << std::endl;
  delete[] fmsg;
}
