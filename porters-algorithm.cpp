

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
  int size = string_len(all_punctuations), i=0;
  while(all_punctuations[i]!=0){
    if(all_punctuations[i]==c) return true;
    i++;
  }
  return false;
}


void test_functions(const char* test_string){
  printf("X is punction? %d\n",isPunctuation('x'));
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
  free(x);

  printf("m-value of TREE = %d\n",m_value("TREE"));
  printf("m-value of BY = %d\n",m_value("BY"));
  printf("m-value of OATS = %d\n",m_value("OATS"));
  printf("m-value of TREES = %d\n",m_value("trees"));
  printf("m-value of IVY = %d\n",m_value("ivy"));
  printf("m-value of TROUBLE = %d\n",m_value("trouble"));
  printf("m-value of TROUBLES = %d\n",m_value("troubles"));
  printf("m-value of OATEN = %d\n",m_value("oaten"));
  printf("m-value of PRIVATE = %d\n",m_value("private"));
}

