#include "Log.h"
using namespace GCommon::GLogger;

void GLog::Log(std::string msg,std::string type){
    std::cout<<"type="<<type<<",msg="<<msg<<std::endl;
}
