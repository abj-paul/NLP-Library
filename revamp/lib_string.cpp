#include "lib_string.h"

abj::String::String(){
	this->curr_size=0;
	this->storage=NULL;
}

abj::String::String(abj::String& data){ // RISKY!!!! because both data and "this" can access this heap data. Thus, without us knowing, data functions can change the heap data.
	this->storage = (char*)calloc(data.size()+1,sizeof(char));

	char* temp = data.get_raw_data();
	for(int i=0; i<data.size(); i++) this->storage[i]=data.get(i);
	this->storage[data.size()]='\0';

	this->curr_size = data.size();
}

abj::String::String(const char* data){
	// Getting String Size
	int size = 0;
	while(data[size]!='\0') size++;

	this->storage = (char*)calloc(size+1,sizeof(char));

	for(int i=0; i<size; i++) this->storage[i]=data[i];
	this->storage[size]='\0';

	this->curr_size=size;
}

abj::String::String(char* data, int FLAG){
	int size=0;
	while(data[size]!='\0') size++;

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
	char* new_memory = (char*)calloc(size+2,sizeof(char));
	for(int i=0; i<this->curr_size; i++) new_memory[i]=this->storage[i];
	free(this->storage);

	this->storage = new_memory;
	this->curr_size = size;

}

void abj::String::concatenate_at_end(abj::String str, char separator){
	// Getting String Size
	int str_size=0;
	while(str.get(str_size)!='\0') str_size++;

	int old_size = this->curr_size;
	this->resize(this->curr_size+str_size);

	this->storage[old_size]=separator;

	int j=0;
	for(int i=old_size+1; j<str.size(); i++, j++)this->storage[i]=str.get(j);
	this->storage[old_size+str_size]='\0';
}

bool abj::String::equals(String data){
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
void abj::String::concatenate_at_point(abj::String str, int index, char separator){
// resize, copy+separator+new_data+copy
	int old_size = this->curr_size;
	resize(this->curr_size+str.size());
	this->storage[old_size] = separator;

	int j=0;
	for(int i=old_size+1; j<str.size(); i++, j++) this->storage[i]=str.get(j);
	this->storage[old_size+str.size()]='\0';
}

char abj::String::get(int index){
    return this->storage[index];
}

void abj::String::test_function(){
	abj::String x("I am Abhijit Paul.");
	x.capitalize();
	x.print();

	abj::String y(x);
	y.capitalize();
	printf("x==y? %d\n",y.equals(x));

	char str[] = "New Word.";
	abj::String z(str);
	z.print();

	x.concatenate_at_end(z, '-');
	x.print();

	y.concatenate_at_point(z, y.size(), '_');
	y.print();
}

/*int main(){
	abj::String x;
	x.test_function();
	return 0;
}*/
