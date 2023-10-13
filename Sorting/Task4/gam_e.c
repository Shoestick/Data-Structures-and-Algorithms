#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle
#define MAX_NB_POKEMON 18625 // Maximum number of Pokemons

/*
 * id: ID for each pokemon (not unique)
 * name: Name of each pokemon
 * type1: Each pokemon has a type, this determines weakness/resistance
 * type 2: Some pokemon are dual type and have 2
 * stat_total: sum of all stats, a general guide to how strong a pokemon is
 * hp: hit points, or health, defines how much damage a pokemon can withstand
 * attack: the base modifier for normal attacks (eg. Scratch, Punch)
 * defense: the base damage resistance against normal attacks
 * sp_atk: special attack, the base modifier for special attacks (e.g. Blizzard)
 * sp_def: the base damage resistance against special attacks
 * speed: determines which pokemon attacks first each round
 * gen: Which generation does the pokemon belong to (1 is oldest, 5 newest)
 * legendary: whether or not pokemon is a legendary pokemon (e.g. Moltres, Articuno)
 * desc: A short text description of the pokemon taken from Pokedex
*/
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
fetch_pokemon (  FILE *csv, struct Game *p) {
	char buf[MAX_BUFFER];

	next_field( csv, p->name, MAX_BUFFER );  // name and console are just strings so read
	next_field( csv, p->console, MAX_BUFFER );

	// Load all the pokemon's stats from the file using buffer as intermediary
	next_field( csv, buf, MAX_BUFFER );
	p->score = atoi(buf);          // atoi stands for ASCII to Integer
	next_field( csv, buf, MAX_BUFFER ); // It converts strings to numbers
	p->year = atoi(buf);                  // It is not a totally safe function to use.
}

void
print_pokemon( struct Game *p ) {
	printf(" --------------------------------------------------------------\n");
	printf("| Name %s | Console %s | IGN Score %i | Year %i |\n",
			p->name, p->console, p->score, p->year);
	printf(" --------------------------------------------------------------\n");
}

int
main ( int argc, char *argv[] ) {
	FILE *f;
	struct Game pArray[MAX_NB_POKEMON];		
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
	
	fetch_pokemon( f, &p ); // discard the header data in the first line

	// Now read and print pokemon until the end of the file
	int nbPokemons = 0;
	while(!feof(f)) {
		
		fetch_pokemon( f, &pArray[nbPokemons] );
		print_pokemon( &pArray[nbPokemons] );
		printf("\n");
		nbPokemons++;
	}

	// Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}