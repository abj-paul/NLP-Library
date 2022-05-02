#include "lib_string.h"

abj::String::String(){
  this->curr_size=0;
  this->storage=NULL;
}

abj::String::~String(){
  if(this->storage!=NULL && this->curr_size!=0){
      free(this->storage);
      this->storage=NULL;
      this->curr_size=0;
    }
}

abj::String::String(std::string str){
  int size = str.size();
  
  this->storage = (char*)calloc(size+1,sizeof(char));

  for(int i=0; i<size; i++) this->storage[i]=str[i];
  this->storage[size]='\0';

  this->curr_size=size;
}


abj::String::String(abj::String& data){ 
  this->storage = (char*)calloc(data.size()+1,sizeof(char));
  
  for(int i=0; i<data.size(); i++) this->storage[i]=data.get(i);
  this->storage[data.size()]='\0';

  this->curr_size = data.size();
}

abj::String::String(const char* data){
  int size = 0;
  while(data[size]!='\0') size++;
  //size--; // because it incremented extra-one-time at the end.

  this->storage = (char*)calloc(size+1,sizeof(char));
  for(int i=0; i<size; i++) this->storage[i]=data[i];
  this->storage[size]='\0';

  this->curr_size=size;
}

abj::String::String(char* data, int FLAG){
  int size=0;
  while(data[size]!='\0') size++;
  //size--;

  if(FLAG==USE_OLD_MEMORY){
    this->curr_size = size;
    this->storage = data;
  }else if(FLAG==ALLOCATE_NEW_MEMORY){
    this->storage = (char*)calloc(size+1, sizeof(char));
    for(int i=0; i<size; i++) this->storage[i]=data[i];
    this->storage[size]='\0';
    
    this->curr_size=size;
    
  }

  else{
    printf("Unrecognized command! Initializing with NULL.\n");
    this->storage=NULL;
    this->curr_size=0;
  }
}


int abj::String::size(){
  return this->curr_size;
}

void abj::String::print(){
  printf("%s\n",this->storage);
}

char abj::String::capitalize(char c){
	int offset = 'a'-'A';
	if(c>='a' && c<='z') c=c-offset;
	return c;
}

void abj::String::capitalize(){
	for(int i=0; i<this->curr_size; i++) this->storage[i]=capitalize(this->storage[i]);
}

char* abj::String::get_raw_data(){
  char* temp = (char*)calloc(this->curr_size+1, sizeof(char));

  for(int i=0; i<this->curr_size; i++) temp[i] = this->storage[i];
  temp[this->curr_size]='\0';
  
  return temp;
}

abj::String abj::String::copy(){
  String t(*this);
  return t;
}

void abj::String::resize(int size){
  size = std::max(size,this->curr_size+1);
  char* new_memory = (char*)calloc(size,sizeof(char));
  for(int i=0; i<this->curr_size; i++) new_memory[i]=this->storage[i];
  new_memory[this->curr_size]='\0';
  free(this->storage);
  this->storage=NULL;

  this->storage = new_memory;
  // this->curr_size = this->curr_size;
}

void abj::String::concatenate_at_end(abj::String& data, char separator){
  // Getting String Size
  int old_size = this->curr_size;
  this->resize(this->curr_size+data.size());
  
  this->storage[old_size]=separator;
  
  int j=0;
  for(int i=old_size+1; j<data.size(); i++, j++)this->storage[i]=data[j];

  this->curr_size = old_size+data.size()+1; //+1 for separator
  this->storage[old_size+data.size()+1]='\0';
}

void abj::String::concatenate_at_end(abj::String& data){
  // Getting String Size
  int old_size = this->curr_size;
  this->resize(this->curr_size+data.size());
  
  int j=0;
  for(int i=old_size; j<data.size(); i++, j++)this->storage[i]=data[j];

  this->curr_size = old_size+data.size(); 
  this->storage[old_size+data.size()+1]='\0';
}


bool abj::String::equals(abj::String& data){
  if(data.size()!=this->curr_size) return false;

  for(int i=0; i<data.size(); i++){
    if(data.get(i)!=this->storage[i]) return false;
  }
  return true;
}

bool abj::String::equals(const char* data){
  int data_size=0;
  while(data[data_size]!='\0') data_size++;
  // data_size--;
  
  if(data_size!=this->curr_size) return false;

  for(int i=0; i<data_size; i++){
    if(data[i]!=this->storage[i]) return false;
  }
  return true;
}


// How it works
// f("abhi paul", "jit', " ") = abhi  jit paul
// f("abhi paul", "jit', "") = abhi jit paul
// f("abhi paul", "jit', "-") = abhi -jit paul
void abj::String::concatenate_at_point(abj::String& data, int index, char separator){
  this->insert_char_at_point(index,separator);
  for(int i=1; i<=data.size(); i++) this->insert_char_at_point(index+i, data[i-1]);
}
void abj::String::concatenate_at_point(abj::String& data, int index){
  for(int i=0; i<data.size(); i++) this->insert_char_at_point(index+i, data[i]);
}


char abj::String::get(int index){
  if(this->curr_size==0){
    printf("Trying to access NULL string!\n");
    return (char)NULL;
  }
  if(index<0 || index>=this->curr_size){
    printf("String Index out of bound! (%s,%d)\n",this->storage, index);
    return (char)NULL;
    //exit(1);
  } 
  return this->storage[index];
}


