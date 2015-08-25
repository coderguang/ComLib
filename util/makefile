../lib/libutil.a : *.o
	ar -crv ../lib/libutil.a *.o
*.o : *.cpp
	clang++ -Wall -c -g Time.cpp TypeTransform.cpp -std=c++11
clean :
	rm -rf *.o *~
