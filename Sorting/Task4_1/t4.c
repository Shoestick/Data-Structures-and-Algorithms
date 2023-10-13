#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUFFER 80
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

void
print_game( struct Game *p ) {
	printf("\t%s\t%s\t%i\t%i\n", p->name, p->console, p->score, p->year);
}

int
main ( int argc, char *argv[] ) {
	FILE *f;
	struct Game pArray[MAX_ARRAY];		
	struct Game p;

	// Users must pass the name of the input file through the command line. Make sure
	// that we got an input file. If not, print a message telling the user how to use
	// the program and quit
	if( argc < 2 ) { 
		printf("usage: csv FILE\n"); 
		return EXIT_FAILURE; 
	}

	// Try to open the input file. If there is a problem, report failure and quit
	f = fopen(argv[1], "r");
	if(!f) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}
	
	fetch_game( f, &p ); // discard the header data in the first line

	// Now read pokemon until the end of the file
	int nbGames = 0;
	while(!feof(f)) {
		
		fetch_game( f, &pArray[nbGames] );
		nbGames++;
	}

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

	for(int i = MAX_ARRAY; i > MAX_ARRAY-10; i--) {
		print_game( &pArray[i]);
	}

    // Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}