
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

  bool happy = true;
  // main loop
  while(happy && !std::cin.eof()){
    std::cout << "> " << std::flush;

    std::string command;
    std::cin >> std::ws >> command;

    if(command == "help"){
      std::cout << "Help" << std::endl;
      std::cout << "  Known commands are:" << std::endl;
      std::cout << "\thelp - this help" << std::endl;
      std::cout << "\tquit, exit - exits tpclient-cpptext" << std::endl;
      std::cout << "\tconnect - connect to server (takes one arg)" << std::endl;
      std::cout << "\tdisconnect - disconnect from server" << std::endl;
    }else if(command == "quit" || command == "exit"){
      happy = false;
    }else if(command == "connect"){
      std::string host;
      std::cin >> std::ws >> host;
      sock->setServerAddr(host.c_str());
      fc->connect();
    }else if(command == "disconnect"){
      if(fc->getStatus() != 0){
	fc->disconnect();
      }
    }
    
    if(fc->getStatus() > 2){
      fc->pollForAsyncFrames();
    }

  }

  
  fc->disconnect();
  delete fc; // also takes care of sock for us

  return 0;

};
