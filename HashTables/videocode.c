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
  int age;

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

//set everything in array to NULL
void clear_hash_array() {
  for(int i = 0; i < ARRAY_SIZE; i++){
    hash_array[i] = NULL;
  }
}

//print the hash array
void print_array() {
  printf("--------------------------------------\n");
  for(int i = 0; i < ARRAY_SIZE; i++){
    if(hash_array[i] == NULL){
      printf("\t%i\t---\n",i+1);
    }
    else{
      printf("\t%i\t%s\n",i+1, hash_array[i]->name);
    }
  }
}

//insert into the hash array
bool hash_insert(person *p){
  if(p == NULL) return false;
  int index = hash(p->name);
  for(int i = 0; i<ARRAY_SIZE; i++){
    int try = (index + i) % ARRAY_SIZE;
    if(hash_array[try] == NULL){
      hash_array[try] = p;
      return true;
    }
  }
  return false;
}

/*
//delete entry in the hash array
person *hash_delete(char *name){
  int index = hash(name);

  for(int i = 0; i<ARRAY_SIZE; i++){
    int try = (index + i) % ARRAY_SIZE;

      if (hash_array[try] != NULL && 
        strncmp(hash_array[try]->name, name, ARRAY_SIZE)==0){
          person *tmp = hash_array[try];
          hash_array[try] = NULL;
          return tmp;
      } else {
        return NULL;
      }

  }

}
*/

//search function by name
person *hash_array_search (char *name){
  int index = hash(name);

  for(int i = 0; i<ARRAY_SIZE; i++){
    int try = (index + i) % ARRAY_SIZE;

    if (hash_array[try] != NULL && 
      strncmp(hash_array[try]->name, name, ARRAY_SIZE)==0){
        return hash_array[try];
    }

  }
  return NULL;
}

int main(void) {

  clear_hash_array();
  
  person fionn = {.name="Fionn", .age=69};
  person mia = {.name="Mia", .age=21};
  person niamh = {.name="Niamh", .age=28};
  person jack = {.name="Jack", .age=23};
  person cora = {.name="Cora", .age=20};

  hash_insert(&fionn);
  hash_insert(&mia);
  hash_insert(&niamh);
  hash_insert(&jack);
  hash_insert(&cora);

  print_array();

  /*printf("Fionn => %u\n",hash("Fionn"));
  printf("Mia => %u\n",hash("Mia"));
  printf("Jack => %u\n",hash("Jack"));
  printf("Niamj => %u\n",hash("Niamh"));
  printf("New2 => %u\n",hash("Cora"));*/

  return 0;
}
