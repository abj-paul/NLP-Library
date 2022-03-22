#include "Stemmer.h"

abj::Stemmer::Stemmer(){
  //Do nothing
  //this->word=NULL;
  this->m_value=0;
}

void abj::Stemmer::initialize(abj::String word){
  this->word.initialize(word);
  this->build_vowel_consonant_array();
  this->m_value = calculate_m_value();
}

abj::Stemmer::Stemmer(abj::String& word){
  this->word.initialize(word);
  this->build_vowel_consonant_array();
  this->m_value = calculate_m_value();
}

void abj::Stemmer::build_vowel_consonant_array(){
  for(int i=0; i<this->word.size(); i++){
    if(isConsonant(i)) this->vowel_consonant_array.push(CONSONANT);
    else if(isPunctuation(this->word.get(i))) this->vowel_consonant_array.push(PUNCTUATION);
    else this->vowel_consonant_array.push(VOWEL);
  }
}

int abj::Stemmer::calculate_m_value(){
  int vc_count=0;
  for(int i=1; i<this->word.size(); i++){
    if(this->vowel_consonant_array.get(i-1)==VOWEL && this->vowel_consonant_array.get(i)==CONSONANT)
      vc_count++;
  }
  return vc_count;
}


bool abj::Stemmer::isConsonant(int index){
  char c = this->capitalize(this->word.get(index));
  if(c=='A' || c=='E' || c=='I' || c=='O' || c=='U') return false;
  else if(c=='Y'){
    if(index==0) return true;
    char previous_character = this->capitalize(this->word.get(index-1));
    if(previous_character=='A' || previous_character=='E' || previous_character=='I' || previous_character=='O' || previous_character=='U') return true;
    else return false;
  }
  if(c>='A' && c<='Z')return true;
  return false; // Punctuations are not consonants
}

