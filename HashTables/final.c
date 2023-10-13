#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

//////////INITIALISE//////////INITIALISE//////////INITIALISE//////////INITIALISE//////////

#define MAX_STRING_SIZE 20
#define ARRAY_SIZE 59

typedef struct Element Element;
struct Element{
    char name[MAX_STRING_SIZE];
    int freq;

};

Element* hashTable[ARRAY_SIZE]; 

void clear_array(){
    for(int i = 0; i < ARRAY_SIZE; i++){
        hashTable[i] = NULL;
    }
}

//////////HASH//////////HASH//////////HASH//////////HASH//////////HASH//////////HASH//////////HASH//////////

int hash(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s) % ARRAY_SIZE;
        s++;
    }

    return hash;
}

//////////SEARCH//////////SEARCH//////////SEARCH//////////SEARCH//////////SEARCH//////////SEARCH//////////

bool find(char* name){
    int index = hash(name);

    for(int i = 0; i < ARRAY_SIZE; i++){
        int try = (i + index) % ARRAY_SIZE;
        if(hashTable[i] != NULL && strncmp(hashTable[i]->name, name, ARRAY_SIZE)==0){
            return true;
        }
    }
    return false;
}

//////////INSERT//////////INSERT//////////INSERT//////////INSERT//////////INSERT//////////INSERT//////////

Element* createNewElement(char* name){
    Element* new = (Element*)malloc(sizeof(Element));
    strcpy(new->name, name);
    new->freq = 1;

    return new;
}

int num_terms = 0;
int collisions = 0;

bool insert(char* name){
    num_terms++;
    int index = hash(name);
    Element* new = createNewElement(name);

    if(hashTable[index] == NULL){
        hashTable[index] = new;
        return true;
    }
    else{
        for(int i = 1; i < ARRAY_SIZE; i++){
            collisions++;
            int try = (i + index) % ARRAY_SIZE;
            if(hashTable[try] == NULL){
                hashTable[try] = new;
                return true;
            }
        }
    }

    return false;
}

void addOrIncrement(char* name){
    //search array to see if name is already there
    bool seen_before = find(name);

    if(seen_before){
        for(int i = 0; i < ARRAY_SIZE; i++){
            if(hashTable[i] != NULL && strncmp(hashTable[i]->name, name, ARRAY_SIZE)==0){
                hashTable[i]->freq++;
            }
        }
    }else{
        insert(name);
    }
}

//////////READ IN//////////READ IN//////////READ IN//////////READ IN//////////READ IN//////////

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
        //insert(buf);
        addOrIncrement( buf);                           //here you call your function from above!
	}

	// always remember to close your file stream
	fclose(f);
    
    printf("%s loaded!\n", *f);
	return true;
}

//////////PRINT//////////PRINT//////////PRINT//////////PRINT//////////PRINT//////////PRINT//////////

void print(){
    for(int i = 0; i < ARRAY_SIZE; i++){
        if(hashTable[i] == NULL){
            printf("\t%i\t---\n", i+1);
        }
        else  if(hashTable[i] != NULL){
                printf("\t%i\t%s - %i\n", i+1, hashTable[i]->name, hashTable[i]->freq);
                //printf("\t%i\t%s\n", i+1, hashTable[i]->name);
                //printf("\t%i\tfull\n", i+1);
            }
        else{
            printf("an error has occured while printing");
        }
    }
    printf("Collisions = %i\nNumterms = %i", collisions, num_terms);
}

//////////MAIN//////////MAIN//////////MAIN//////////MAIN//////////MAIN//////////MAIN//////////

int main()  {
    
    clear_array();
    load_file("names.csv");
    print();
    
    return 0;
}
