#ifndef PRINTOBJECT_H
#define PRINTOBJECT_H

namespace TPProto{
  class Object;
}

class PrintObject{
 public:
  PrintObject();
  ~PrintObject();

  void visit(TPProto::Object* ob);

 

};

#endif
