#ifndef PRINTORDERPARAM_H
#define PRINTORDERPARAM_H

#include <tpproto/orderparametervisitor.h>

namespace TPProto{
  class OrderParameter;
}

class PrintOrderParam : public TPProto::OrderParameterVisitor{
 public:
  PrintOrderParam();
  virtual ~PrintOrderParam();

  

  void visitOrderParam(TPProto::SpaceCoordinates* op);
  void visitOrderParam(TPProto::TimeParameter* op);
  void visitOrderParam(TPProto::ObjectOrderParameter* op);
  void visitOrderParam(TPProto::ListParameter* op);
  void visitOrderParam(TPProto::PlayerParameter* op);
  void visitOrderParam(TPProto::SpaceCoordinatesRel* op);
  void visitOrderParam(TPProto::RangeParameter* op);
  void visitOrderParam(TPProto::StringParameter* op);
  void printOParam(TPProto::OrderParameter* op);

 private:
  

};

#endif
