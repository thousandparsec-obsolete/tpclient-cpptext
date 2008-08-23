
#include <iostream>

#include <tpproto/object.h>

#include "printobject.h"

using namespace TPProto;

PrintObject::PrintObject(){
}

PrintObject::~PrintObject(){
}


void PrintObject::visit(Object* ob){

  std::cout << std::endl << "Name: " << ob->getName() << std::endl;
  std::cout << "Id: " << ob->getId() << std::endl;
  std::cout << "Type: " << ob->getObjectType() << std::endl;
  //std::cout << "Size: " << ob->getSize() << std::endl;

  std::set<unsigned int> obset = ob->getContainedObjectIds();
  std::cout << "Num contained: " << obset.size() << std::endl << "Contains: ";
  for(std::set<unsigned int>::iterator itcurr = obset.begin(); itcurr != obset.end(); ++itcurr){
    std::cout << (*itcurr) << " ";
  }
  std::cout << std::endl;

//   if(!ob->getAvailableOrders().empty()){
//     std::cout << "Available orders: ";
//     std::set<unsigned int> ordset = ob->getAvailableOrders();
//     for(std::set<unsigned int>::iterator itcurr = ordset.begin(); itcurr != ordset.end(); ++itcurr){
//       std::cout << *itcurr << " ";
//     }
//     std::cout << std::endl;
//   }

}


