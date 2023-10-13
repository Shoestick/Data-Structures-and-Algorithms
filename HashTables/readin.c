#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_STRING_SIZE 20
#define ARRAY_SIZE 59

//person data
typedef struct {
  
  char name[MAX_STRING_SIZE];
  int frequency;

} person;

person * hash_array[ARRAY_SIZE];

//-----------------------------------------------------------------------------------------------------------------
//maps key to an index
int hash(char* s){
  int hash = 0;
    while(*s){
      hash = (hash + *s) % ARRAY_SIZE;
      s++;
    }
  return hash;
}

//set everything in array to NULL
void clear_hash_array() {
  for(int i = 0; i < ARRAY_SIZE; i++){
    hash_array[i] = NULL;
  }
}

person* createNewPerson(char* name){
    // TODO
    // you might want to use the function strcpy from the string package here!
    person* new = malloc(sizeof(new));
    strcpy(new->name, name);
    new->frequency = 1;
    return new;
}

int collisions = 0;
//INSERT into the hash array
bool hash_insert(char* name){

    person* newname = createNewPerson(name);

    int index = hash(newname->name);

    if(hash_array[index] == NULL) {
        hash_array[index] = newname;
        return true;
    }
    else{
        collisions++;
        for(int i = 1; i < ARRAY_SIZE; i++){
            int try = index + i;
            if(hash_array[try] != NULL){
                hash_array[try] = newname;
                return true;
            }
        }
    }
    return false;
}

//INSERT into the hash array
/*bool insert(char name){
    person* temp = malloc(sizeof(temp));
    temp->name = name;
    int index = hash(temp->name);

    if(hash_array[index] == NULL){
        person* new = malloc(sizeof(new));
        name = new->name;
        new->frequency = 1;
        return true;
    }else{
        collisions++;
        for(int i = 1; i<ARRAY_SIZE; i++){
            int try = (index + i) % ARRAY_SIZE;

            if(hash_array[try] == NULL){
                person* new = malloc(sizeof(new));
                name = new->name;
                new->frequency = 1;
                return true;
            }
        }
    }
}*/

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

//-----------------------------------------------------------------------------------------------------------------
//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(char* name){

    //has to be a neater way to do this
    if(hash_array_search(name) != NULL) {
        int index = hash(name);

        for(int i = 0; i<ARRAY_SIZE; i++){
            int try = (index + i) % ARRAY_SIZE;

        if (hash_array[try] != NULL && strcmp(hash_array[try]->name, name)==0){
            hash_array[try]->frequency++;
    }

  }
    }
    else hash_insert(name); 

}

// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token ( char *buf, FILE *f, int string_max ) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( !isalnum(buf[i]) ) { break; } // only load letters and numbers
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}


//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
bool load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return false; 
	}
	
	// read until the end of the file
	while ( !feof(f) ) {
		next_token(buf, f, MAX_STRING_SIZE);
        addOrIncrement( buf);                           //here you call your function from above!
	}

	// always remember to close your file stream
	fclose(f);
    
    printf("%s loaded!", *f);
	return true;
}
//-----------------------------------------------------------------------------------------------------------------
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

int main()  {
    
    clear_hash_array();
    load_file ("names.csv");
    print_array();
    
    return 0;
}
