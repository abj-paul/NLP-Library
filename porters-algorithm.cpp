
#include "String-Library.cpp"
#include "auxiliary.cpp"
#define VOWEL 1
#define CONSONANT 2
#define PUNCTUATION 3

// Function Prototypes
int* vowel_consonant_count_array(const char* str);
int m_value(const char* str);
bool isConsonant(int i, const char* str);
char capitalize(char c);
bool isPunctuation(char c);
bool regex(const char* condition, const char* str);

bool ends_with(const char* suffix, const char* word);
void replace_suffix(char* word, const char* prev_suffix, const char* new_suffix);
char* get_stem(char* word);
void test_functions(const char* test_string);


int main(){
  test_functions("The skies are crying, I am watching, catching teardrops in my hands.");
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

char capitalize(char c){
  int offset = 'a' - 'A';
  if(c>='a' && c<='z') c=c-offset;
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



bool regex(const char* condition, const char* str){
  int len = string_len(str);
  
  if(is_same_string("*s",condition)){
    if(capitalize(str[string_len(str)-1])=='S'){
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
    if(word[i]!=suffix[j]) return false;
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
    word[i]=new_suffix[j];
  }
  word[i]='\0';

  //  printf("After adding new suffix: %s\n",word);
}

char* get_stem(char* word){
  if(ends_with("sses",word)){ replace_suffix(word, "sses","ss"); return word;}
  else if(ends_with("ies",word)){ replace_suffix(word, "ies","i"); return word;}
  else if(ends_with("ss",word)){ replace_suffix(word, "ss","ss"); return word;}
  else if(ends_with("s",word)){ replace_suffix(word, "s",""); return word;}

  return NULL; // Invalid suffix
}
void test_functions(const char* test_string){
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
  printf("*s : Walkers=%d\n",regex("*s","walkers"));
  printf("*d : Caress=%d\n",regex("*d","Caress"));
  printf("*o : Reganwil=%d\n",regex("*o","Reganwil"));*/

  char editable_string[MAX_WORD_SIZE*2] = "Caresses";

  printf("Caresses ends with %d\n",ends_with("sses",editable_string));
  replace_suffix(editable_string, "sses", "ss");

  string_copy(editable_string,"Caresses");
  printf("Stem of Caresses is %s\n",editable_string,get_stem(editable_string));
  string_copy(editable_string,"Tries");
  printf("Stem of Tries is %s\n",editable_string,get_stem(editable_string));
  string_copy(editable_string,"Caress");
  printf("Stem of Caress is %s\n",editable_string,get_stem(editable_string));
  string_copy(editable_string,"cats");
  printf("Stem of cats is %s\n",editable_string,get_stem(editable_string));

}
