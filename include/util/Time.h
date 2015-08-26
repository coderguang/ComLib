#ifndef _COMMON_UTIL_GTIME_H_
#define _COMMON_UTIL_GTIME_H_

#if defined(UTIL_EXPORTS)&&defined(_WINDOWS)
	#define UTIL_DLL_API _declspec(dllexport)
#elif defined(_WINDOWS)
	#define UTIL_DLL_API _declspec(dllimport)
#endif


#include <string>

namespace GCommon{
  namespace GUtil{

#if defined(_WINDOWS)
	  class UTIL_DLL_API CTime{
#else 
	class CTime{
#endif
  public:
	static  std::string getTimeNow();

    static void delayTime(double sec);

};

  }
}
#endif
