/*
	Names:	
	Matthew Villarica
  Mark Laroza
  Pierre Hernandez
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define FALSE 0
#define TRUE 1

// gameboard design icons
#define HD 196 // horizontal divider 
#define VD 179 // vertical divider 
#define C 197   //cross
#define V 186 // vertical lines for gameboard
#define H 205 // horizontal lines for gameboard
#define UR 187 // upper-right corner for gameboard
#define LR 188 // lower-right corner for gameboard
#define UL 201 // upper-left corner for gameboard
#define LL 200 // lower-left corner for gameboard

// characters for players
#define EMPTY 219 // H areas
#define CHA '1' // Cha
#define ORD '0' // Ord

typedef char gameBoard [4][4]; // gameboard contents

/*
  Cha - 'C'
  Ord - 'O'
  H coords - 'X'
  other free coords - small letters
*/

// =================================== GAME DISPLAY

/*
System colors for terminal:
<color ID> - <color>
1 - Blue
2 - Green
3 - Aqua
4 - Red
5 - Purple
6 - Yellow
7 - White/light gray
8 - Gray
9 - Light blue
0 - Black
A - Light green
B - Light aqua
C - Light red
D - Light purple
E - Light yellow
F - Bright white 
*/

// prints cIcon every nSpacing
void printFloatingChars(int nMax, char cIcon, int nSpacing)
{
  int k;
  
  for(k = 1; k <= nMax; k++)
  {
    if(k % nSpacing == 0) // checks if it is nSpacing from last printed char
      printf("%c", cIcon); 
    else
      printf(" ");
  }
}


// ------------------------------------ DASHBOARD
// ------------------------------------ DASHBOARD

    // this part is kinda hard to display
/*
Dashboard outline

  ===================================================================================
  || Sector 1:         | Sector 2:         | Sector 3:         | Sector 4:         ||
  || Areas: a, d, g    | Areas: b, f, k    | Areas: c, e, h    | Areas: i, j, k    || 
  ===================================================================================
  =======================  ============================
  ||       CHA         ||  ||          ORD           ||
  ||  Conquered Areas  ||  ||     Protected Areas    ||
  ||                   ||  ||                        ||
  || Sector 1: <***>   ||  ||  Areas:                ||
  || Sector 2: <***>   ||  ||     <***>              ||
  || Sector 3: <***>   ||  ||                        ||
  || Sector 4: <***>   ||  ||  Units left: <*>       ||
  ||                   ||  ||  <**>                  ||
  =======================  ============================
  
  * number of times can conquer an area (Max: 4)
  ** displays a warning message if Ord needs to free up an area he/she conquered 
     since it is only limited to 4 areas
  *** displays the corresponding letters if they conquered the letter area
  
Sector 1:
Coords - {1,4},{2,4},{3,4}
Array index- [0][3], [1][3], [2][3] 
letters - a, d, g

Sector 2:
Coords - {2,2},{3,3},{4,4}
Array index- [1][1], [2][2], [3][3] 
letters - b, f, k

Sector 3:
Coords - {2,3},{3,2},{4,1}
Array index- [1][2], [2][1], [3][0] 
letters - c, e, h

Sector 4:
Coords - {4,2},{4,3},{4,4}
Array index- [1][2], [2][1], [3][0] 
letters - i, j, k

# coords can be read as matrix
# sectors are the winning combos
# letters of the sectors are based from the coordinates in row-col array form
## (check Gameboard outline to visualize (lines: 39-47))
*/

// ----------------------------------------------- Sector Dashboard

// prints the upper and lower part of the sector dashboard
void printOuterSectorBoard(char cLeftCorner, char cRightCorner)
{
  printf("\t%c", cLeftCorner);
  printFloatingChars(83, H, 1); 
  printf("%c\n", cRightCorner); // total width: 85 chars excluding tab chars
}

