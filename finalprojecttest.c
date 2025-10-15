#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <unistd.h>

///////////////////////
// Struct Definition //
///////////////////////


///////////////////////////////////////////////////
// User Defined Functions Prototype ///////////////
// List prototypes here and define ////////////////
// them below the main function ///////////////////
///////////////////////////////////////////////////
int startGame();///////////////////////////////////
void randomizeOption(int turn, char order[]);
int scoreGame(int score, int turn, char order[]);
void drawTriangle();
void drawRectangle();
void drawX();
void drawRhombus();
void drawBox();
void drawBoxOnTop();
void displayShapesInNcurses();


int main(){
  char order[100];
  startGame();

  randomizeOption(1, order);

  printf("%c", order[1]);

  return 0;
}

////////////////////////////////////////
// User Defined Functions' Definition //
////////////////////////////////////////

int startGame()
{
  char start;
  // Prints the welcome screen, keeping each line in it's own print statement for easier editing
  printf("Welcome to the Memory Game!\n");
  printf("To start the game press \"g\"");
  printf("In the game various shapes will appear with a circle around it\n");
  printf("You must remember the shapes the are circled and repeat the order\n");
  printf("Use w for up, s for down, d for right, a for left\n\n");
  // Call the printHighScores function here
  printf("What would you like to do?\n");
  printf("\"g\" for a game\n");
  while (start != 'g')
  {
    scanf("%c", &start);
    displayShapesInNcurses();
    drawBoxOnTop();
  }

  return 1;
}

void randomizeOption(int turn, char order[])
{
  srand(time(NULL));
  // Randomly picks a number between 0 and 3
  int newOption = rand() % 4;
  // Assigns the new value of order to w,a,s, or d depending on the value of newOption
  switch (newOption)
  {
    case(0):
      order[turn] = 'w';
      break;
    case(1):
      order[turn] = 'a';
      break;
    case(2):
      order[turn] = 's';
      break;
    case(3):
      order[turn] = 'd';
      break;
    default:
      order[turn] = 'w';
      break;
  }
}

int scoreGame(int score, int turn, char order[])
{
  char currentGuess;
  // Print the informaton before guessing
  printf("Turn: %d\n", turn);
  printf("Score: %d\n", score);
  printf("Okay, what was the order? (Use w,a,s,d)\n");

  // Start the guessing
  for (int i = 1; i <= turn; i--)
  {
    printf("%d time: ", i);
    scanf("%c", currentGuess);
    // Checks if the guess was the correct answer
    if (tolower(currentGuess) == order[i])
    {
      score++;
      printf("Score: \n\n", score);
      if (score >= 99)
      {
        printf("Congrats! You've gotten to the point where we no longer want to format the high score screen!");
        printf("Therefore you should go outside! We're ending the game early.");
        return -1;
      }
    }
    else
    {
      // Call checkHighScore and assign it to a value
      // if (highScore) {Ask to enter the name as 3 capital letters and add a high score somehow}
      // else {
      printf("Nope, the correct answer was %c\n", order[i]);
      printf("Sorry, you lose, at least you got to turn %d!\n", turn);
      printf("Your final score was %d, Try again and get even higher!\n", score);
      // }

      // Ends the function call so it doesn't continue
      return -1;
    }
  }

  return score;
}


void drawTriangle()
{
    int rows = 5; // Shape Size
    int i, j, k;

    for (i = 1; i <= rows; i++) {
        for (j = i; j < rows; j++) {
            printf(" ");
        }
        for (k = 1; k <= (2 * i - 1); k++) {
            printf("^");
        }
        printf("\n");
    }
}

void drawRectangle()
{
  int rows = 10; // Shape Size
    int cols = 6; // Shape Size
    int i, j;


  // Print the rectangle
  for (i = 0; i < rows; i++) {
      // Move 40 spaces right for each line
      for (j = 1; j <= 40; j++) {
          printf(" ");
      }
      for (j = 0; j < cols; j++) {
          if (j == 0 || j == cols - 1 || i == 0 || i == rows - 1)
              printf("H ");
          else
              printf("  "); // Two spaces to maintain the rectangle shape
      }
      printf("\n");
  }
}

void drawX()
{
    int size = 5; // Shape Size
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (i == j || j == size - 1 - i)
                printf("X ");
            else
                printf("  "); 
        }
        printf("\n");
    }
}

void drawRhombus()
{
    printf("    O\n");
    printf("   O O\n");
    printf("  O   O\n");
    printf(" O     O\n");
    printf("  O   O\n");
    printf("   O O\n");
    printf("    O\n");
}

void drawBox() 
{
  int width = 8;
  int height = 12; 

  for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf(". ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void drawBoxOnTop() {
  int choice = rand() % 4; // Randomly choose which shape to draw on top

  // TO DO: Make function that draws both the shape and the box in one function

  // TO DO: Make sure randomization is correct

  // TO DO: Make sure its not in lncurses
  switch (choice) {
      case 0:
          drawBox();
          drawTriangle();
          drawRectangle();
          drawRhombus();
          drawX();
          break;
      case 1:
          drawTriangle();
          drawBox();
          drawRectangle();
          drawRhombus();
          drawX();
          break;
      case 2:
          drawTriangle();
          drawRectangle();
          drawBox();
          drawRhombus();
          drawX();
          break;
      case 3:
          drawTriangle();
          drawRectangle();
          drawRhombus();
          drawBox();
          drawX();
          break;
      default:
          break;
    }
}

void displayShapesInNcurses() {
    initscr(); // Initialize ncurses
    clear(); // Clear the screen

    // Print shapes in the ncurses window
    mvprintw(5, 20, "Triangle");
    drawTriangle();
    refresh(); // Refresh the window

    // Wait for 2 seconds
    sleep(2);

    endwin(); // Close ncurses
}