#include "../include/util/TypeTransform.h"

using namespace GCommon::GUtil;

std::string CTypeTransform::IntToStr(int value){
    std::stringstream ss;
    ss<<value;
    return ss.str();
};

int CTypeTransform::StrToInt(std::string value){
    int number;
    std::stringstream ss;
    ss<<value;		//string -->stringstream
    ss>>number;		//stringstream-->int
    return number;
}