// prints sector board content with the sector numbers with its corresponding areas
void printSectorBoardContent()
{
  int w;
  char cWinningLetterCombo[4][3] = {{'a','d','g'}, {'b','f','k'}, {'c','e','h'}, {'i','j','k'}};

  printf("\t%c", V);
  // width: 80 chars(contents) + 3 chars(dividers)
  for(w = 1; w <= 4; w++)
  {
    printf("%8s%2d:", "Sector", w);

    if(w < 4)
      printf("%10c", VD);
  }
  printf("%10c\n\t%c", V, V);

  // width: 80 chars(contents) + 3 chars(dividers)
  for(w = 0; w < 4; w++) 
  {
    // prints the designated area letters for each sector
    printf("%9s", "Areas: ");
    printf("%c, %c, %c", cWinningLetterCombo[w][0], cWinningLetterCombo[w][1], cWinningLetterCombo[w][2]);

    if(w < 3)
      printf("%5c", VD); 
  }
  printf("%5c\n", V);

  // total width: 85 chars
}

// displays the whole sector dash board
void displaySectorDashboard()
{
  printOuterSectorBoard(UL,UR);
  printSectorBoardContent();
  printOuterSectorBoard(LL,LR);
}
// ----------------------------------------------------------------

// ------------------------------------------ Cha and Ord Dashboard

// prints the upper and lower part of the Cha and Ord dashboard
void printOrdChaDashBorder(char cLeft, char cRight)
{
  printf("\t%c", cLeft);
  printFloatingChars(19, H, 1);
  printf("%c\t%c", cRight, cLeft);
  printFloatingChars(19, H, 1);
  printf("%c\n", cRight); // total width: 42 chars excluding tab chars
}

// prints the headers of Cha and Ord dashboard
void printOrdChaDashHeaders()
{
  printf("\t%c", V);
  printf("%10s%10c\t%c%10s%10c\n", "CHA", V, V, "ORD", V);
  printf("\t%c%16s%4c\t%c%16s%4c\n", V, "Conquered Areas", V, V, "Protected Areas", V);
  printf("\t%c%20c\t%c%20c\n", V, V, V, V); // total width: 42 chars excluding tab chars
}

// prints Ord's conquered areas
void printOrdConqueredAreas(char cOrd[], int nOCount)
{
  int q;

  printf("%8s", "Areas: ");

  for(q = 0; q < 4; q++)
  {
    // prints the area letters Ord conquered
    if(q < nOCount) //cOrd[q] != '\0'
      printf("%c ", cOrd[q]);
    
    // prints a whitespace if Ord hasn't utilized all four units to specific areas yet
    else
      printf("  ");
  }

  printf("%4c\n", V);
}

// returns TRUE(1) if Cha conquered the cKeyCombo area
int checkConqueredAreas(char cKeyCombo, char cPlayer[], int nElem)
{
  int t, bFound = FALSE;

  // linear search the array of cPlayer
  for(t = 0; t < nElem && !bFound; t++)
    if(cPlayer[t] == cKeyCombo)
      bFound = TRUE; // search stops if found

  return bFound;
}

// prints the contents of Cha and Ord dashboard
// it includes the areas conquered of both parties
void printOrdChaDashContents(char cCha[], int nCElem, char cOrd[], int nOElem)
{
  int row, col, nUnitsLeft = 4 - nOElem; // nUnitsLeft for Ord
  char cWinCombo[4][3] = {{'a','d','g'}, {'b','f','k'}, {'c','e','h'}, {'i','j','k'}};

  // prints the contents per row
  for(row = 0; row < 4; row++)
  {
    printf("\t%c%7s%2d: ", V, "Sector", row+1);

    // prints the areas within the sectors that Cha conquered
    for(col = 0; col < 3; col++)
    {
      // prints the area letter if conquered by Cha
      if(checkConqueredAreas(cWinCombo[row][col], cCha, nCElem))
        printf("%c ", cWinCombo[row][col]);

      // prints a whitespace if area not conquered by Cha
      else
        printf("  ");
    } // width: 17 chars

    printf("%3c\t%c", V, V);

    if(row == 0)
      printOrdConqueredAreas(cOrd, nOElem); // prints Ord conquered areas

    if(row == 1)
      printf("%13s%d%6c\n", "Units left: ", nUnitsLeft, V); // units left for Ord to use

    if(row == 2 && nUnitsLeft == 0)
      printf("%13s%7c\n", "> WARNING!!!", V); // warning message if 0 units left for Ord

    if(row == 3 && nUnitsLeft == 0)
      printf("%17s%3c\n","> FREE UP 1 UNIT", V); // hint message if 0 units left for Ord

    if((row == 2 && nUnitsLeft > 0) || (row == 3 && nUnitsLeft > 0))
      printf("%20c\n", V);
  } // total width: 42 chars excluding tab chars
}

