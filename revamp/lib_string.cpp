#include "lib_string.h"

abj::String::String(){
	this->curr_size=0;
	this->curr_capacity=0;
	this->storage=NULL;
}

abj::String::String(abj::String& data){ // RISKY!!!! because both data and "this" can access this heap data. Thus, without us knowing, data functions can change the heap data.
	this->storage = (char*)calloc(data.size()+1,sizeof(char));

	char* temp = data.get_raw_data();
	for(int i=0; i<data.size(); i++) this->storage[i]=data.get(i);
	this->storage[data.size()]='\0';

	this->curr_size = data.size();
	this->curr_capacity= data.capacity();
}

abj::String::String(const char* data){
	// Getting String Size
	int size = 0;
	while(data[size]!='\0') size++;

	this->storage = (char*)calloc(size+1,sizeof(char));

	for(int i=0; i<size; i++) this->storage[i]=data[i];
	this->storage[size]='\0';

	this->curr_size=size;
	this->curr_capacity=size;
}

abj::String::String(char* data, int FLAG){
	int size=0;
	while(data[size]!='\0') size++;

	if(FLAG==USE_OLD_MEMORY){
		this->curr_size = size;
		this->storage = data;
		this->curr_capacity=size;
	}else if(FLAG==ALLOCATE_NEW_MEMORY){
		this->storage = (char*)calloc(size+1, sizeof(char));
		for(int i=0; i<size; i++) this->storage[i]=data[i];
		this->storage[size]='\0';

		this->curr_size=size;
		this->curr_capacity=size;

	}
	else{
		printf("Unrecognized command! Initializing with NULL.\n");
		this->storage=NULL;
		this->curr_size=0;
		this->curr_capacity=0;
	}
}


int abj::String::size(){
	return this->curr_size;
}

int abj::String::capacity(){
  return this->curr_capacity;
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

	for(int i=0; i<this->curr_size; i++){
		temp[i]	= this->storage[i];
	}
	temp[this->curr_size]='\0';

	return temp;
}

abj::String abj::String::copy(){
	String t(*this);
	return t;
}

void abj::String::resize(int size){
        int new_size = std::max(this->curr_capacity*2, size);
        char* new_memory = (char*)calloc(new_size,sizeof(char));
	for(int i=0; i<this->curr_size; i++) new_memory[i]=this->storage[i];
	free(this->storage);

	this->storage = new_memory;
	this->curr_size = this->curr_size;
	this->curr_capacity=new_size;

}

void abj::String::concatenate_at_end(abj::String& str, char separator){
	// Getting String Size
	int str_size=0;
	while(str.get(str_size)!='\0') str_size++;

	int old_size = this->curr_size;
	this->resize(this->curr_size+str_size);

	this->storage[old_size]=separator;

	int j=0;
	for(int i=old_size+1; j<str.size(); i++, j++)this->storage[i]=str.get(j);
	if(old_size==0){
	  this->curr_size = old_size+str_size+1;
	  this->storage[old_size+str_size+1]='\0';
	}
	else{
	  this->curr_size = old_size+str_size;
	  this->storage[old_size+str_size]='\0';
	}
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
void abj::String::concatenate_at_point(abj::String& str, int index, char separator){
// resize, copy+separator+new_data+copy
	int old_size = this->curr_size;
	resize(this->curr_size+str.size());
	this->storage[old_size] = separator;

	int j=0;
	for(int i=old_size+1; j<str.size(); i++, j++) this->storage[i]=str.get(j);
	this->storage[old_size+str.size()]='\0';
	this->curr_size = old_size+str.size();
}

int abj::String::get(int index){
  if(index>this->curr_size) return -1;
    return this->storage[index];
}


void abj::String::initialize(abj::String& data){ // RISKY!!!! because both data and "this" can access this heap data. Thus, without us knowing, data functions can change the heap data.
	this->storage = (char*)calloc(data.size()+1,sizeof(char));

	char* temp = data.get_raw_data();
	for(int i=0; i<data.size(); i++) this->storage[i]=data.get(i);
	this->storage[data.size()]='\0';

	this->curr_size = data.size();
	this->curr_capacity = data.capacity();
}

void abj::String::initialize(char* data){
	// Getting String Size
	int size = 0;
	while(data[size]!='\0') size++;

	this->storage = (char*)calloc(size+1,sizeof(char));

	for(int i=0; i<size; i++) this->storage[i]=data[i];
	this->storage[size]='\0';

	this->curr_size=size;
	this->curr_capacity=size;
}


void abj::String::removeData(){
  this->storage=NULL;
  this->curr_size=0;
  this->curr_capacity=0;
  free(this->storage);
}


void abj::String::insert_char_at_point(int index, char c){
  if(this->curr_capacity<=this->curr_size+1) resize(this->curr_size+1);

  char temp;
  char prev_char = this->storage[index];
  this->storage[index]=c;
  for(int i=index+1; i<=this->curr_size; i++) {
    temp = this->storage[i];
    this->storage[i]=prev_char;
    prev_char = temp;
  }

  this->curr_size = this->curr_size+1;
  
}


char abj::String::lastChar(){
  return this->storage[this->curr_size-1];
}


bool abj::String::set(int index, char c){
  if(index>=this->curr_size){
    //printf("String Set error! Unable to set(%d) as string size is lesser(%d).\n",index,this->curr_size);

    this->resize(index+5);
    this->storage[index]=c;
    return true;
  }
  if(c=='\0') this->curr_size=index;
  this->storage[index]=c;
  return true;
}

void abj::String::test_function(){
printf("Testing String----------------\n");
	abj::String x("I am Abhijit Paul.");
	x.capitalize();
	x.print();

	abj::String y(x);
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
}

/*int main(){
	abj::String x;
	x.test_function();
	return 0;
}*/
