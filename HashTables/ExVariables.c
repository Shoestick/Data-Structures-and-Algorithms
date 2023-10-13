#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 20
#define ARRAY_SIZE 11

//person data
typedef struct {
  
  char name[MAX_STRING_SIZE];
  int frequency;

} person;

//maps key to an index
int hash(char* s){
  int hash = 0;
    while(*s){
      hash = (hash + *s) % ARRAY_SIZE;
      s++;
    }
  return hash;
}

person * hash_array[ARRAY_SIZE];

//INITIALISE everything in array to NULL
void clear_hash_array() {
  for(int i = 0; i < ARRAY_SIZE; i++){
    hash_array[i] = NULL;
  }
}
int collisions = 0;
//PRINT the hash array
void print_array() {
  printf("--------------------------------------\n");
  for(int i = 0; i < ARRAY_SIZE; i++){
    printf("\t%i",i+1);
    if(hash_array[i] == NULL){
      printf("\t---\n");
    }
    else{
      printf("\t%s\t%i\n", hash_array[i]->name, hash_array[i]->frequency);
    }
  }
  printf("\t\tCollisions = %i",collisions);
}


//INSERT into the hash array
bool hash_insert(person *p){
    if(p == NULL) return false;
    int index = hash(p->name);

    if(hash_array[index] == NULL){
            hash_array[index] = p;
            return true;
    }else{
        collisions++;
        for(int i = 1; i<ARRAY_SIZE; i++){
            int try = (index + i) % ARRAY_SIZE;

            if(hash_array[try] == NULL){
                hash_array[try] = p;
                return true;

            }else if(strcmp(hash_array[try]->name, p)==0){
                hash_array[try]->frequency++;
                return true;
            }
        }
    }
    return false;
}

//SEARCH function by name
person *hash_array_search (char *name){
  int index = hash(name);

  for(int i = 0; i<ARRAY_SIZE; i++){
    int try = (index + i) % ARRAY_SIZE;

    if (hash_array[try] != NULL && strcmp(hash_array[try]->name, name)==0){
        return hash_array[try];
    }

  }
  return NULL;
}

int main(void) {

  clear_hash_array();
  
  person fionn = {.name="Fionn", .frequency=69};
  person mia = {.name="Mia", .frequency=21};
  person niamh = {.name="Niamh", .frequency=28};
  person jack = {.name="Jack", .frequency=23};
  person cora = {.name="Cora", .frequency=20};

  hash_insert(&fionn);
  hash_insert(&mia);
  hash_insert(&niamh);
  hash_insert(&jack);
  hash_insert(&cora);

  print_array();

  return 0;
}
