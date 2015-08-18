#ifndef _COMMON_LOG_LOG_H_
#define _COMMON_LOG_LOG_H_

#include <string>
#include <iostream>

namespace GCommon{
  namespace GLogger{

class GLog{
  public:
    static void Log(std::string msg,std::string type="default");
};

  }
}

#endif
