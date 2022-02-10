a.out: find_string_match.o sentence-probablity.o String-Library.o
	g++ find_string_match.o sentence_probablity.o String-Library.o -o nlp

String-Library.o: String-Library.o
	g++ -c String-Library.cpp
find_string_match.o: find_string_match.o String-Library.o
	g++ -c find_string_match.cpp
sentence-probablity.o: String-Library.o find_string_match.o sentence-probablity.o
	g++ -c sentence-probablity.cpp
