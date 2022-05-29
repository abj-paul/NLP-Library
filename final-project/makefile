run: main.o lib_string.o lib_punctuation.o BinarySearchTree.o SentenceSegmenter.o Tokenizer.o Stemmer.o Bigram.o OrderedSet.o PrecomputeNGram.o NGram.o ConfusionMatrix.o MED.o KMP.o DefineNoisyChannel.o NoisyChannelModel.o Evaluation.o KneeserNey.o SpellingCorrection.o Candidate.o
	g++ -g main.o lib_string.o lib_punctuation.o BinarySearchTree.o SentenceSegmenter.o Tokenizer.o Stemmer.o Bigram.o PrecomputeNGram.o NGram.o ConfusionMatrix.o MED.o KMP.o DefineNoisyChannel.o NoisyChannelModel.o Evaluation.o KneeserNey.o SpellingCorrection.o Candidate.o -o execute
main.o: main.cpp
	g++ -g -pg -c main.cpp
lib_string.o: Data-Structures/lib_string.h Data-Structures/lib_string.cpp
	g++ -g -pg -c Data-Structures/lib_string.cpp
lib_punctuation.o: Preprocess-data/lib_punctuation.cpp Preprocess-data/lib_punctuation.h
	g++ -g -pg -c Preprocess-data/lib_punctuation.cpp
BinarySearchTree.o: Data-Structures/BinarySearchTree.cpp Data-Structures/BinarySearchTree.h
	g++ -g -pg -c Data-Structures/BinarySearchTree.cpp
SentenceSegmenter.o: Preprocess-data/SentenceSegmenter.h Preprocess-data/SentenceSegmenter.cpp
	g++ -g -pg -c Preprocess-data/SentenceSegmenter.cpp
Tokenizer.o: Preprocess-data/Tokenizer.h Preprocess-data/Tokenizer.cpp
	g++ -g -pg -c Preprocess-data/Tokenizer.cpp
Stemmer.o: Preprocess-data/Stemmer.h Preprocess-data/Stemmer.cpp
	g++ -g -pg -c Preprocess-data/Stemmer.cpp
Bigram.o: LanguageModel/Bigram.cpp LanguageModel/Bigram.h
	g++ -g -pg -c LanguageModel/Bigram.cpp
OrderedSet.o: Data-Structures/OrderedSet.h
	g++ -g -pg -c Data-Structures/OrderedSet.h
PrecomputeNGram.o: LanguageModel/PrecomputeNGram.h LanguageModel/PrecomputeNGram.cpp
	g++ -g -pg -c LanguageModel/PrecomputeNGram.cpp
NGram.o: LanguageModel/NGram.cpp LanguageModel/NGram.h
	g++ -g -pg -c LanguageModel/NGram.cpp
ConfusionMatrix.o: NoisyChannelModel/ConfusionMatrix.h NoisyChannelModel/ConfusionMatrix.cpp
	g++ -g -pg -c NoisyChannelModel/ConfusionMatrix.cpp
MED.o: NoisyChannelModel/MED.h NoisyChannelModel/MED.cpp
	g++ -g -pg -c NoisyChannelModel/MED.cpp
KMP.o: NoisyChannelModel/KMP.h NoisyChannelModel/KMP.cpp
	g++ -g -pg -c NoisyChannelModel/KMP.cpp
DefineNoisyChannel.o: NoisyChannelModel/DefineNoisyChannel.h NoisyChannelModel/DefineNoisyChannel.cpp
	g++ -g -pg -c NoisyChannelModel/DefineNoisyChannel.cpp
NoisyChannelModel.o: NoisyChannelModel/NoisyChannelModel.h NoisyChannelModel/NoisyChannelModel.cpp
	g++ -g -pg -c NoisyChannelModel/NoisyChannelModel.cpp
Evaluation.o: Evaluation/Evaluation.cpp Evaluation/Evaluation.h
	g++ -g -pg -c Evaluation/Evaluation.cpp
KneeserNey.o: KneeserNey/KneeserNey.cpp KneeserNey/KneeserNey.h
	g++ -g -pg -c KneeserNey/KneeserNey.cpp
SpellingCorrection.o: Spelling-Correction/SpellingCorrection.h Spelling-Correction/SpellingCorrection.cpp
	g++ -g -pg -c Spelling-Correction/SpellingCorrection.cpp
Candidate.o: Spelling-Correction/Candidate.cpp
	g++ -g -pg -c Spelling-Correction/Candidate.cpp
clean:
	rm *.o *~ *.gch execute
