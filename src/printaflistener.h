#ifndef PRINTAFLISTENER_H
#define PRINTAFLISTENER_H

#include <tpproto/asyncframelistener.h>

class PrintAFListener : public TPProto::AsyncFrameListener{
 public:
  PrintAFListener();
  virtual ~PrintAFListener();

  void recvTimeRemaining(TPProto::TimeRemaining* trf);

};

#endif
