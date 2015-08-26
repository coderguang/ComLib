#include "stdafx.h"

#include "../include/log/Log.h"

/*
 * this cpp is use for windows dll
 * because create dll and winlib must include stdafx.h
 * and it can't use #ifdef _WINDOWS_ to include this header file
 * because all code before the #include "stdafx.h" will be ignore!

 */
#ifdef LOG_EXPORTS
	#define LOG_DLL_API _declspec(dllexport)
#else
	#define LOG_DLL_API _declspec(dllimport)
#endif


using namespace GCommon::GLog;

void CLog::Log(std::string msg, std::string type){
    std::cout<<"type="<<type<<",msg="<<msg<<std::endl;
}
