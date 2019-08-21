../lib/liblog.a : Log.o
	ar -crv ../lib/liblog.a Log.o
Log.o : Log.cpp
	clang++ -Wall -c -g Log.cpp -std=c++11
clean :
	-rm -rf *.o *~

