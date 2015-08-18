#ifndef _COMMON_UTIL_GTIME_H_
#define _COMMON_UTIL_GTIME_H_
#include <string>

namespace GCommon{
  namespace GUtil{

class GTime{
  public:
    static std::string getTimeNow();

    static void delayTime(double sec);

};

  }
}
#endif