// prints the whole Cha and Ord Dashboard
void displayOrdChaDashboard(char cCha[], int nCElem, char cOrd[], int nOElem)
{
  printOrdChaDashBorder(UL, UR);
  printOrdChaDashHeaders();
  printOrdChaDashContents(cCha, nCElem, cOrd, nOElem);
  printOrdChaDashBorder(LL, LR); // total width: 42 chars excluding tab chars
}
// ----------------------------------------------------------------
// ----------------------------------------------------------------


// ------------------------------------ GAMEBOARD
// ------------------------------------ GAMEBOARD

/*
Gameboard design outline:

  ===================
  || X | X | X | a ||     // X - H coords  
  ||---------------||     // "a - k" - free areas
  || X | b | c | d ||     // replace small letters with 'C' if Cha takes the area
  ||---------------||     // replace small letters with 'O' if Ord takes the area
  || X | e | f | g ||
  ||---------------||
  || h | i | j | k ||
  ===================

  row-col array type of access and display
  left to right
  top to bottom
*/

// prints the upper and lower border of the gameboard
void printGameboardBoarder(char cLeftCorner, char cRightCorner)
{
  printf("%30c", cLeftCorner);
  printFloatingChars(15, H, 1);
  printf("%c\n", cRightCorner);
}

// prints a divider for each row 
void printGameboardRowDivi()
{
  int d;

  printf("%30c", V);

  for(d = 0; d < 4; d++)
  {
    printf("%c%c%c", HD, HD, HD);

    if(d < 3)
      printf("%c", C);
  }

  printf("%c\n", V);
}

// prints the contents of aBoard
void printGameboardContent(char aBoard[])
{
  int q;

  printf("%30c", V);

  for(q = 0; q < 4; q++)
  {
    printf(" %c ", aBoard[q]);

    if(q < 3)
      printf("%c", VD);
  }

  printf("%c\n", V);
}

// displays the whole gameboard
void displayGameboard(gameBoard aBoard)
{
  int z;

  printGameboardBoarder(UL, UR);
  
  for(z = 0; z < 4; z++)
  {
    printGameboardContent(aBoard[z]);

    if(z < 3)
      printGameboardRowDivi();
  }
  
  printGameboardBoarder(LL, LR);
}
// ----------------------------------------------------------------
// =================================================================

/*
/for coordinates
typedef int Coords[3];


	//not sure about data type and return type of this function pero for sure this is a function, pos so maybe an int
  
  feeling ko pwede int* pointer yung paramater for this

void NextPlayerMove(int bInP, int pos, int Ord[], int Cha[]) //pos = chosen coordinate/place by the player (?)
{
  
}
*/


typedef struct WComboTag
{
  int x[3];
  int y[3];
  
}WComboType;
 /*Returns 1 if Chaos conquers a winning combo, 0 otherwise
 */
