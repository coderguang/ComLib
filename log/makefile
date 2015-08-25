../lib/liblog.a : *.o
	ar -crv ../lib/liblog.a Log.o
*.o : *.cpp
	clang++ -Wall -c -g *.cpp -std=c++11
clean :
	rm -rf *.o *~

