#ifndef PRINTOBJECT_H
#define PRINTOBJECT_H

#include <tpproto/objectvisitor.h>


class PrintObject : public TPProto::ObjectVisitor{
 public:
  PrintObject();
  virtual ~PrintObject();

  void visit(TPProto::Universe* ob);
  void visit(TPProto::Galaxy* ob);
  void visit(TPProto::StarSystem* ob);
  void visit(TPProto::Planet* ob);
  void visit(TPProto::Fleet* ob);
  void visit(TPProto::Object* ob);

 

};

#endif
