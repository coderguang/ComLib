#include "TypeTransform.h"

using namespace GCommon::GUtil;

std::string GTypeTransform::IntToStr(int value){
    std::stringstream ss;
    ss<<value;
    return ss.str();
};

int GTypeTransform::StrToInt(std::string value){
    int number;
    std::stringstream ss;
    ss<<value;		//string -->stringstream
    ss>>number;		//stringstream-->int
    return number;
}

