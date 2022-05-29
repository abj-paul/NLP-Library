VPATH=..:.
run: NoisyChannelModel.o ConfusionMatrix.o MED.o KMP.o lib_string.o
	g++ NoisyChannelModel.o ConfusionMatrix.o MED.o KMP.o lib_string.o -o execute
NoisyChannelModel.o: NoisyChannelModel/NoisyChannelModel.cpp NoisyChannelModel/NoisyChannelModel.h
	g++ -c -g NoisyChannelModel/NoisyChannelModel.cpp
ConfusionMatrix.o: NoisyChannelModel/ConfusionMatrix.cpp NoisyChannelModel/ConfusionMatrix.h
	g++ -c -g NoisyChannelModel/ConfusionMatrix.cpp
MED.o: NoisyChannelModel/MED.cpp NoisyChannelModel/MED.h
	g++ -c -g NoisyChannelModel/MED.cpp
KMP.o: NoisyChannelModel/KMP.cpp NoisyChannelModel/KMP.h
	g++ -c -g NoisyChannelModel/KMP.cpp
lib_string.o: Data-Structures/lib_string.cpp Data-Structures/lib_string.h
	g++ -c -g Data-Structures/lib_string.cpp
clean:
	rm *.o
