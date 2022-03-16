#include "porters-algorithm.h"

int main(){
  test_functions();
  return 0;
  }


int* vowel_consonant_count_array(const char* str){
  int* vc_array = (int*)calloc(string_len(str), sizeof(int));

  int i=0;
  while(str[i]!='\0'){
    if(isConsonant(i,str)) vc_array[i]=CONSONANT;
    else if(isPunctuation(str[i])) vc_array[i]=PUNCTUATION;
    else vc_array[i]=VOWEL;
    i++;
  }
  return vc_array;
}

int m_value(const char* str){
  int n = string_len(str);
  if(n<=1)return 0;


  int* vowel_consonant_array = vowel_consonant_count_array(str);
  int count_vc=0;
  for(int i=1; i<n; i++){
    if(vowel_consonant_array[i-1]==VOWEL && vowel_consonant_array[i]==CONSONANT) count_vc++;
  }
  free(vowel_consonant_array);
  return count_vc;
}

bool isConsonant(int i, const char* str){
  char c= capitalize(str[i]);
  if(c=='A' || c=='E' || c=='I' || c=='O' || c=='U') return false;
  else if(c=='Y'){
    if(i==0) return true;
    char previous_character = capitalize(str[i-1]);
    if(previous_character=='A' || previous_character=='E' || previous_character=='I' || previous_character=='O' || previous_character=='U') return true;
    else return false;
  }

  if(c>='A' && c<='Z')return true;
  return false; // Punctuations are not consonants
}


char smallize(char c){
  int offset = 'a' - 'A';
  if(c>='A' && c<='Z') c=c+offset;
  return c;

}

bool isPunctuation(char c){
  char all_punctuations[] = "!\"#$%&'()*+,-./:;<=>?@[]^_`{|}~\\";
  //  print_string(all_punctuations);
  int i=0;
  while(all_punctuations[i]!=0){
    if(all_punctuations[i]==c) return true;
    i++;
  }
  return false;
}


bool isCapital(char c){
  if(c<='A' && c>='Z') return true;
  return false;
}

bool regex(const char* condition, const char* str, int index){
  if(capitalize(str[index])==capitalize(condition[1])) return true;
  return false;
}

bool regex(const char* condition, const char* str){
  int len = string_len(str);
  
  if(isCapital(condition[1])){
    if(capitalize(str[string_len(str)-1])==condition[1]){
      return true;
    }else return false;
  }
  else if(is_same_string("*v*",condition)){
    int i=0;
    while(str[i]!='\0'){
      if(!isConsonant(i,str) && !isPunctuation(str[i])) return true;
      i++;
    }
    return false;
  }
  else if(is_same_string("*d",condition)){
    if(len<=1) return false;
    else if(isConsonant(len-1,str) && isConsonant(len-2, str)) return true;
    else return false;
  }
  else if(is_same_string("*o",condition)){

    if(len<=2) return false; 
    else{
      char c= capitalize(str[len-1]);
      if(isConsonant(len-1, str) && c!='W' && c!='Y' && c!='X' && !isConsonant(len-2,str) && !isPunctuation(str[len-2]) && isConsonant(len-3,str)) return true;
      else{
	 return false;
      }
    }
  }
  return false; // Unknown Regex
}


bool ends_with(const char* suffix, const char* word){
  if(string_len(suffix)>string_len(word)){
    return false;
  }

  int n1 = string_len(word);
  int n2 = string_len(suffix);

  for(int i=n1-1, j=n2-1; j>=0; j--,i--){
    if(capitalize(word[i])!=capitalize(suffix[j])) return false;
  }
  return true;
}


void replace_suffix(char* word, const char* prev_suffix, const char* new_suffix){
  // cut -> Add

  int stem_size = string_len(word)-string_len(prev_suffix), len=string_len(word);
  word[stem_size] = '\0';
  //  printf("After trimming Suffix: %s\n",word);
  int i=INT_INITIALIZE_VALUE, j=INT_INITIALIZE_VALUE;

  for(i=stem_size, j=0; i<len && j<string_len(new_suffix); i++, j++){
    word[i]=smallize(new_suffix[j]);
  }
  word[i]='\0';

  //  printf("After adding new suffix: %s\n",word);
}

