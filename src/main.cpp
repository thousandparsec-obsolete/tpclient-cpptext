/*  Main method for tpclient-cpptext
 *
 *  Copyright (C) 2004-2005  Lee Begg and the Thousand Parsec Project
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

#include <readline/readline.h>
#include <readline/history.h>

#include <tpproto/framecodec.h>
#include <tpproto/tcpsocket.h>
#include <tpproto/object.h>
#include <tpproto/board.h>
#include <tpproto/getobjectbyid.h>
#include <tpproto/getboard.h>
#include <tpproto/getmessage.h>
#include <tpproto/message.h>
#include <tpproto/getorder.h>
#include <tpproto/order.h>
#include <tpproto/orderparameter.h>
#include <tpproto/removeorder.h>
#include <tpproto/removemessage.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define VERSION "0.0.0"
#endif

#include "printlogger.h"
#include "printaflistener.h"
#include "printobject.h"
#include "printorderparam.h"

using namespace TPProto;

static bool brdobj = true;

char* command_generator(const char* text, int state)
{
  static int index, len;
  char *cname = NULL;

  /* If this is a new word to complete, initialize now.  This
     includes saving the length of TEXT for efficiency, and
     initializing the index variable to 0. */
  if (!state)
    {
      index = 0;
      len = strlen (text);
    }

  switch(index){
  case 0:
    if(strncasecmp(text, "quit", len) == 0){
      cname = (char*)malloc(5);
      strncpy(cname, "quit", 5);
      index = 1;
      break;
    }
  case 1:
    if(strncasecmp(text, "exit", len) == 0){
      cname = (char*)malloc(5);
      strncpy(cname, "exit", 5);
      index = 2;
      break;
    }
  case 2:
    if(strncasecmp(text, "help", len) == 0){
      cname = (char*)malloc(5);
      strncpy(cname, "help", 5);
      index = 3;
      break;
    }
  case 3:
    if(strncasecmp(text, "connect", len) == 0){
      cname = (char*)malloc(8);
      strncpy(cname, "connect", 8);
      index = 4;
      break;
    }
  case 4:
    if(strncasecmp(text, "disconnect", len) == 0){
      cname = (char*)malloc(11);
      strncpy(cname, "disconnect", 11);
      index = 5;
      break;
    }
  case 5:
    if(strncasecmp(text, "login", len) == 0){
      cname = (char*)malloc(6);
      strncpy(cname, "login", 6);
      index = 6;
      break;
    }
  case 6:
    if(strncasecmp(text, "time", len) == 0){
      cname = (char*)malloc(5);
      strncpy(cname, "time", 5);
      index = 7;
      break;
    }
  case 7:
    if(strncasecmp(text, "object", len) == 0){
      cname = (char*)malloc(7);
      strncpy(cname, "object", 7);
      index = 8;
      break;
    }
  case 8:
    if(strncasecmp(text, "board", len) == 0){
      cname = (char*)malloc(6);
      strncpy(cname, "board", 6);
      index = 9;
      break;
    }
  case 9:
    if(strncasecmp(text, "show", len) == 0){
      cname = (char*)malloc(5);
      strncpy(cname, "show", 5);
      index = 10;
      break;
    }
  case 10:
    if(brdobj && strncasecmp(text, "order", len) == 0){
      cname = (char*)malloc(6);
      strncpy(cname, "order", 6);
      index = 11;
      break;
    }
  case 11:
    if(brdobj && strncasecmp(text, "del_order", len) == 0){
      cname = (char*)malloc(10);
      strncpy(cname, "del_order", 10);
      index = 12;
      break;
    }
  case 12:
    if(!brdobj && strncasecmp(text, "message", len) == 0){
      cname = (char*)malloc(8);
      strncpy(cname, "message", 8);
      index = 13;
      break;
    }
  case 13:
    if(!brdobj && strncasecmp(text, "del_message", len) == 0){
      cname = (char*)malloc(12);
      strncpy(cname, "del_message", 12);
      index = 14;
      break;
    }


  default:
    index = 99;
    break;
  }

  return cname;
}