void abj::String::initialize(abj::String& data){
  this->storage = (char*)calloc(data.size()+1,sizeof(char));

  for(int i=0; i<data.size(); i++) this->storage[i]=data.get(i);
  this->storage[data.size()]='\0';
  
  this->curr_size = data.size();
}

void abj::String::initialize(char* data){
  int size = 0;
  while(data[size]!='\0') size++;
  //size--;
  
  this->storage = (char*)calloc(size+1,sizeof(char));
  
  for(int i=0; i<size; i++) this->storage[i]=data[i];
  this->storage[size]='\0';
  
  this->curr_size=size;
}

void abj::String::initialize(const char* data){
  int size = 0;
  while(data[size]!='\0') size++;
  //size--;
  
  this->storage = (char*)calloc(size+1,sizeof(char));
  
  for(int i=0; i<size; i++) this->storage[i]=data[i];
  this->storage[size]='\0';
  
  this->curr_size=size;
}


void abj::String::removeData(){
  this->curr_size=0;
  free(this->storage);
  this->storage=NULL;
}

//0123
//abhjit,3 -> abhijit
void abj::String::insert_char_at_point(int index, char data){
  resize(this->curr_size+2); //+1 for null, +! for new character
  this->curr_size++;

  char oldCharacter = this->storage[index];
  this->storage[index] = data;

  for(int i=index+1; i<this->curr_size; i++){
    //swap
    char temp = oldCharacter;
    oldCharacter = this->storage[i];
    this->storage[i] = temp;
  }
}


char abj::String::lastChar(){
  return this->storage[this->curr_size-1];
}


bool abj::String::set(int index, char data){
  if(index>=this->curr_size){ printf("Can't set(%d,%c). String index out of bound.\n",index,data); return false; };
  if(data=='\0') this->curr_size=index;
  this->storage[index]=data;
  return true;
}

char abj::String::operator[](int index){
  if(index<0 || index>=this->curr_size){
    printf("String index out of bound!\n");
    return (char)NULL;
  }
  return this->storage[index];
}


abj::String abj::String::operator+(abj::String data){
  char* new_data = (char*)calloc(this->curr_size+data.size()+1, sizeof(char)); //+1 for NULL
  for(int i=0; i<this->curr_size; i++) new_data[i]=this->storage[i];

  int j=0;
  for(int i=this->curr_size; j<data.size(); i++, j++) new_data[i]=data[j];
  new_data[this->curr_size+data.size()]='\0'; //5,4 -> 0-4, 5,6,7,8

  abj::String s(new_data);
  return s;
}

bool abj::String::operator==(abj::String data){
  if(data.size()!=this->curr_size) return false;

  for(int i=0; i<data.size(); i++){
    if(capitalize(data[i])!=capitalize(this->storage[i])) return false;
  }
  return true;
}

abj::String& abj::String::operator=(abj::String data){
  this->removeData();
  this->initialize(data);
  return *this;
}

int abj::String::compare_string(char *str1, char *str2){
  while( ( *str1 != '\0' && *str2 != '\0' ) && capitalize(*str1) == capitalize(*str2) ){
        str1++;
        str2++;
    }

    if(*str1 == *str2) return 0; // strings are identical or found null for both
    else return capitalize(*str1) - capitalize(*str2);
}
bool abj::String::operator>(abj::String data){
  if(this->compare_string(this->storage, data.get_raw_data()) > 0) return true;
  return false;
}
bool abj::String::operator<(abj::String data){
  if(this->compare_string(this->storage, data.get_raw_data()) < 0) return true;
  return false;
}


void abj::String::test_function(){
printf("Testing String----------------\n");
	abj::String x("I am Abhijit Paul.");
	x.capitalize();
	x.print();

	abj::String y("I am only human~");
        y.capitalize();
	printf("x==y? %d\n",y.equals(x));

	char str[] = "New Word.";
	abj::String z(str);
	z.print();

	x.concatenate_at_end(z, ':');
	x.print();

	y.concatenate_at_point(z, y.size(), '_');
	y.print();

	abj::String t;
	t.concatenate_at_end(x, '_');
	t.print();

	t.insert_char_at_point(t.size()-2, '!');
	t.insert_char_at_point(t.size()-3, '~');
	t.print();

	printf("New test cases.\n");

	abj::Vector<abj::String>v;
	for(int i=0; i<10000; i++){
	  abj::String* newString = new abj::String("Random data is being loaded!");
	  v.push(*newString);
	}

	for(int i=0; i<v.size(); i++) v[i].~String();

	abj::String* data1 = new abj::String();
	data1->initialize("Data one.");
	data1->print();
	abj::String* data2 = new abj::String(*data1);
	data2->concatenate_at_point(*new abj::String("Stuff1"),4,'_');
	data2->print();
	data2->concatenate_at_end(*new abj::String("I am only human~"), '.');
	data2->print();
	abj::String* data3 = new abj::String("Eat");
	data3->print();
	data3->concatenate_at_end(*new abj::String("ing."));
	data3->print();
	abj::String name("AbhiPaul");
	name.concatenate_at_point(*new abj::String("jit "),4);
	name.print();

	printf("Raw data=%sEND\n",name.get_raw_data());
	abj::String name2("Abhijit Paul");
	printf("Equal?%d\n",name.equals(name2));
	printf("Equal?%d\n",name==name2);

	abj::String firstPart("Rubik's");
	abj::String lastPart("Cube is fun!");
	abj::String answer;
	answer = firstPart + *new abj::String(" ") + lastPart;
	answer.capitalize();
	answer.print();
}

int main(){
  abj::String::test_function();
  return 0;
}
