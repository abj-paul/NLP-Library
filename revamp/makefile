run: main.o lib_string.o lib_vector.o lib_punctuation.o SentenceSegmenter.o Tokenizer.o Stemmer.o Bigram.o Perplexity.o NoisyChannelModel.o NonWord.o
	g++ main.o lib_string.o lib_punctuation.o SentenceSegmenter.o Tokenizer.o Stemmer.o Bigram.o Perplexity.o NoisyChannelModel.o NonWord.o -o run
main.o: main.cpp Bigram.o
	g++ -c -g main.cpp
NonWord.o: NonWord.cpp NonWord.h
	g++ -c -g NonWord.cpp
NoisyChannelModel.o: NoisyChannelModel.cpp NoisyChannelModel.h
	g++ -c -g NoisyChannelModel.cpp
Perplexity.o: Perplexity.cpp Perplexity.h Bigram.o
	g++ -c -g Perplexity.cpp
Bigram.o: Bigram.cpp Bigram.h Tokenizer.o Stemmer.o
	g++ -c -g Bigram.cpp
Tokenizer.o: Tokenizer.cpp Tokenizer.h lib_vector.o lib_string.o
	g++ -c -g Tokenizer.cpp
SentenceSgmenter.o: SentenceSegmenter.cpp SentenceSegmenter.h lib_punctuation.o
	g++ -c -g SentenceSegmenter.cpp
lib_punctuation.o: lib_punctuation.cpp lib_punctuation.h lib_vector.o lib_string.o
	g++ -c -g lib_punctuation.cpp
Stemmer.o: lib_string.o lib_vector.o auxiliary.o Stemmer.cpp Stemmer.h
	g++ -c -g Stemmer.cpp
lib_string.o: lib_string.cpp lib_string.h
	g++ -c -g lib_string.cpp
lib_vector.o: lib_vector.h
	g++ -c -g lib_vector.h
auxiliary.o: auxiliary.h
	g++ -c -g auxiliary.h
clean:
	rm *.o run *.gch input_*.txt corpus_*.txt train_*.txt test_*.txt *_OUTPUT.txt
