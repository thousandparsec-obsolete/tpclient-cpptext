
#include <iostream>

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define VERSION "0.0.0"
#endif

int main(int argc, char** argv){

  std::cout << "tpclient-cpptext " << VERSION << std::endl;


  return true;

};
