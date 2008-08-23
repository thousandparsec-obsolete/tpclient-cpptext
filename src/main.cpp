/*  Main method for tpclient-cpptext
 *
 *  Copyright (C) 2004-2005, 2008  Lee Begg and the Thousand Parsec Project
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <tprl/rlcommand.h>
#include <tprl/commandalias.h>

#include <tpproto/gamelayer.h>
#include <tpproto/simpleeventloop.h>
#include <tpproto/gamestatuslistener.h>

#include <tpproto/object.h>
#include <tpproto/board.h>
#include <tpproto/message.h>
#include <tpproto/order.h>
#include <tpproto/orderparameter.h>
#include <tpproto/objectcache.h>
#include <tpproto/boardcache.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define VERSION "0.0.0"
#endif

#include "printlogger.h"
#include "printaflistener.h"
#include "printobject.h"
#include "printorderparam.h"
#include "console.h"

using namespace TPProto;

GameLayer *game;
SimpleEventLoop* eventloop;
Console* console;

void showObject(boost::shared_ptr<Object> ob){
  PrintObject po;
  po.visit(ob.get());
}

void showBoard(boost::shared_ptr<Board> currBoard){
  std::cout << std::endl;
  std::cout << "Name: " << currBoard->getName() << std::endl;
  std::cout << "Id: " << currBoard->getId() << std::endl;
  std::cout << "Description: " << currBoard->getDescription() << std::endl;
  std::cout << "Number of messages: " << currBoard->numMessages() << std::endl << std::endl;
}

class QuitCommand : public tprl::RLCommand{
  public:
    QuitCommand() : tprl::RLCommand(){
      name = "quit";
      help = "Exits tpclient-cpptext";
    }

    void action(const std::string & cmdline){
        eventloop->endEventLoop();
    }
};

class ConnectCommand : public tprl::RLCommand{
  public:
    ConnectCommand() : tprl::RLCommand(){
      name = "connect";
      help = "Connects to a server";
    }
    void action(const std::string & cmdline){
      if(game->getStatus() == gsDisconnected && game->connect(cmdline)){
         std::cout << "Connection started" << std::endl;
      }
    }
};

class LoginCommand : public tprl::RLCommand{
  public:
    LoginCommand() : tprl::RLCommand(){
        name = "login";
        help = "Log in to a player on the server.";
    }

    void action(const std::string & cmdline){
        if(game->getStatus() == TPProto::gsConnected){
            size_t p = cmdline.find(' ');
            if(game->login(cmdline.substr(0, p), cmdline.substr(p + 1))){
                std::cout << "Login ok, status: " << game->getStatus() << std::endl;
            }
        }else{
            std::cout << "Not connected or already logged in." << std::endl;
        }
    }
};

class DisconnectCommand : public tprl::RLCommand{
  public:
    DisconnectCommand() : tprl::RLCommand(){
        name = "disconnect";
        help = "Close the connection.";
    }

    void action(const std::string & cmdline){
        if(game->getStatus() != TPProto::gsDisconnected){
            game->disconnect();
        }
    }
};

class TimeCommand : public tprl::RLCommand{
  public:
    TimeCommand() : tprl::RLCommand(){
      name = "time";
      help = "Get the time to the next End of Turn.";
    }
    void action(const std::string & cmdline){
      game->getTimeRemaining();
    }
};

class ObjectCommand : public tprl::RLCommand{
  public:
    ObjectCommand() : tprl::RLCommand(){
      name = "object";
      help = "Get and display an Object.";
    }

    void action(const std::string& cmdline){
      game->getObjectCache()->requestObject(atoi(cmdline.c_str()), &showObject);
    }
};

class BoardCommand : public tprl::RLCommand{
  public:
    BoardCommand() : tprl::RLCommand(){
      name = "board";
      help = "Get and display a board.";
    }

    void action(const std::string& cmdline){
      game->getBoardCache()->requestBoard(atoi(cmdline.c_str()), &showBoard);
    }
};

#if 0
  // main loop
 

    if(command == "help"){

       std::cout << std::endl << "When working on an Object (prompt starts with \"Object\"):"<< std::endl;
      std::cout << "\tshow - show the object" << std::endl;
      std::cout << "\torder - gets and print an order (takes one arg)" << std::endl;
      std::cout << "\tdel_order - removes an order from the object (takes one arg)" << std::endl;

      std::cout << std::endl << "When working on a Board (prompt starts with \"Board\"):"<< std::endl;
      std::cout << "\tshow - show the properities of the board" << std::endl;
      std::cout << "\tmessage - gets and prints the message (takes one arg)" << std::endl;
      std::cout << "\tdel_message - removes a message from the board (takes one arg)" << std::endl;

    }else if(command == "time"){
      std::cout << "Time Remaining: ";
        int tvrem = game->getTimeRemaining();
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
      streamline >> id;
      Object* ob = game->getObject(id);
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
      streamline >> id;
      Board* bb = game->getBoard(id);
      if(bb == NULL){
	std::cout << "Did not get Board" << std::endl;
      }else{
	if(currBoard != NULL){
	  delete currBoard;
	}
	currBoard = bb;
	brdobj = false;

      }
    }else if(brdobj){
      if(currObj != NULL){
	if(command == "show"){
	  currObj->visit(objectprinter);
	}else if(command == "order"){
	  int id;
	  streamline >> id;
	  Order* order = game->getOrder(currObj->getId(), id);
	    if(order != NULL){
	      std::cout << std::endl;
	      std::cout << "Order Type: " << order->getOrderType() << std::endl;
	      std::cout << "Slot: " << order->getSlot() << std::endl;
	      std::cout << "Turns: " << order->getNumTurns() << std::endl;
	      std::cout << "Num Params: " << order->getNumParameters() << std::endl;
	      for(unsigned int i = 0; i < order->getNumParameters(); i++){
		order->getParameter(i)->visit(orderParamPrinter);
	      }
	      delete order;
	      std::cout << std::endl;
	    }
	  
	}else if(command == "del_order"){
	  int id;
	  streamline >> id;
	  if(game->removeOrder(currObj->getId(), id)){
	    std::cout << "Did not remove order" << std::endl;
	  }
	}
      }
    }else{
      if(currBoard != NULL){
	if(command == "show"){
	  std::cout << std::endl;
	  std::cout << "Name: " << currBoard->getName() << std::endl;
	  std::cout << "Id: " << currBoard->getId() << std::endl;
	  std::cout << "Description: " << currBoard->getDescription() << std::endl;
	  std::cout << "Number of messages: " << currBoard->numMessages() << std::endl << std::endl;
	}else if(command == "message"){
	  int id;
	  streamline >> id;
	  Message* msg = game->getMessage(currBoard->getId(), id);
	    if(msg != NULL){
	      std::cout << std::endl << "Message Subject: " << msg->getSubject() << std::endl;
	      std::cout << "Body: " << msg->getBody() << std::endl << std::endl;
	      delete msg;
	    }
	  
	}else if(command == "del_message"){
	  int id;
	  streamline >> id;
	  if(game->removeMessage(currBoard->getId(), id)){
	    std::cout << "Did not remove message" << std::endl;
	  }
	}
      }
    }
}

#endif

int main(int argc, char** argv){

  std::cout << "tpclient-cpptext " << VERSION << std::endl;

    game = new GameLayer();
    game->setClientString(std::string("tpclient-cpptext/") + VERSION);

  //async rame listener
  //  fc->setAsyncFrameListener(new PrintAFListener());
  //logger
  game->setLogger(new PrintLogger());

  eventloop = new SimpleEventLoop();
  game->setEventLoop(eventloop);

  std::set<tprl::RLCommand*> commands;
  commands.insert(new ConnectCommand());
  commands.insert(new DisconnectCommand());
  commands.insert(new LoginCommand());
  commands.insert(new TimeCommand());
  commands.insert(new ObjectCommand());
  commands.insert(new BoardCommand());

  tprl::RLCommand* quit = new QuitCommand();
  tprl::CommandAlias *exit = new tprl::CommandAlias("exit");
  exit->setTarget(quit);
  commands.insert(quit);
  commands.insert(exit);

  console = new Console();
  console->setCommandSet(&commands);
  console->connect();
  console->start();
  
  eventloop->listenForSocketRead(console);
  eventloop->runEventLoop();
  
  game->disconnect();
  delete game;

  console->stop();
  delete console;

  return 0;
}
