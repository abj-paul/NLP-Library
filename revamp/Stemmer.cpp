#include "Stemmer.h"

abj::Stemmer::Stemmer(abj::String& word){
  this->word.initialize(word);
  this->build_vowel_consonant_count_array();
}
abj::Stemmer::Stemmer(){
  // Do nothing
}
void abj::Stemmer::initialize(abj::String& word){
  this->word.initialize(word);
  this->build_vowel_consonant_count_array();
}

void abj::Stemmer::build_vowel_consonant_count_array(){
  for(int i=0; i<this->word.size(); i++){
    if(isConsonant(i)) this->vowel_consonant_count.push(CONSONANT);
    else if(isPunctuation(this->word.get(i))) this->vowel_consonant_count.push(PUNCTUATION);
    else this->vowel_consonant_count.push(VOWEL);
  }
}

int abj::Stemmer::m_value(){
  if(this->word.size()<=1)return 0;

  int count_vc=0;
  for(int i=1; i<this->word.size(); i++){
    if(this->vowel_consonant_count.get(i-1)==VOWEL && this->vowel_consonant_count.get(i)==CONSONANT) count_vc++;
  }
  return count_vc;
}

bool abj::Stemmer::isConsonant(int i){
  char c= this->capitalize(this->word.get(i));
  if(c=='A' || c=='E' || c=='I' || c=='O' || c=='U') return false;
  else if(c=='Y'){
    if(i==0) return true;
    char previous_character = capitalize(this->word.get(i-1));
    if(previous_character=='A' || previous_character=='E' || previous_character=='I' || previous_character=='O' || previous_character=='U') return true;
    else return false;
  }

  if(c>='A' && c<='Z')return true;
  return false; // Punctuations are not consonants
}


char abj::Stemmer::smallize(char c){
  int offset = 'a' - 'A';
  if(c>='A' && c<='Z') c=c+offset;
  return c;

}

char abj::Stemmer::capitalize(char c){
  int offset = 'a' - 'A';
  if(c>='a' && c<='z') c=c-offset;
  return c;

}


bool abj::Stemmer::isPunctuation(char c){
  char all_punctuations[] = "!\"#$%&'()*+,-./:;<=>?@[]^_`{|}~\\";
  //  print_string(all_punctuations);
  int i=0;
  while(all_punctuations[i]!=0){
    if(all_punctuations[i]==c) return true;
    i++;
  }
  return false;
}


bool abj::Stemmer::isCapital(char c){
  if(c<='A' && c>='Z') return true;
  return false;
}


bool abj::Stemmer::regex(const char* condition, int index){
  if(capitalize(word.get(index))==capitalize(condition[1])) return true;
  return false;
}

bool abj::Stemmer::regex(const char* condtion){
  abj::String condition(condition);
  
  if(isCapital(condition.get(1))){
    if(capitalize(this->word.lastChar())==condition.get(1)){
      return true;
    }else return false;
  }
  else if(condition.equals("*v*")){
    for(int i=0; i<this->word.size(); i++){
      if(!isConsonant(i) && !isPunctuation(this->word.get(i))) return true;
      i++;
    }
    return false;
  }
  else if(condition.equals("*d")){
    if(this->word.size()<=1) return false;
    else if(isConsonant(this->word.size()-1) && isConsonant(this->word.size()-2)) return true;
    else return false;
  }
  else if(condition.equals("*o")){
    if(this->word.size()<=2) return false; 
    else{
      char c= capitalize(this->word.get(this->word.size()-1));
      int len = this->word.size();
      if(isConsonant(len-1) && c!='W' && c!='Y' && c!='X' && !isConsonant(len-2) && !isPunctuation(this->word.get(len-2)) && isConsonant(len-3)) return true;
      else{
	 return false;
      }
    }
  }
  return false; // Unknown Regex
}


bool abj::Stemmer::ends_with(const char* sufix, abj::String& word){ // Taking word as input just for beauty
  abj::String suffix(sufix);
  
  if(suffix.size()>word.size()){
    return false;
  }

  for(int i=this->word.size()-1, j=suffix.size()-1; j>=0; j--,i--){
    if(capitalize(this->word.get(i))!=capitalize(suffix.get(j))) return false;
  }
  return true;
}


