
#include <iostream>
#include <string>

#include <tpproto/framecodec.h>
#include <tpproto/tcpsocket.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define VERSION "0.0.0"
#endif

#include "printlogger.h"
#include "printaflistener.h"

using namespace TPProto;

int main(int argc, char** argv){

  std::cout << "tpclient-cpptext " << VERSION << std::endl;

  FrameCodec* fc = new FrameCodec();
  fc->setClientString(std::string("tpclient-cpptext/") + VERSION);
  TcpSocket* sock = new TcpSocket();
  fc->setSocket(sock);

  //async frame listener
  fc->setAsyncFrameListener(new PrintAFListener());
  //logger
  fc->setLogger(new PrintLogger());

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
      std::cout << "\tlogin - login to server (takes two args)" << std::endl;
      std::cout << "\ttime - get the time before the next End Of Turn" << std::endl;
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
    }else if(command == "login"){
      std::string user, pass;
      std::cin >> std::ws >> user >> pass;
      std::cout << "User: " << user << " pass: " << pass << " foo" << std::endl;
      fc->login(user, pass);
    }else if(command == "time"){
      std::cout << "Time Remaining: ";
      int tvrem = fc->getTimeRemaining();
      bool seen = false;
      if(tvrem > 86400){
	std::cout << (tvrem / 86400) << " days, ";
	seen = true;
	tvrem = tvrem % 86400;
      }
      if(seen || tvrem > 3600){
	std::cout << (tvrem / 3600) << " hours, ";
	seen = true;
	tvrem = tvrem % 3600;
      }
      if(seen || tvrem > 60){
	std::cout << (tvrem / 60) << " minutes, ";
	seen = true;
	tvrem = tvrem % 60;
      }
      if(seen)
	std::cout << "and ";
      
      std::cout << tvrem << " seconds." << std::endl;
      
    }

    
    
    if(fc->getStatus() > 2){
      fc->pollForAsyncFrames();
    }

  }

  
  fc->disconnect();
  delete fc; // also takes care of sock for us

  std::cout << std::endl;

  return 0;

};
