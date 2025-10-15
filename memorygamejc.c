// SE 185: Final Project Template //
////////////////////////////////////
/* 
Team xx (please insert your team number instead of xx)
Team member 1 "Johnathon Endicott" | 50%
Team member 2 "Camden Beightler" | 50%
*/

//////////////////////////////
#include <stdio.h>////////////
//add more here///////////////
#include <stdlib.h>///////////
#include <string.h>///////////
#include <ctype.h>////////////
#include <time.h>/////////////
#include <unistd.h>///////////
#include <ncurses/ncurses.h>//
//////////////////////////////

///////////////////////
// Struct Definition //
///////////////////////


//////////////////////////////////////
// User Defined Functions Prototype //
// List prototypes here and define ///
// them below the main function //////
//////////////////////////////////////
int startGame(char* names[], int scores[]);
int randomizeOption(int turn, char order[]);
int scoreGame(int score, int turn, char order[], char* names[], int scores[]);
void printShapes(int selected);
void printTriangle();
void printRectangle();
void printX();
void printCircle();
void printBox(int y, int x);
void readHighScore(char* names[], int scores[]);
void printHighScore(char* names[], int scores[]);
int checkHighScore(char* names[], int scores[], int currentScore);
void writeHighScores(char* names[], int scores[]);
void countdown();

int main(){
	char order[100];
	char* names[10];
	int scores[10];
	int selected;
	int score = 20;
	int turn = 1;
	readHighScore(names, scores);
	startGame(names, scores);
	
	//game loop
	while (score != -1)
	{
		selected = randomizeOption(turn, order);
		printShapes(selected);
		score = scoreGame(score, turn, order, names, scores);
		turn++;
	}

	writeHighScores(names, scores);
	return 0;
}

////////////////////////////////////////
// User Defined Functions' Definition //
////////////////////////////////////////

int startGame(char* names[], int scores[])
{
	char start;
	// Prints the welcome screen, keeping each line in it's own print statement for easier editing
	printf("Welcome to the Memory Game!\n");
	printf("To start the game press \"g\"\n");
	printf("In the game various shapes will appear with a circle around it\n");
	printf("You must remember the shapes the are circled and repeat the order\n");
	printf("Use w for up, s for down, d for right, a for left\n\n");
	printHighScore(names, scores);
	printf("What would you like to do?\n");
	printf("\"g\" for a game\n");
	while (start != 'g')
	{
		scanf("%c", &start);
	}
	countdown();

	return 1;
}

int randomizeOption(int turn, char order[])
{
	srand(time(NULL));
	// Randomly picks a number between 0 and 3
	int newOption = rand() % 4;
	// Assigns the new value of order to w,a,s, or d depending on the value of newOption
	switch (newOption)
	{
		case(0):
			order[turn] = 'w';
			// Draw select box around the upper shape
			break;
		case(1):
			order[turn] = 'a';
			// Draw select box around the rightmost shape
			break;
		case(2):
			order[turn] = 's';
			// Draw select box around the lower shape
			break;
		case(3):
			order[turn] = 'd';
			// Draw select box around the leftmost shape
			break;
		default:
			order[turn] = 'w';
			// Draw select box around the upper shape
			break;
	}
	return newOption;
}

int scoreGame(int score, int turn, char order[], char* names[], int scores[])
{
	char currentGuess;
	// Print the informaton before guessing
	printf("Turn: %d\n", turn);
	printf("Score: %d\n", score);
	printf("Okay, what was the order? (Use w,a,s,d)\n");

	// Start the guessing
	for (int i = 1; i <= turn; i++)
	{
		printf("%d time: ", i);
		scanf(" %c", &currentGuess);
		
		// Prevents invalid inputs
		for (int i = 0; i < currentGuess; i++) 
		{
			while(currentGuess != 'w' && currentGuess != 'a' && currentGuess != 's' && currentGuess != 'd') 
			{
			printf("Error: Invalid input '%c'. Please re-enter w, a, s, or d.\n", currentGuess);
			printf("Re-Enter: ");
			scanf(" %c", &currentGuess);
			}
		}
		// Checks if the guess was the correct answer
		if (tolower(currentGuess) == order[i])
		{
			score++;
			printf("Score: %d\n\n", score);
			if (score >= 99)
			{
				printf("Congrats! You've gotten to the point where we no longer want to format the high score screen!\n");
				printf("Therefore you should go outside! We're ending the game early.");
			if (checkHighScore(names, scores, score))
			{
			printHighScore(names, scores);
			}
				return -1;
			}
		}
		else
		{
			printf("Nope, the correct answer was %c\n", order[i]);
			printf("Sorry, you lose, at least you got to turn %d!\n", turn);
			printf("Your final score was %d, Try again and get even higher!\n", score);
			if (checkHighScore(names, scores, score))
			{
				printHighScore(names, scores);
			}
			// Ends the function call so it doesn't continue
			return -1;
		}
	}

	printf("Good job, get ready for the next round.\n");
	countdown();

	return score;
}

