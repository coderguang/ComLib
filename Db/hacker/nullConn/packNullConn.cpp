//C++ file
/*
#***********************************************
#
#      Filename: pack.cpp
#
#      Author: coderguang 
#      Email: royalchen@royalchen.com
#      website: www.royalchen.com
#      Description: ----
#      put your result file in path 
#      
#     Create: 2016-01-20 15:47:39
#     Last Modified: 2016-01-20 15:47:39
#***********************************************
*/
#include <iostream>
#include <fstream>

using namespace std;

static const string src="../../../../result.txt";
static const string dest="../../../../packResult.txt";


int main(int argc,char **argv){
  
  std::ifstream fin(src.c_str());
  std::ofstream fout(dest.c_str());

  std::string lastline;
  std::string curline;
  
  while(fin>>curline){
    if(curline.find("√¸¡Ó")!=string::npos){
      //cout<<lastline<<endl;
      fout<<lastline<<endl;
    }
    lastline=curline;
  }
  
  fin.close();
  fout.close();
  return 0;

}
