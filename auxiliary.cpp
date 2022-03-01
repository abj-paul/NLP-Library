#define INT_INITIALIZE_VALUE 0
#define MAX_SIZE 100

void print_array(int *x, int size){
  for(int i=0; i<size; i++) printf("%d ", x[i]);
  printf("\n");
}
void print_array(char *x, int size){
  for(int i=0; i<size; i++) printf("%c ", x[i]);
  printf("\n");
}
