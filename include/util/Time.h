#ifndef _COMMON_UTIL_GTIME_H_
#define _COMMON_UTIL_GTIME_H_

#if defined(UTIL_EXPORTS)&&(defined(WIN32)||defined(WIN64))
	#define UTIL_DLL_API _declspec(dllexport)
#elif !defined(_LIB)&&(defined(WIN32)||defined(WIN64))&&!defined(_USRDLL)
	#define UTIL_DLL_API _declspec(dllimport)
#endif


#include <string>

namespace GCommon{
  namespace GUtil{

#if defined(UTIL_DLL_API)
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
