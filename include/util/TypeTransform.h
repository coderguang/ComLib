#ifndef _COMMON_UTIL_TYPETRANSFORM_H_
#define _COMMON_UTIL_TYPETRANSFORM_H_

/**
 *this is some func header 
 *create by coderguang
 *date 2015-08-18
 *e-mail:royalchen@royalchen.com
 * */


#if defined(UTIL_EXPORTS)&&(defined(WIN32)||defined(WIN64))
	#define UTIL_DLL_API _declspec(dllexport)
#elif !defined(_LIB)&&(defined(WIN32)||defined(WIN64))&&!defined(_USRDLL)
	#define UTIL_DLL_API _declspec(dllimport)
#endif


#include <sstream>
#include <iostream>
#include <ctime>

namespace GCommon{
  namespace GUtil{

#ifdef UTIL_DLL_API
	class UTIL_DLL_API CTypeTransform{
#else
	class CTypeTransform{
#endif
  public:
    static std::string IntToStr(int value);

    static int StrToInt(std::string value);


};

#define ToStr(n) CTypeTransform::IntToStr(n)


  }
}
#endif
