
#include <iostream>


#include <tpproto/orderparameter.h>
#include <tpproto/spacecoord.h>
#include <tpproto/timeparameter.h>
#include <tpproto/objectparameter.h>
#include <tpproto/listparameter.h>
#include <tpproto/playerparameter.h>
#include <tpproto/spacecoordrel.h>
#include <tpproto/rangeparameter.h>
#include <tpproto/stringparameter.h>

#include "printorderparam.h"

using namespace TPProto;

PrintOrderParam::PrintOrderParam(){
}

PrintOrderParam::~PrintOrderParam(){
}


void PrintOrderParam::visitOrderParam(SpaceCoordinates* op){
  printOParam((OrderParameter*)op);
  std::cout << "Pos: <" << op->getPos().getX() << ", " << op->getPos().getY() << ", " << op->getPos().getZ() << ">" << std::endl;
}

void PrintOrderParam::visitOrderParam(TimeParameter* op){
  printOParam((OrderParameter*)op);
  std::cout << "Time max: " << op->getMaximumTurns() << std::endl;
  std::cout << "Turns: " << op->getTurns() << std::endl;
}

void PrintOrderParam::visitOrderParam(ObjectParameter* op){
  printOParam((OrderParameter*)op);
  std::cout << "Objectid: " << op->getObjectId() << std::endl;
}

void PrintOrderParam::visitOrderParam(ListParameter* op){
  printOParam((OrderParameter*)op);
  std::cout << "List parameter object and I'm lazy" << std::endl;
}

void PrintOrderParam::visitOrderParam(TPProto::PlayerParameter* op){
  printOParam((OrderParameter*)op);
  std::cout << "PlayerId: " << op->getPlayerId() << std::endl;
}

void PrintOrderParam::visitOrderParam(TPProto::SpaceCoordinatesRel* op){
  printOParam((OrderParameter*)op);
  std::cout << "Object Id: " << op->getObjectId() << std::endl;
  std::cout << "Pos: <" << op->getPos().getX() << ", " << op->getPos().getY() << ", " << op->getPos().getZ() << ">" << std::endl;
}

void PrintOrderParam::visitOrderParam(TPProto::RangeParameter* op){
  printOParam((OrderParameter*)op);
  std::cout << "Value: " << op->getValue() << std::endl;
  std::cout << "Limits: " << op->getMinimum() << " to " << op->getMaximum() << std::endl;
  std::cout << "Increment: " << op->getIncrement() << std::endl;
}

void PrintOrderParam::visitOrderParam(TPProto::StringParameter* op){
  printOParam((OrderParameter*)op);
  std::cout << "Max length: " << op->getMaxLength() << std::endl;
  std::cout << "String: " << op->getString() << std::endl;
}

void PrintOrderParam::printOParam(OrderParameter* op){
  std::cout << "OrderParameter" << std::endl << "Name: " << op->getName() << std::endl;
  std::cout << "Description: " << op->getDescription() << std::endl;
}
