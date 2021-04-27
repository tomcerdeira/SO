#ifndef CHESS_GAME
#define CHESS_GAME

#include <chessPieces.h>
#include <libasm.h>
#include <standardLib.h>

#define PLAYER1_PRINT_X 120
#define PLAYER2_PRINT_X 880
#define PLAYER1_PRINT_Y 120
#define PLAYER2_PRINT_Y 120
#define TIMER_X 10
#define TIMER_Y 10
#define WINNER_COLOR 0xDEAD00

#define PLAYER1_COLOR 0x00FF00
#define PLAYER2_COLOR 0x995E30
#define ALLOWED_SECONDS 60000
#define LOOSER 0x101010

#define HEIGHT 8
#define WIDTH 8
#define BLACK_PIECE 0
#define WHITE_PIECE 1
#define EMPTY_CODE -1

typedef struct
{
    char firstMove;
    int color; // 0 = Negro | 1 = Blanco
    int pieceCode;
    char isActive; // si sigue en juego
    int posX;
    int posY; // posX, posY
    //char (*isvalidMovement)(piece *piecePointer, int toX, int toY); // ver el tema
} piece;

typedef struct
{
    piece matriz[HEIGHT][WIDTH];
    char up;
} tablero_type;

typedef struct
{
    piece pieceC;
    char from[5];
    char to[5];
    // posX, posY
} play;

typedef struct
{
    char name[20];
    int color;
    play historial[1024];
    int play_number;
    int time;
} player;

void initChess();
void drawPeon();
int positionIsFree(int toX, int toY);
int validPosition(int toX, int toY, int pieceColor);

char validPeonMovement(piece *piecePointer, int toX, int toY);
char validCaballoMovement(piece *piecePointer, int toX, int toY);
char validAlfilMovement(piece *piecePointer, int toX, int toY);
char validTorreMovement(piece *piecePointer, int toX, int toY);
char validReinaMovement(piece *piecePointer, int toX, int toY);
char validReyMovement(piece *piecePointer, int toX, int toY);
int validEnroque(piece piece, int toX, int toY);
void chessManager();
int isPossible(piece *piece, int coord_x, int coord_y);
void getMovement(char *from, char *to, int *exit);
int changeTurn();
void printHistoriales();
void reDrawTable();
void printCronometro();

int isNumberChess(char c);

int isLetterChess(char c);

int checkCorrectMovement(char *buffer, char *bufferFinal);
int makeMove(char *bufferInicial, char *bufferFinal);
#endif