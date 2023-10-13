//#include "t2.h"
//#include "t4.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUFFER 256
#define MAX_ARRAY 18625

struct Game {
    char name[MAX_BUFFER], console[MAX_BUFFER];
    int score, year;
};

// The CSV parser
int
next_field( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<max-1 ) { ++i; } 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

// Stuff to make life a bit neater in main
void
fetch_game (  FILE *csv, struct Game *p) {
	char buf[MAX_BUFFER];

	next_field( csv, p->name, MAX_BUFFER );  // name and type are just strings so read
	next_field( csv, p->console, MAX_BUFFER );

	// Load all the pokemon's stats from the file using buffer as intermediary
	next_field( csv, buf, MAX_BUFFER );
	p->score = atoi(buf);          // atoi stands for ASCII to Integer
	next_field( csv, buf, MAX_BUFFER ); // It converts strings to numbers
	p->year = atoi(buf);
}

bool load_file ( char *fname, struct Game array[MAX_ARRAY] ) {
    FILE *f;
    struct Game p;

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return false; 
	}

	char buf[MAX_BUFFER];
    int nbGames = 0;
    while(fgets(buf, sizeof(buf), f)){
        char *token;

        token = strtok(buf, ",");

        while(token != NULL) {
            fetch_game(f, &p);
            token = strtok(NULL, ",");
        }
        fetch_game( f, &array[nbGames] );
        //print_pokemon( &array[nbGames] );
		//printf("\n");
        nbGames++;
        printf("%i, ", nbGames);
    }
}

int main(int argc, char *argv[])  {

    struct Game pArray[MAX_ARRAY];
    
    load_file("t4_ign.csv", pArray);

    for(int sorted = 0; sorted < MAX_ARRAY - 1; sorted++){
      for(int i = sorted + 1; i > 0; i--){
          if(pArray[i - 1].score > pArray[i].score){
            struct Game temp = pArray[i];
            pArray[i] = pArray[i - 1];
            pArray[i - 1] = temp;
          } else{
              break;
            }
        }
    }

    for(int i = 0; i < 10; i++){
        printf("%s, %i\n", pArray[i].name, pArray[i].score);
    }
    
    return 0;
}
