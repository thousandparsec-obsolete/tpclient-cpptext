
#include <iostream>

#include <tpproto/object.h>
#include <tpproto/universe.h>
#include <tpproto/galaxy.h>
#include <tpproto/starsystem.h>
#include <tpproto/planet.h>
#include <tpproto/fleet.h>

#include "printobject.h"

using namespace TPProto;

PrintObject::PrintObject(){
}

PrintObject::~PrintObject(){
}

void PrintObject::visit(Universe* ob){
  visit((Object*)ob);
  
  std::cout << "Age: " << ob->getAge() << std::endl;
 
  std::cout << std::endl;

  
}

void PrintObject::visit(Galaxy* ob){
  visit((Object*)ob);
 
  std::cout << std::endl;

 
}

void PrintObject::visit(StarSystem* ob){
  visit((Object*)ob);
  
  std::cout << std::endl;

}

void PrintObject::visit(Planet* ob){
  visit((Object*)ob);
 
  std::cout << "Num orders: " << ob->getNumberOrders() << std::endl;

  std::cout << "Owned by: " << ob->getOwner() << std::endl;

//   if(!ob->getAvailableOrders().empty()){
//     funobject = ob->getId();
//     if(ob->getNumberOrders() > 0){
//       std::cout << "Getting orders" << std::endl;
//       GetOrder* go = fc->createGetOrderFrame();
//       go->setObjectId(ob->getId());
//       go->addOrderRange(0, ob->getNumberOrders());
//       std::map<unsigned int, Order*> orders = fc->getOrders(go);
//       for(std::map<unsigned int, Order*>::iterator itcurr = orders.begin(); itcurr != orders.end(); ++itcurr){
	
// 	std::cout << "Order: slot " << itcurr->second->getSlot() << std::endl;
// 	std::cout << "type: " << itcurr->second->getOrderType() << std::endl;
// 	std::cout << "num turns: " << itcurr->second->getNumTurns() << std::endl;
// 	std::cout << "num params: " << itcurr->second->getNumParameters() << std::endl;
	
// 	// for each parameter...
// 	for(unsigned int i = 0; i < itcurr->second->getNumParameters(); i++){
// 	  itcurr->second->getParameter(i)->visit(this);
// 	}
	
//       }
//     }
//   }

  std::cout << std::endl;
 
}

void PrintObject::visit(Fleet* ob){
  visit((Object*)ob);  

  std::cout << "Owned By: " << ob->getOwner() << std::endl;
  std::cout << "Damage: " << ob->getDamage() << std::endl;
  std::cout << "Ships: Scouts(" << ob->numShips(0) << "), Frigates(" << ob->numShips(1) << "), Battleships(" <<
    ob->numShips(2) << ")" << std::endl;

 //  if(!ob->getAvailableOrders().empty()){
//     funobject = ob->getId();
//     if(ob->getNumberOrders() > 0){
//       std::cout << "Getting orders" << std::endl;
//       GetOrder* go = fc->createGetOrderFrame();
//       go->setObjectId(ob->getId());
//       go->addOrderRange(0, ob->getNumberOrders());
//       std::map<unsigned int, Order*> orders = fc->getOrders(go);
//       for(std::map<unsigned int, Order*>::iterator itcurr = orders.begin(); itcurr != orders.end(); ++itcurr){
	
// 	std::cout << "Order: slot " << itcurr->second->getSlot() << std::endl;
// 	std::cout << "type: " << itcurr->second->getOrderType() << std::endl;
// 	std::cout << "num turns: " << itcurr->second->getNumTurns() << std::endl;
// 	std::cout << "num params: " << itcurr->second->getNumParameters() << std::endl;
	
// 	// for each parameter...
// 	for(unsigned int i = 0; i < itcurr->second->getNumParameters(); i++){
// 	  itcurr->second->getParameter(i)->visit(this);
// 	}
//       }
//     }
//  }

  std::cout << std::endl;
  
}

void PrintObject::visit(Object* ob){

  std::cout << std::endl << "Name: " << ob->getName() << std::endl;
  std::cout << "Id: " << ob->getId() << std::endl;
  std::cout << "Type: " << ob->getObjectType() << std::endl;
  std::cout << "Size: " << ob->getSize() << std::endl;

  std::set<unsigned int> obset = ob->getContainedObjectIds();
  std::cout << "Num contained: " << obset.size() << std::endl << "Contains: ";
  for(std::set<unsigned int>::iterator itcurr = obset.begin(); itcurr != obset.end(); ++itcurr){
    std::cout << (*itcurr) << " ";
  }
  std::cout << std::endl;

  if(!ob->getAvailableOrders().empty()){
    std::cout << "Available orders: ";
    std::set<unsigned int> ordset = ob->getAvailableOrders();
    for(std::set<unsigned int>::iterator itcurr = ordset.begin(); itcurr != ordset.end(); ++itcurr){
      std::cout << *itcurr << " ";
    }
    std::cout << std::endl;
  }

}


