#ifndef _COMMON_LOG_LOG_H_
#define _COMMON_LOG_LOG_H_
//This has some problem,if ignore this define ,winsock.dll can create
//as a lib,it can't had any _declspec define,when lib use for dll,it can't had _declspec define
//作为一个被dll引用的lib,该lib不能有_declspec宏定义，因此，必须保证该头文件不是被dll所引用时才设置_declspec宏
#if defined(LOG_EXPORTS)&&((defined(WIN32)||defined(WIN64)))
  #define LOG_DLL_API _declspec(dllexport)
#elif !defined(_LIB)&&(defined(WIN32)||defined(WIN64))&&!defined(_USRDLL)
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
#endif
  public:
	static void Log(std::string msg,std::string type="default");

};

  }
}

#endif
