#include "stdafx.h"
#include "../include/log/Log.h"
using namespace GCommon::GLog;

/*
 * this cpp is use for windows dll
 * because create dll and winlib must include stdafx.h
 * and it can't use #ifdef _WINDOWS_ to include this header file
 * because all code before the #include "stdafx.h" will be ignore!
 */

void CLog::Log(std::string msg,std::string type){
    std::cout<<"type="<<type<<",msg="<<msg<<std::endl;
}