bool abj::Stemmer::isPunctuation(char c){
  if(c>='!' && c<='/') return true;
  if(c>=':' && c<='@') return true;
  return false;
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

bool abj::Stemmer::isCapital(char c){
  if(c<='A' && c>='Z') return true;
  return false;
}

// Main Functions Start Here
bool abj::Stemmer::regex(const char* c){
  abj::String condition(c);
  
  if(this->isCapital(condition.get(1))){
    if(this->capitalize(word.lastChar())==condition.get(1)) return true;
    else return false;
  }

  else if(condition.equals("*v*")){
    for(int i=0; i<this->word.size(); i++){
      if(!isConsonant(i) && !isPunctuation(this->word.get(i))) return true;
    }
    return false;
  }

  else if(condition.equals("*d")){
    if(this->word.size()<=1) return false;
    else if(this->isConsonant(this->word.size()-1) && isConsonant(this->word.size()-2)) return true;
    else return false;
  }

  else if(condition.equals("*o")){
    if(this->word.size()<=2) return false;

    char c = capitalize(this->word.lastChar());
    int len = this->word.size();
    // CVC
    if(isConsonant(len-1) && c!='W' && c!= 'Y' && c!='X' && !isConsonant(len-2) && !isPunctuation(this->word.get(len-2)) && isConsonant(len-3)) return true;
    else return false;
  }
  return false; // NO known command
}

bool abj::Stemmer::regex(const char* condition, int index){ // Special Case
  if(capitalize(this->word.get(index))==capitalize(condition[1])) return true;
  return false;
}

bool abj::Stemmer::ends_with(const char* s){
  abj::String suffix(s);

  if(suffix.size() >= this->word.size()) return false;

  int i,j;
  for(i=word.size()-1, j=suffix.size()-1; i>=0 && j>=0; i--,j--){
    if(capitalize(word.get(i))!=capitalize(suffix.get(j)))  return false;
  }
  return true;
}
void abj::Stemmer::replace_suffix(const char* ps, const char* ns){
  abj::String prev_suffix(ps);
  abj::String new_suffix(ns);
  
  int stem_size = std::abs(this->word.size()-prev_suffix.size());

  int i=stem_size,j=0;
  for(i=stem_size,j=0; i<this->word.size() && j<new_suffix.size(); i++, j++){
    this->word.set(i,this->smallize(new_suffix.get(j)));
  }
  this->word.set(i,'\0'); // String size is automatically updated when String class encounters SET NULL
}

abj::String abj::Stemmer::get_stem(){
  // 1a
  if(ends_with("sses")) replace_suffix("sses","ss");
  else if(ends_with("ies")) replace_suffix("ies","i");
  else if(ends_with("ss")) replace_suffix("ss","ss");
  else if(ends_with("s")) replace_suffix("s","");

  //1b
  else if(this->m_value>0 && ends_with("EED")) replace_suffix("EED","EE");
  else if(regex("*v*") && ends_with("ED")) replace_suffix("ED","");
 else if(regex("*v*") && ends_with("ING")) replace_suffix("ING","");

  // Correction rules
  if(ends_with("AT")) replace_suffix("AT","ATE");
  else if(ends_with("BL")) replace_suffix("BL","BLE");
  else if(ends_with("IZ")) replace_suffix("IZ","IZE");

  //return word;

  // 1C
  if(regex("*v*") && ends_with("Y")) replace_suffix("Y","I"); 

  // Step 2
  if(this->m_value>0){
    if(ends_with("ATIONAL")) replace_suffix("TIONAL", "TION"); 
    else if(ends_with("TIONAL")) replace_suffix("TIONAL", "TION");
    else if(ends_with("ENCI")) replace_suffix("ENCI", "ENCE");
    else if(ends_with("ANCI")) replace_suffix("ANCI", "ANCE");
    else if(ends_with("IZER")) replace_suffix("IZER", "IZE");
    else if(ends_with("ABLI")) replace_suffix("ABLI", "ABLE");
    else if(ends_with("ALLI")) replace_suffix("ALLI", "AL");
    else if(ends_with("ENTLI")) replace_suffix("ENTLI", "ENT");
    else if(ends_with("ELI")) replace_suffix("ELI", "E");
    else if(ends_with("OUSLI")) replace_suffix("OUSLI", "OUS");
    else if(ends_with("IZATION")) replace_suffix("IZATION", "IZE");
    else if(ends_with("ATION")) replace_suffix("ATION", "ATE");
    else if(ends_with("ATOR")) replace_suffix("ATOR", "ATE");
    else if(ends_with("ALISM")) replace_suffix("ALISM", "AL");
    else if(ends_with("IVENESS")) replace_suffix("IVENESS", "IVE");
    else if(ends_with("FULNESS")) replace_suffix("FULNESS", "FUL");
    else if(ends_with("OUSNESS")) replace_suffix("OUSNESS", "OUS");
    else if(ends_with("ALITI")) replace_suffix("ALITI", "AL");
    else if(ends_with("IVITI")) replace_suffix("IVITI", "IVE");
    else if(ends_with("BILITI")) replace_suffix("BILITI", "BLE");
  } 


  // Step 3
  if(this->m_value>0){
    if(ends_with("ICATE"))  replace_suffix("ICATE", "IC");
    else if(ends_with("ATIVE"))  replace_suffix("ATIVE", "");
    else if(ends_with("ALIZE"))  replace_suffix("ALIZE", "AL");
    else if(ends_with("ICITI"))  replace_suffix("ICITI", "IC");
    else if(ends_with("ICAL"))  replace_suffix("ICAL", "IC");
    else if(ends_with("FUL"))  replace_suffix("FUL", "");
    else if(ends_with("NESS"))  replace_suffix("NESS", "");
  }

  // Step 4
  if(this->m_value>1){
    if(ends_with("AL"))  replace_suffix("AL", "");
    else if(ends_with("ANCE"))  replace_suffix("ANCE", "");
    else if(ends_with("ENCE"))  replace_suffix("ENCE", "");
    else if(ends_with("ER"))  replace_suffix("ER", "");
    else if(ends_with("IC"))  replace_suffix("IC", "");
    else if(ends_with("ABLE"))  replace_suffix("ABLE", "");
    else if(ends_with("IBLE"))  replace_suffix("IBLE", "");
    else if(ends_with("ANT"))  replace_suffix("ANT", "");
    else if(ends_with("EMENT"))  replace_suffix("EMENT", "");
    else if(ends_with("MENT"))  replace_suffix("MENT", "");
    else if(ends_with("ENT"))  replace_suffix("ENT", "");
    
    else if((regex("*S",word.size()-1-3) || regex("*T",word.size()-1-3) ) && ends_with("ION"))  replace_suffix("ION", "");
    else if(ends_with("OU"))  replace_suffix("OU", "");
    else if(ends_with("ISM"))  replace_suffix("ISM", "");
    else if(ends_with("ATE"))  replace_suffix("ATE", "");
    else if(ends_with("ITI"))  replace_suffix("ITI", "");
    else if(ends_with("OUS"))  replace_suffix("OUS", "");
    else if(ends_with("IVE"))  replace_suffix("IVE", "");
    else if(ends_with("IZE"))  replace_suffix("IZE", "");


    // Step 5a
    if(this->m_value>1 && ends_with("E"))  replace_suffix("E", "");
    else if(this->m_value==1 && !regex("*o") && ends_with("E"))  replace_suffix("E", "");

    // Step 5b
    if(this->m_value>1 && regex("*d") && regex("*L", word.size()-1)) replace_suffix("L","");
  }
  
  return word;
}


void abj::Stemmer::test_function(){
  char all_words[10][50] = {"revival","adoption","formative","relational","controlling"};
  for(int i=0; i<5; i++){
    abj::String str(all_words[i]);
    str.print();
    abj::Stemmer stemmer(str);
    stemmer.get_stem().print();
  }
}
