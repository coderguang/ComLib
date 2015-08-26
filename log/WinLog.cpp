#include "stdafx.h"

#include "../include/log/Log.h"

/*
 * this cpp is use for windows dll
 * because create dll and winlib must include stdafx.h
 * and it can't use #ifdef _WINDOWS_ to include this header file
 * because all code before the #include "stdafx.h" will be ignore!

 */
using namespace GCommon::GLog;

void CLog::Log(std::string msg, std::string type){
    std::cout<<"type="<<type<<",msg="<<msg<<std::endl;
}
