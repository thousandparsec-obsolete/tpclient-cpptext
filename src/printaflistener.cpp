
#include <iostream>
#include <tpproto/timeremaining.h>

#include "printaflistener.h"

using namespace TPProto;

PrintAFListener::PrintAFListener(){
}

PrintAFListener::~PrintAFListener(){
}

void PrintAFListener::recvTimeRemaining(TimeRemaining* trf){
  std::cout << "Time Remaining: ";
  int tvrem = trf->getTimeRemaining();
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

  std::cout << tvrem << " seconds." << std::endl << std::endl;

}