int ChaosWin(gameBoard board)
{
  WComboType WCombos[4];
  int bFound = 0;
  int cCount;

  int i;
  int j;
  
  WCombos[0].x[0] = 0;
  WCombos[0].x[1] = 1;
  WCombos[0].x[2] = 2;

  WCombos[0].y[0] = 3;
  WCombos[0].y[1] = 3;
  WCombos[0].y[2] = 3;
  
  WCombos[1].x[0] = 1;
  WCombos[1].x[1] = 2;
  WCombos[1].x[2] = 3;

  WCombos[1].y[0] = 1;
  WCombos[1].y[1] = 2;
  WCombos[1].y[2] = 3;

  WCombos[2].x[0] = 1;
  WCombos[2].x[1] = 2;
  WCombos[2].x[2] = 3;

  WCombos[2].y[0] = 2;
  WCombos[2].y[1] = 1;
  WCombos[2].y[2] = 0;

  WCombos[3].x[0] = 3;
  WCombos[3].x[1] = 3;
  WCombos[3].x[2] = 3;

  WCombos[3].y[0] = 1;
  WCombos[3].y[1] = 2;
  WCombos[3].y[2] = 3;
  
  i = 0;
  
  while(bFound == 0 && i < 4) {

    cCount = 0;
      
    for(j = 0; j < 3; j++) {
      if(board[WCombos[i].x[j]][WCombos[i].y[j]] == CHA)
        cCount++;
        
    }

    i++;
    
    if(cCount == 3)
      bFound = 1;
  } 

  if(bFound == 1)
    return 1;
  else return 0;
  
  
}  
/*
    Returns 0 if Chaos wins, 1 if Ord wins, and -1 if the game goes on.

    @param board - The 2D array of characters that represents the gameboard.
    
  

*/
int GameOver(gameBoard board) 
{
  int freeCount = 11;
  int bResult = -1; //initially assume that the game will continue given the contents of board

  int i, j;
  
  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {

      if(board[i][j] == CHA || board[i][j] == ORD) 
          --freeCount;   
      
   }
  }

  //for debugging
  // printf("\n*** FREECOUNT: %d****\n", freeCount);

  
  if(ChaosWin(board)) //Win condition of Chaos
    bResult = 0;
  
  if(freeCount == 0) //set of free spots is empty, Ord wins
    bResult = 1;
 
  
  return bResult; 
  
}

int searchCharKey(char key, char cArray[], int count) 
{
  
  int j;
  int index = -1; // -1 = not found
  
  for(j = 0; j < count; j++) {

    if(key == cArray[j])
      index = j;
    
  }
  return index;
}

/* 
    Checks if user input is a valid choice in the game board.
    Returns 1 if user input is a valid choice, 0 otherwise.

    @param cChoice - user input
    @param board - the matrix representing the gamebaord
*/

int checkChoice(char cChoice, gameBoard board)
{
  //VALID INPUT: a, b , c, d, e, f, g, h, i , j , k
  char validInput[11];
  
  int count = 0;
  int res;

  int i, j;

  for(i = 0; i < 4; i++)
    for(j = 0; j < 4; j++)
      if(board[i][j] != EMPTY && board[i][j] != CHA && board[i][j] != ORD) {
        validInput[count] = board[i][j];
        count++;
        
        
      }

  res = searchCharKey(cChoice, validInput, count);

  if(res == -1)
    return 0;
  else return 1;


}

// gets a single character from user
void getChar(char *cChoice)
{
  char cGet = '\0';
  int bFirst = TRUE;

  // scans up until newline character
  // to avoid any extra characters being left in the input buffer
  while(cGet != '\n')
  {
    scanf("%c", &cGet);

    if(bFirst) // gets first character only
    {
      *cChoice = cGet;
      bFirst = FALSE;
    } 
  }
}

void deleteChar(char aOrd[], int nIndexToDelete)
{
  int w;

  // deletes the character and moves the contents of the array
  for(w = nIndexToDelete; w + 1 < 4; w++)
    aOrd[w] = aOrd[w + 1];

  aOrd[w] = '\0'; // deletes last element of array
}

void removeOrd(int *OrdCount, char aOrd[], gameBoard board, gameBoard copyOfBoard, char cToRemove)
{
  // removes Ord's area in the gameboard and in Ord's array itself
  // then update array contents
  int row, col, bDeleted = FALSE;

  for(col = 0; col < *OrdCount && !bDeleted; col++)
    if(cToRemove == aOrd[col])
    {
      deleteChar(aOrd, col); // removes the character from Ord's array
      bDeleted = TRUE; // flags the loop that cToRemove is removed in Ord's array
    }
  
  for(row = 0; row < 4 && bDeleted; row++)
    for(col = 0; col < 4 && bDeleted; col++)
      if(cToRemove == copyOfBoard[row][col])
      {
        board[row][col] = copyOfBoard[row][col]; // changes back the gameboard content to its default unconquered content
        bDeleted = FALSE; // area removal is done
      }

  --*OrdCount; // decrements number of areas Ord has conquered
}