char* get_stem(char* word){
  // 1a
  if(ends_with("sses",word)) replace_suffix(word, "sses","ss");
  else if(ends_with("ies",word)) replace_suffix(word, "ies","i");
  else if(ends_with("ss",word)) replace_suffix(word, "ss","ss");
  else if(ends_with("s",word)) replace_suffix(word, "s","");

  //1b
  else if(m_value(word)>0 && ends_with("EED",word)) replace_suffix(word, "EED","EE");
  else if(regex("*v*",word) && ends_with("ED",word)) replace_suffix(word, "ED","");
  else if(regex("*v*",word) && ends_with("ING",word)) replace_suffix(word, "ING","");

  // Correction rules
  if(ends_with("AT",word)) replace_suffix(word, "AT","ATE");
  else if(ends_with("BL",word)) replace_suffix(word, "BL","BLE");
  else if(ends_with("IZ",word)) replace_suffix(word, "IZ","IZE");

  //return word;

  // 1C
  if(regex("*v*",word) && ends_with("Y",word)) replace_suffix(word, "Y","I"); 

  // Step 2
  if(m_value(word)>0){
    if(ends_with("ATIONAL",word)) replace_suffix(word, "TIONAL", "TION"); 
    else if(ends_with("TIONAL",word)) replace_suffix(word, "TIONAL", "TION");
    else if(ends_with("ENCI",word)) replace_suffix(word, "ENCI", "ENCE");
    else if(ends_with("ANCI",word)) replace_suffix(word, "ANCI", "ANCE");
    else if(ends_with("IZER",word)) replace_suffix(word, "IZER", "IZE");
    else if(ends_with("ABLI",word)) replace_suffix(word, "ABLI", "ABLE");
    else if(ends_with("ALLI",word)) replace_suffix(word, "ALLI", "AL");
    else if(ends_with("ENTLI",word)) replace_suffix(word, "ENTLI", "ENT");
    else if(ends_with("ELI",word)) replace_suffix(word, "ELI", "E");
    else if(ends_with("OUSLI",word)) replace_suffix(word, "OUSLI", "OUS");
    else if(ends_with("IZATION",word)) replace_suffix(word, "IZATION", "IZE");
    else if(ends_with("ATION",word)) replace_suffix(word, "ATION", "ATE");
    else if(ends_with("ATOR",word)) replace_suffix(word, "ATOR", "ATE");
    else if(ends_with("ALISM",word)) replace_suffix(word, "ALISM", "AL");
    else if(ends_with("IVENESS",word)) replace_suffix(word, "IVENESS", "IVE");
    else if(ends_with("FULNESS",word)) replace_suffix(word, "FULNESS", "FUL");
    else if(ends_with("OUSNESS",word)) replace_suffix(word, "OUSNESS", "OUS");
    else if(ends_with("ALITI",word)) replace_suffix(word, "ALITI", "AL");
    else if(ends_with("IVITI",word)) replace_suffix(word, "IVITI", "IVE");
    else if(ends_with("BILITI",word)) replace_suffix(word, "BILITI", "BLE");
  } 


  // Step 3
  if(m_value(word)>0){
    if(ends_with("ICATE",word))  replace_suffix(word, "ICATE", "IC");
    else if(ends_with("ATIVE",word))  replace_suffix(word, "ATIVE", "");
    else if(ends_with("ALIZE",word))  replace_suffix(word, "ALIZE", "AL");
    else if(ends_with("ICITI",word))  replace_suffix(word, "ICITI", "IC");
    else if(ends_with("ICAL",word))  replace_suffix(word, "ICAL", "IC");
    else if(ends_with("FUL",word))  replace_suffix(word, "FUL", "");
    else if(ends_with("NESS",word))  replace_suffix(word, "NESS", "");
  }

  // Step 4
  if(m_value(word)>1){
    if(ends_with("AL",word))  replace_suffix(word, "AL", "");
    else if(ends_with("ANCE",word))  replace_suffix(word, "ANCE", "");
    else if(ends_with("ENCE",word))  replace_suffix(word, "ENCE", "");
    else if(ends_with("ER",word))  replace_suffix(word, "ER", "");
    else if(ends_with("IC",word))  replace_suffix(word, "IC", "");
    else if(ends_with("ABLE",word))  replace_suffix(word, "ABLE", "");
    else if(ends_with("IBLE",word))  replace_suffix(word, "IBLE", "");
    else if(ends_with("ANT",word))  replace_suffix(word, "ANT", "");
    else if(ends_with("EMENT",word))  replace_suffix(word, "EMENT", "");
    else if(ends_with("MENT",word))  replace_suffix(word, "MENT", "");
    else if(ends_with("ENT",word))  replace_suffix(word, "ENT", "");
    
    else if((regex("*S",word,string_len(word)-1-3) || regex("*T",word,string_len(word)-1-3) ) && ends_with("ION",word))  replace_suffix(word, "ION", "");
    else if(ends_with("OU",word))  replace_suffix(word, "OU", "");
    else if(ends_with("ISM",word))  replace_suffix(word, "ISM", "");
    else if(ends_with("ATE",word))  replace_suffix(word, "ATE", "");
    else if(ends_with("ITI",word))  replace_suffix(word, "ITI", "");
    else if(ends_with("OUS",word))  replace_suffix(word, "OUS", "");
    else if(ends_with("IVE",word))  replace_suffix(word, "IVE", "");
    else if(ends_with("IZE",word))  replace_suffix(word, "IZE", "");


    // Step 5a
    if(m_value(word)>1 && ends_with("E",word))  replace_suffix(word, "E", "");
    else if(m_value(word)==1 && !regex("*o",word) && ends_with("E",word))  replace_suffix(word, "E", "");

    // Step 5b
    if(m_value(word)>1 && regex("*d",word) && regex("*L",word, string_len(word)-1)) replace_suffix(word, "L","");
  }
  
  return word;
}
void test_functions(){
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

  char editable_string[MAX_WORD_SIZE*2] = "Caresses";

  printf("Caresses ends with %d\n",ends_with("sses",editable_string));
  replace_suffix(editable_string, "sses", "ss");

  /*  string_copy(editable_string,"Caresses");
  printf("Stem of Caresses is %s\n",get_stem(editable_string));
  string_copy(editable_string,"Tries");
  printf("Stem of Tries is %s\n",get_stem(editable_string));
  string_copy(editable_string,"Caress");
  printf("Stem of Caress is %s\n",get_stem(editable_string));
  string_copy(editable_string,"cats");
  printf("Stem of cats is %s\n",get_stem(editable_string));*/

  // revival->reviv, adoption->adopt, formative->form, relational->relate, controlling->control, rolling->roll
  char all_words[10][50] = {"revival","adoption","formative","relational","controlling"};
  for(int i=0; i<5; i++){
    string_copy(editable_string,all_words[i]);
    printf("Stem of %s is ",editable_string);
    printf("%s\n",get_stem(editable_string));
  }

}
