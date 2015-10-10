#include <netdb.h>

int main(int argc,char **argv)
{
  struct hostent *hs;
  char *host="182.254.233.115";
  hs=gethostbyname(host);
  
  int i;


}
