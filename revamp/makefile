run: main.o lib_string.o lib_vector.o
	g++ main.o lib_string.o -o run
main.o: main.cpp lib_string.o lib_vector.o
	g++ -c main.cpp 
lib_string.o: lib_string.cpp lib_string.h
	g++ -c lib_string.cpp
lib_vector.o: lib_vector.h
	g++ -c lib_vector.h
clean:
	rm *.o run