char** command_completion (const char* text, int start, int end)
{
  char **matches;

  matches = (char **)NULL;

  if (start == 0)
    matches = rl_completion_matches (text, command_generator);
  
  rl_attempted_completion_over = 1;

  return (matches);
}

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

  PrintObject* objectprinter = new PrintObject();
  PrintOrderParam* orderParamPrinter = new PrintOrderParam();

  Object* currObj = NULL;
  Board* currBoard = NULL;


  //setup readline completion
  rl_attempted_completion_function = command_completion;

  // main loop
  while(true){
    std::ostringstream prompt;
    if(brdobj){
      if(currObj != NULL){
	prompt << "Object: " << currObj->getName();
      }
    }else{
      if(currBoard != NULL){
	prompt << "Board: " << currBoard->getName();
      }
    }

    prompt << "> ";

    char* line = readline(prompt.str().c_str());
    if(line == NULL)
      break;

    add_history(line);

    std::istringstream streamline;
    streamline.str(std::string(line));

    std::string command;
    streamline >> std::ws >> command;

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
      std::cout << "\tshow - show the object" << std::endl;
      std::cout << "\torder - gets and print an order (takes one arg)" << std::endl;
      std::cout << "\tdel_order - removes an order from the object (takes one arg)" << std::endl;

      std::cout << std::endl << "When working on a Board (prompt starts with \"Board\"):"<< std::endl;
      std::cout << "\tshow - show the properities of the board" << std::endl;
      std::cout << "\tmessage - gets and prints the message (takes one arg)" << std::endl;
      std::cout << "\tdel_message - removes a message from the board (takes one arg)" << std::endl;

    }else if(command == "quit" || command == "exit"){
      break;
    }else if(command == "connect"){
      std::string host;
      streamline >> std::ws >> host;
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
      streamline >> std::ws >> user >> pass;
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
      streamline >> id;
      GetObjectByID* go = fc->createGetObjectByIDFrame();
      go->addObjectID(id);
      Object* ob = fc->getObjects(go).begin()->second;
      delete go;
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
      GetBoard* gb = fc->createGetBoardFrame();
      gb->addBoardId(id);
      Board* bb = fc->getBoards(gb).begin()->second;
      delete gb;
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
	  GetOrder* go = fc->createGetOrderFrame();
	  go->setObjectId(currObj->getId());
	  go->addOrderId(id);
	  std::map<unsigned int, Order*> ords = fc->getOrders(go);
	  delete go;
	  for(std::map<unsigned int, Order*>::iterator itcurr = ords.begin(); itcurr != ords.end(); ++itcurr){
	    Order* order = itcurr->second;
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
	  }
	}else if(command == "del_order"){
	  int id;
	  streamline >> id;
	  RemoveOrder* rg = fc->createRemoveOrderFrame();
	  rg->setObjectId(currObj->getId());
	  rg->removeOrderId(id);
	  if(fc->removeOrders(rg) != 1){
	    std::cout << "Did not remove order" << std::endl;
	  }
	  delete rg;
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
	  GetMessage* gm = fc->createGetMessageFrame();
	  gm->setBoard(currBoard->getId());
	  gm->addMessageId(id);
	  std::map<unsigned int, Message*> messgs = fc->getMessages(gm);
	  delete gm;
	  for(std::map<unsigned int, Message*>::iterator itcurr = messgs.begin(); itcurr != messgs.end(); ++itcurr){
	    Message* msg = itcurr->second;
	    if(msg != NULL){
	      std::cout << std::endl << "Message Subject: " << msg->getSubject() << std::endl;
	      std::cout << "Body: " << msg->getBody() << std::endl << std::endl;
	      delete msg;
	    }
	  }
	}else if(command == "del_message"){
	  int id;
	  streamline >> id;
	  RemoveMessage* rm = fc->createRemoveMessageFrame();
	  rm->setBoard(currBoard->getId());
	  rm->removeMessageId(id);
	  if(fc->removeMessages(rm) != 1){
	    std::cout << "Did not remove message" << std::endl;
	  }
	  delete rm;
	}
      }
    }

    
    
    if(fc->getStatus() > 2){
      fc->pollForAsyncFrames();
    }

    free(line); 

  }

  if(currObj != NULL){
    delete currObj;
  }
  if(currBoard != NULL){
    delete currBoard;
  }
  
  fc->disconnect();
  delete fc; // also takes care of sock for us

  //delete the local printers and helper objects
  delete objectprinter;
  delete orderParamPrinter;

  std::cout << std::endl;

  return 0;

};
