#ifndef _COMMON_UTIL_TYPETRANSFORM_H_
#define _COMMON_UTIL_TYPETRANSFORM_H_

/**
 *this is some func header 
 *create by coderguang
 *date 2015-08-18
 *e-mail:royalchen@royalchen.com
 * */

#include <sstream>
#include <iostream>
#include <ctime>

namespace GCommon{
  namespace GUtil{

class CTypeTransform{
  public:
    static std::string IntToStr(int value);

    static int StrToInt(std::string value);


};

#define ToStr(n) CTypeTransform::IntToStr(n)


  }
}
#endif
