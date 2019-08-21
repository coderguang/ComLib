../../lib/libsock.a : *.o
	ar -crv ../../lib/libsock.a *.o 
*.o : *.cpp 
	clang++ -Wall -c -fPIC *.cpp -std=c++11 
clean :
	-rm *.o *~

