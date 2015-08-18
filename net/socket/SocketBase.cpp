#include "../../log/Log.h"
#include "SocketBase.h"

using namespace GCommon::GNet::GSocket;
using namespace GCommon::GLog;

int GSocketBase::Socket(int family,int type,int protocol){
  int temp=socket(family,type,protocol);
  if(ERROR==temp){
    GLog::Log("socket init failed when call socket("<<family<<

  }


}

