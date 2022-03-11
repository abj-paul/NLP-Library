run: main.o lib_string.o lib_vector.o lib_punctuation.o
	g++ main.o lib_string.o lib_punctuation.o -o run
main.o: main.cpp lib_string.o lib_vector.o
	g++ -c -g main.cpp
lib_punctuation.o: lib_punctuation.cpp lib_punctuation.h lib_vector.o lib_string.o
	g++ -c -g lib_punctuation.cpp
lib_string.o: lib_string.cpp lib_string.h
	g++ -c -g lib_string.cpp
lib_vector.o: lib_vector.h
	g++ -c -g lib_vector.h
clean:
	rm *.o run