void abj::Stemmer::replace_suffix(const char* prev_sufix, const char* new_sufix){
  // cut -> Add
  abj::String prev_suffix(prev_sufix);
  abj::String new_suffix(new_sufix);

  int stem_size = this->word.size()-prev_suffix.size();
  int old_len = this->word.size();


  this->word.set(stem_size,'\0');
  //  printf("After trimming Suffix: %s\n",word);
  int i=INT_INITIALIZE_VALUE, j=INT_INITIALIZE_VALUE;

  for(i=stem_size, j=0; i<old_len && j<new_suffix.size(); i++, j++){
    word.set(i,this->smallize(new_suffix.get(j)));
  }
  word.set(i,'\0');

  //  printf("After adding new suffix: %s\n",word);
}

abj::String abj::Stemmer::get_stem(){
  // 1a
  if(ends_with("sses",word)) replace_suffix("sses","ss");
  else if(ends_with("ies",word)) replace_suffix("ies","i");
  else if(ends_with("ss",word)) replace_suffix("ss","ss");
  else if(ends_with("s",word)) replace_suffix("s","");

  //1b
  else if(m_value()>0 && ends_with("EED",word)) replace_suffix("EED","EE");
  else if(regex("*v*") && ends_with("ED",word)) replace_suffix("ED","");
  else if(regex("*v*") && ends_with("ING",word)) replace_suffix("ING","");

  // Correction rules
  if(ends_with("AT",word)) replace_suffix("AT","ATE");
  else if(ends_with("BL",word)) replace_suffix("BL","BLE");
  else if(ends_with("IZ",word)) replace_suffix("IZ","IZE");

  //return word;

  // 1C
  if(regex("*v*") && ends_with("Y",word)) replace_suffix("Y","I"); 

  // Step 2
  if(this->m_value()>0){
    if(ends_with("ATIONAL",word)) replace_suffix("TIONAL", "TION"); 
    else if(ends_with("TIONAL",word)) replace_suffix("TIONAL", "TION");
    else if(ends_with("ENCI",word)) replace_suffix("ENCI", "ENCE");
    else if(ends_with("ANCI",word)) replace_suffix("ANCI", "ANCE");
    else if(ends_with("IZER",word)) replace_suffix("IZER", "IZE");
    else if(ends_with("ABLI",word)) replace_suffix("ABLI", "ABLE");
    else if(ends_with("ALLI",word)) replace_suffix("ALLI", "AL");
    else if(ends_with("ENTLI",word)) replace_suffix("ENTLI", "ENT");
    else if(ends_with("ELI",word)) replace_suffix("ELI", "E");
    else if(ends_with("OUSLI",word)) replace_suffix("OUSLI", "OUS");
    else if(ends_with("IZATION",word)) replace_suffix("IZATION", "IZE");
    else if(ends_with("ATION",word)) replace_suffix("ATION", "ATE");
    else if(ends_with("ATOR",word)) replace_suffix("ATOR", "ATE");
    else if(ends_with("ALISM",word)) replace_suffix("ALISM", "AL");
    else if(ends_with("IVENESS",word)) replace_suffix("IVENESS", "IVE");
    else if(ends_with("FULNESS",word)) replace_suffix("FULNESS", "FUL");
    else if(ends_with("OUSNESS",word)) replace_suffix("OUSNESS", "OUS");
    else if(ends_with("ALITI",word)) replace_suffix("ALITI", "AL");
    else if(ends_with("IVITI",word)) replace_suffix("IVITI", "IVE");
    else if(ends_with("BILITI",word)) replace_suffix("BILITI", "BLE");
  } 


  // Step 3
  if(this->m_value()>0){
    if(ends_with("ICATE",word))  replace_suffix("ICATE", "IC");
    else if(ends_with("ATIVE",word))  replace_suffix("ATIVE", "");
    else if(ends_with("ALIZE",word))  replace_suffix("ALIZE", "AL");
    else if(ends_with("ICITI",word))  replace_suffix("ICITI", "IC");
    else if(ends_with("ICAL",word))  replace_suffix("ICAL", "IC");
    else if(ends_with("FUL",word))  replace_suffix("FUL", "");
    else if(ends_with("NESS",word))  replace_suffix("NESS", "");
  }

  // Step 4
  if(this->m_value()>1){
    if(ends_with("AL",word))  replace_suffix("AL", "");
    else if(ends_with("ANCE",word))  replace_suffix("ANCE", "");
    else if(ends_with("ENCE",word))  replace_suffix("ENCE", "");
    else if(ends_with("ER",word))  replace_suffix("ER", "");
    else if(ends_with("IC",word))  replace_suffix("IC", "");
    else if(ends_with("ABLE",word))  replace_suffix("ABLE", "");
    else if(ends_with("IBLE",word))  replace_suffix("IBLE", "");
    else if(ends_with("ANT",word))  replace_suffix("ANT", "");
    else if(ends_with("EMENT",word))  replace_suffix("EMENT", "");
    else if(ends_with("MENT",word))  replace_suffix("MENT", "");
    else if(ends_with("ENT",word))  replace_suffix("ENT", "");
    
    else if((regex("*S",word.size()-1-3) || regex("*T",word.size()-1-3) ) && ends_with("ION",word))  replace_suffix("ION", "");
    else if(ends_with("OU",word))  replace_suffix("OU", "");
    else if(ends_with("ISM",word))  replace_suffix("ISM", "");
    else if(ends_with("ATE",word))  replace_suffix("ATE", "");
    else if(ends_with("ITI",word))  replace_suffix("ITI", "");
    else if(ends_with("OUS",word))  replace_suffix("OUS", "");
    else if(ends_with("IVE",word))  replace_suffix("IVE", "");
    else if(ends_with("IZE",word))  replace_suffix("IZE", "");


    // Step 5a
    if(this->m_value()>1 && ends_with("E",word))  replace_suffix("E", "");
    else if(this->m_value()==1 && !regex("*o") && ends_with("E",word))  replace_suffix("E", "");

    // Step 5b
    if(this->m_value()>1 && regex("*d") && regex("*L", word.size()-1)) replace_suffix("L","");
  }
  
  return this->word;
}
void abj::Stemmer::test_function(){
  /*printf("X is punction? %d\n",isPunctuation('x'));
  printf("\' is punction? %d\n",isPunctuation('\''));

  // Testing
  print_string(test_string);
  for(int i=0; i<string_len(test_string); i++){
    //printf("%c becomes %c\n",test_string[i],capitalize(test_string[i]));
    //printf("%c is %d\n",test_string[i],isConsonant(i,test_string));
    printf("%c",capitalize(test_string[i]));
  }
  printf("\n");
  for(int i=0; i<string_len(test_string); i++){
    //printf("%c becomes %c\n",test_string[i],capitalize(test_string[i]));
    //printf("%c is %d\n",test_string[i],isConsonant(i,test_string));
    printf("%d",isConsonant(i,test_string));
  }
  printf("\n");

  int* x = vowel_consonant_count_array(test_string);
  print_array(x,string_len(test_string));
  free(x);*/

  /*  printf("m-value of TREE = %d\n",m_value("TREE"));
  printf("m-value of BY = %d\n",m_value("BY"));
  printf("m-value of OATS = %d\n",m_value("OATS"));
  printf("m-value of TREES = %d\n",m_value("trees"));
  printf("m-value of IVY = %d\n",m_value("ivy"));
  printf("m-value of TROUBLE = %d\n",m_value("trouble"));
  printf("m-value of TROUBLES = %d\n",m_value("troubles"));
  printf("m-value of OATEN = %d\n",m_value("oaten"));
  printf("m-value of PRIVATE = %d\n",m_value("private"));


  printf("Checking regex:\n");
  printf("*v* : Plastered=%d\n",regex("*v*","Plastered"));
  printf("*S : Walkers=%d\n",regex("*S","walkers"));
  printf("*d : Caress=%d\n",regex("*d","Caress"));
  printf("*o : Reganwil=%d\n",regex("*o","Reganwil"));*/

  //char editable_string[MAX_WORD_SIZE*2] = "Caresses";

  //printf("Caresses ends with %d\n",ends_with("sses",editable_string));
  //replace_suffix(editable_string, "sses", "ss");

  /*  string_copy(editable_string,"Caresses");
  printf("Stem of Caresses is %s\n",get_stem(editable_string));
  string_copy(editable_string,"Tries");
  printf("Stem of Tries is %s\n",get_stem(editable_string));
  string_copy(editable_string,"Caress");
  printf("Stem of Caress is %s\n",get_stem(editable_string));
  string_copy(editable_string,"cats");
  printf("Stem of cats is %s\n",get_stem(editable_string));*/

  // revival->reviv, adoption->adopt, formative->form, relational->relate, controlling->control, rolling->roll

  printf("Testing stemmer----------\n");
  abj::Stemmer stemmer;
  char all_words[10][50] = {"revival","adoption","formative","relational","controlling"};
  for(int i=0; i<5; i++){
    abj::String str(all_words[i]);
    str.print();
    stemmer.initialize(str);
    stemmer.get_stem().print();
  }
}
