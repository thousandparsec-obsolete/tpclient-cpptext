
#include <iostream>
#include <string>

#include <tpproto/framecodec.h>
#include <tpproto/tcpsocket.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define VERSION "0.0.0"
#endif

using namespace TPProto;

int main(int argc, char** argv){

  std::cout << "tpclient-cpptext " << VERSION << std::endl;

  FrameCodec* fc = new FrameCodec();
  fc->setClientString(std::string("tpclient-cpptext/") + VERSION);
  TcpSocket* sock = new TcpSocket();
  fc->setSocket(sock);

  //async frame listener
  //logger


  // main loop
  
  fc->disconnect();
  delete fc; // also takes care of sock for us

  return 0;

};
