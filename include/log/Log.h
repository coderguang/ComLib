#ifndef _COMMON_LOG_LOG_H_
#define _COMMON_LOG_LOG_H_
//This has some problem,if ignore this define ,winsock.dll can create
#if defined(LOG_EXPORTS)&&defined(_WINDOWS)
  #define LOG_DLL_API _declspec(dllexport)
#elif defined(_WINDOWS)
  #define LOG_DLL_API _declspec(dllimport)
#endif

#include <string>
#include <iostream>

namespace GCommon{
  namespace GLog{
	 
#ifdef LOG_DLL_API
	class LOG_DLL_API CLog{
#else 
	class CLog{
//#endif
  public:
	static void Log(std::string msg,std::string type="default");

};

  }
}

#endif