void printShapes(int selected)
{
	initscr();
	refresh();

	// Draws all the shapes regardless of which option was selected
	printTriangle();
	printRectangle();
	printX();
	printCircle();
	switch (selected)
	{
		// Draw a box around the selected shape
		case(0):
			printBox(0, 46);
			break;
		case(1):
			printBox(16, 28);
			break;
		case(2):
			printBox(32, 47);
			break;
		case(3):
			printBox(16, 64);
			break;
		default:
			printBox(9, 44);
			break;
	}
	// Sleeps 2 seconds so the user can actually see which shape was selected
	sleep(2);
	clear();
	endwin();
}

void printTriangle()
{
	for (int i = 0; i < 4; i++)
	{
		// Adds 1 character in the middle of the triangle for the top of it
		mvaddch(i + 2, 50, '^');
		refresh();
		for (int j = 0; j <= i; j++)
		{
			// Adds j number of characters to the left and right each iteration, depending on the current size of i
			mvaddch(i + 2, 50 - j, '^');
			refresh();
			mvaddch(i + 2, 50 + j, '^');
			refresh();
		}
	}
}

void printRectangle()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			// Only prints a character if it's on the edge of the square
			if (i == 0 || j == 0 || i == 4 || j == 4)
			{
				mvaddch(i + 18, j + 30, 'I');
				refresh();
			}
		}
	}
}

void printX()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			// Only prints a character if there was an intersection so it prints an X shape
			if (i == j || j == 4 - i)
			{
				mvaddch(i + 18, j + 66, 'x');
				refresh();
			}
		}
	}
}

void printCircle()
{
	for (int i = 0; i < 3; i++)
	{
		// Prints a character starting from the middle and further out and expanding out until the two ends meet
		mvaddch(36 + i, 48 + i, 'o');
		refresh();
		mvaddch(36 + i, 54 - i, 'o');
		refresh();
		mvaddch(36 - i, 48 + i, 'o');
		refresh();
		mvaddch(36 - i, 54 - i, 'o');
		refresh();
	}
}

void printBox(int y, int x)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			// Similar structure to the rectangle but bigger so it fits around each shape
			if (i == 0 || j == 0 || i == 8 || j == 8)
			{
				mvaddch(i + y, j + x, '*');
				refresh();
			} 
		}
	}
}

void readHighScore(char* names[], int scores[])
{
	int rank = 0;
	char line[6];
	char *n;
	// Opens the file, formatted differently than provided, each entry is seperated by a newline rather than a '-'
	FILE* fp = fopen("highScores.txt", "r");
	while (!feof(fp)) 
	{
		// Scans the numbers in the front of each line, this takes it out of the fgets statement
		fscanf(fp, "%d", &scores[rank]);
		// Scans the remainder of the line to n so it can be converted into names
		n = fgets(line, 4, fp);
		// Only executes if n actually read something
		if (n != NULL)
		{
			// Gives the array a length so it can store the initials
			names[rank] = (char *)malloc(strlen(line) + 1);
			// Assigns the name of the specific rank to the index of the same number - 1, will be accessed as if it was the same
			strcpy(names[rank], line);
			// Adds to rank
			rank++;
		}
	}
	fclose(fp);
}

void printHighScore(char* names[], int scores[])
{
	printf("Highscore Table:\n");
	printf("Rank Score Name\n");
	// Loop to print high scores
	for(int i = 0; i < 9; i++)
	{
		printf(" %d    %d   %s\n", i + 1, scores[i], names[i]);
	}
}

int checkHighScore(char* names[], int scores[], int currentScore)
{
	char initials[4];

	//Checks the high score list and moves them based on their rank
	for (int i = 0; i < 9; i++)
	{
		if (currentScore > scores[i])
		{
			printf("\nPlease enter your initials: ");
			scanf("%s", initials);
			for(int j = 8; j > i; j--)
			{
				scores[j] = scores[j - 1];
				strcpy(names[j], names[j - 1]);
			}
			scores[i] = currentScore;
			strcpy(names[i], initials);
			printf("%s\n", names[i]);
			return 1;
		}	
	}
	return 0;
}

void writeHighScores(char* names[], int scores[])
{
	// Opens the file in write mode, which deletes the old file
	FILE* fp = fopen("highScores.txt", "w");
	for (int i = 0; i < 9; i++)
	{
		// Prints each high score on its own line
		fprintf(fp, "%d%s\n", scores[i], names[i]);
	}
	fclose(fp);
}

void countdown()
{
	printf("3...\n");
	sleep(1);
	printf("2...\n");
	sleep(1);
	printf("1...\n");
	sleep(1);
}