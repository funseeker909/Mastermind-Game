/* MASTERMIND
 *
 * Name: Logan Gardner
 * Instructor: Workman
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_DIM 6
#define MIN_DIM 3
#define MAX_GUESSES 12
#define MAXCHAR 'F'

typedef struct
{
   char letters[MAX_DIM+1]; /* +1 for the null char */
   int exact;
   int inexact;
} Guess;

/* This function already implemented.
 * Compile with "gcc -Wall -ansi -pedantic mastermind.c util.o" to use it.
 * Otherwise, implement the function yourself and just compile with "gcc -Wall -ansi -pedantic  mastermind.c"
 */
int calcMatches(char answer[], int dim, Guess guess[], int index);

/* Prototypes for functions you must implement */
char getRandChar(char maxchar);
void getGuess(char letters[], int dim, char maxChar);
void printBoard(Guess guesses[], int tries, int dim);

int main(void)
{
   char maxLetter, again;
   int dimension, seed, guesses;
   int possibleNumbers, i = 0;
   Guess gameStructure[12];
   char secretAnswer[MAX_DIM + 1];
   int won;
   
   /*variables for the average*/
   int gamesPlayed = 0;
   int attempts = 0;
   double average;

   printf("Enter max letter: ");
   scanf(" %c", &maxLetter);
   
   
   while ( maxLetter > 'F' || maxLetter < 'A' )
	{
		printf("Max letter must be between A and F.\n");
		printf("Enter max letter: ");
		scanf(" %c", &maxLetter);
	}
	
	printf("Enter game dimension: ");
	scanf("%d", &dimension);
	
    while ( dimension > 6 || dimension < 3 )
	{
		printf("Dimension must be between 3 and 6.\n");
		printf("Enter game dimension: ");
		scanf("%d", &dimension);
	}

   	printf("Enter the seed: ");
    scanf("%d", &seed);
	srand(seed);

	for (i=0; i<dimension; i++)
	{
		secretAnswer[i] = getRandChar(maxLetter);
	}
	secretAnswer[i] = '\0';
	
	possibleNumbers = (maxLetter - 'A' + 1);
	
	guesses = ceil((double)(dimension*possibleNumbers)/3);
	
	do
	{
		printf("\nStarting game...\n");
		printf("You have %d guesses left!\n", guesses);
		gamesPlayed++;
		i = 0;
		
		while (guesses != 0 && won != 1)
		{
			
			getGuess(gameStructure[i].letters, dimension, maxLetter);

			attempts++;
			
			won = calcMatches(secretAnswer, dimension, gameStructure, i);
			
			printBoard(gameStructure, i+1, dimension);
			
			guesses--;
			
			i++;
			
			if ( won == 1 )
			{
				printf("\nYou win!!\n");
				average = (double)attempts/gamesPlayed;
				printf("Pattern found in %d attempts! Current average: %.3f\n\n", i, average);			
				break;

			}
			
			printf("\nYou have %d guesses left!\n",guesses);

		}
		printf("Another game? [Y/N]? ");
		scanf(" %c", &again);
		won = 0;
		guesses = ceil((double)(dimension*possibleNumbers)/3);
		
		for (i=0; i<dimension; i++)
		{
			secretAnswer[i] = getRandChar(maxLetter);
		}
		
	} while ( again != 'n' && again != 'N' );
		
   /* TODO - determine maximum guesses based on max letter and dimension */


   /* TODO - main game loop here */

	
   return 0;
}

/* TODO - Implement this function.
 * Use the rand() function to return a random character
 *    in between 'A' and the maxChar.
 */
char getRandChar(char maxChar)
{
	return rand()%(maxChar - 'A' + 1) + 'A';
}

/* TODO - Implement this function.
 * Prompt the user for characters to fill in the letters array.
 * Make sure all input characters are between 'A' and maxChar.
 * "dim" indicates how many letters to get.
 */
void getGuess(char letters[], int dim, char maxChar)
{
	int i;
	
	printf("Enter Guess (%d chars): ", dim);
	scanf("%s", letters);
	
	for ( i=0; i<dim; i++)
	{
		if (letters[i] > maxChar)
		{
			printf("One or more chars out of range A-F, try again: ");
			scanf("%s", letters);
			i = -1;
		}
	}
	
}
 
/* TODO - Implement this function.
 * Display the mastermind board according to the following example:
 *
 *       XXXX
 *       ----
 * (0,2) ABCD
 * (0,3) ABBD
 * (3,0) BEDE
 *
 * "tries" indicates how many guesses are in the Guess array.
 * "dim" indicates how many letters are in each Guess.
 */
void printBoard(Guess guesses[], int tries, int dim)
{
	int i;
	
	printf("\n      ");
	for ( i=0; i<dim; i++)
	{
		printf("X");
	}
	printf("\n");
	
	printf("      ");
	for ( i=0; i<dim; i++)
	{
		printf("-");
	}
	printf("\n");

	for ( i=0; i<tries; i++)
	{
		printf("(%d,%d) %s\n", guesses[i].exact, guesses[i].inexact, guesses[i].letters);
	}
}
