#ifndef _COMMON_LOG_LOG_H_
#define _COMMON_LOG_LOG_H_

#include <string>
#include <iostream>

#if defined(LOG_EXPORTS)&&defined(_WINDOWS)
	#define LOG_DLL_API _declspec(dllexport)
#elif defined(_WINDOWS)
	#define LOG_DLL_API _declspec(dllimport)
else
	#define LOG_DLL_API 
#endif


namespace GCommon{
  namespace GLog{

class CLog{
  public:
    static LOG_DLL_API void Log(std::string msg,std::string type="default");

};

  }
}

#endif
