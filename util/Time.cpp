#include "../include/util/Time.h"

using namespace GCommon::GUtil;
std::string CTime::getTimeNow(){
    char *s;
    time_t now;
    time(&now);
    s=ctime(&now);
    std::string t=s;
    return t;	
}

void CTime::delayTime(double sec){
    time_t start_time,cur_time;
    time(&start_time);
    do{
      time(&cur_time);
    }while((cur_time-start_time<sec));
}

