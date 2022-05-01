VPATH=..:.
run: NoisyChannelModel.o ConfusionMatrix.o MED.o KMP.o lib_vector.o lib_string.o
	g++ NoisyChannelModel.o ConfusionMatrix.o MED.o KMP.o lib_string.o -o execute
NoisyChannelModel.o: NoisyChannelModel.cpp NoisyChannelModel.h
	g++ -c -g NoisyChannelModel.cpp
ConfusionMatrix.o: ConfusionMatrix.cpp ConfusionMatrix.h
	g++ -c -g ConfusionMatrix.cpp
MED.o: MED.cpp MED.h
	g++ -c -g MED.cpp
KMP.o: KMP.cpp KMP.h
	g++ -c -g KMP.cpp
lib_string.o: lib_string.cpp lib_string.h
	g++ -c -g ../lib_string.cpp
lib_vector.o: lib_vector.h
	g++ -c -g ../lib_vector.h
clean:
	rm *.o