/* 
    Checks if input of Ord is in Ord's array of conquered areas when Ord
    has to remove one of his conquered areas.

    @param aOrd - array of Ord's conquered areas
    @param toRemove - user input, checked for validity
*/
int isValidOrdRemove(char aOrd[], char toRemove) 
{
  int res; 

  res = searchCharKey(toRemove, aOrd, 4);

  if(res == -1)
    return 0;
  else return 1;



}

void placeChaOrd(gameBoard board, char cChoice, int bTurn)
{
  int i;
  int j;

  for(i = 0; i < 4; i++) {
    
    for(j = 0; j < 4; j++) {

      if(board[i][j] == cChoice) {

        if(bTurn == TRUE)
          board[i][j] = CHA;
        else 
          board[i][j] = ORD;

      }

    }
  }
}

int main()
{
  gameBoard board = {{EMPTY,EMPTY,EMPTY,'a'},{EMPTY,'b','c','d'},{EMPTY,'e','f','g'},{'h','i','j','k'}};
  gameBoard copyOfBoard = {{EMPTY,EMPTY,EMPTY,'a'},{EMPTY,'b','c','d'},{EMPTY,'e','f','g'},{'h','i','j','k'}};
  int bTurn = TRUE; // TRUE = 1; FALSE = 0
  int OrdCount = 0, bValid = 0, bRemove;
  int ChaCount = 0, bGame = -1;
  char aOrd[4];
  char aCha[11];
  char cChoice; // player input
	
  /*If and only neither Cha nor Ord has won yet, the game will continue */
  while(bGame == -1) // GameOver(board) == -1
  {
    system("cls"); //refreshes display

    // displays
    displaySectorDashboard();
	  displayOrdChaDashboard(aCha, ChaCount, aOrd, OrdCount);
	  displayGameboard(board);

    if(bTurn)
      printf("\n%40s", "CHA'S TURN");
    else
      printf("\n%40s", "ORD'S TURN");

    // prints this when OrdCount < 4 or when it's still Cha's turn
    if(OrdCount < 4 || bTurn)
      printf("\n%53s", "Enter area to conquer: ");
    // prints when it is Ord's turn and his max capacity is reached
    if(OrdCount == 4 && !bTurn)
      printf("\n%55s", "Enter area to unconquer: ");

    // get input for either Ord or Cha
    getChar(&cChoice);
    
    if(OrdCount < 4 && (!bTurn || bTurn))
      bValid = checkChoice(cChoice, board);


    // Cha entered a valid area to conquer
    if(bValid && bTurn) {
      
      /*Place cha's character in corresponding place in the gameboard. */
      placeChaOrd(board, cChoice, bTurn);

      //Put's new area conquered a part of Cha's domain(array), increments ChaCount
      aCha[ChaCount] = cChoice;
      ChaCount++;

      //Ends Cha's turn, it is now Ord's turn
      bTurn = FALSE;

    } else if (bValid && !bTurn && OrdCount < 4) {

      /*Place Ord's character in corresponding place in the gameboard. */

      placeChaOrd(board, cChoice, bTurn);

      //Put's new area conquered a part of Ord domain(array), increments OrdCount
      aOrd[OrdCount] = cChoice;
      OrdCount++;

      bTurn = TRUE;//End's Ord's turn, it is now Cha's turn
    }
       

    // when it's Ord's turn
    // checks if input is in Ord's array
    if(OrdCount == 4 && !bTurn)
      bRemove = isValidOrdRemove(aOrd, cChoice);

    // executes only when Ord entered a valid input to remove
    if(bRemove && !bTurn)
    {
      removeOrd(&OrdCount, aOrd, board, copyOfBoard, cChoice);
      bRemove = 0;
    }

    if((!bValid && (bTurn || (!bTurn && OrdCount < 4))) || (!bTurn && OrdCount == 4 && !bRemove))
      printf("\n\n%44s", "INVALID CHOICE");
    
    bGame = GameOver(board);
  }
  
	system("cls"); //refreshes display
	displaySectorDashboard();
	displayOrdChaDashboard(aCha, ChaCount, aOrd, OrdCount);
	displayGameboard(board);

  if(bGame == 0) // Cha wins
    printf("\n\n%38s\n", "CHA WINS");

  if(bGame == 1)  // Ord wins
    printf("\n\n%38s\n", "ORD WINS");

	return 0;
}