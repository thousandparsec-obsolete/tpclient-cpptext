
#include <iostream>
#include <string>

#include <tpproto/framecodec.h>
#include <tpproto/tcpsocket.h>
#include <tpproto/object.h>
#include <tpproto/board.h>
#include <tpproto/getobjectbyid.h>
#include <tpproto/getboard.h>

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
  Object* currObj = NULL;
  Board* currBoard = NULL;
  bool brdobj = true;

  // main loop
  while(happy && !std::cin.eof()){
    if(brdobj){
      if(currObj != NULL){
	std::cout << "Object: " << currObj->getName();
      }
    }else{
      if(currBoard != NULL){
	std::cout << "Board: " << currBoard->getName();
      }
    }

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
      std::cout << "\tobject - get an object, take an id arg" << std::endl;
      std::cout << "\tboard - get a board, take an id arg" << std::endl;
      std::cout << std::endl << "When working on an Object (prompt starts with \"Object\"):"<< std::endl;

      std::cout << std::endl << "When working on a Board (prompt starts with \"Board\"):"<< std::endl;

    }else if(command == "quit" || command == "exit"){
      happy = false;
    }else if(command == "connect"){
      std::string host;
      std::cin >> std::ws >> host;
      sock->setServerAddr(host.c_str());
      fc->connect();
      if(currObj != NULL){
	delete currObj;
	currObj = NULL;
      }
      if(currBoard != NULL){
	delete currBoard;
	currBoard = NULL;
      }
    }else if(command == "disconnect"){
      if(fc->getStatus() != 0){
	fc->disconnect();
      }
      if(currObj != NULL){
	delete currObj;
	currObj = NULL;
      }
      if(currBoard != NULL){
	delete currBoard;
	currBoard = NULL;
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
      
    }else if(command == "object"){
      int id;
      std::cin >> id;
      GetObjectByID* go = fc->createGetObjectByIDFrame();
      go->addObjectID(id);
      Object* ob = fc->getObjects(go).begin()->second;
      if(ob == NULL){
	std::cout << "Did not get object" << std::endl;
      }else{
	if(currObj != NULL){
	  delete currObj;
	}
	currObj = ob;
	brdobj = true;
      }
      

    }else if(command == "board"){
      int id;
      std::cin >> id;
      GetBoard* gb = fc->createGetBoardFrame();
      gb->addBoardId(id);
      Board* bb = fc->getBoards(gb).begin()->second;
      if(bb == NULL){
	std::cout << "Did not get Board" << std::endl;
      }else{
	if(currBoard != NULL){
	  delete currBoard;
	}
	currBoard = bb;
	brdobj = false;

      }
    }

    
    
    if(fc->getStatus() > 2){
      fc->pollForAsyncFrames();
    }

  }

  if(currObj != NULL){
    delete currObj;
  }
  if(currBoard != NULL){
    delete currBoard;
  }
  
  fc->disconnect();
  delete fc; // also takes care of sock for us

  std::cout << std::endl;

  return 0;

};
