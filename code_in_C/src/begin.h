#ifndef BEGIN_H
#define BEGIN_H
#include "structenum.h"
#include "../include/SDL.h"
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define BASEPOS 65
#define MSIZE 360
#define TOTAL 24
#define ANSI_COLOUR_RED "\x1b[31m"
#define ANSI_COLOUR_GREEN "\x1b[32m"
#define ANSI_COLOUR_YELLOW "\x1b[33m"
#define ANSI_COLOUR_BLUE "\x1b[34m"
#define ANSI_COLOUR_MAGENTA "\x1b[35m"
#define ANSI_COLOUR_CYAN "\x1b[36m"
#define ANSI_COLOUR_RESET "\x1b[0m"
extern const char Treasureset[25][20];
extern const char ANSI[5][8];
void SDL_ExitWithError(const char* message);
void SDL_ForceExit(SDL_Window*app,SDL_Renderer*rend);

int askNumber();
Player* createtable(int numPlayer);
Player* askName(Player* player,int numplayer);
void PrintfPlayerList(Player*player,int NumPlayer);
LOT * FillTreasureList();
void PrintRandomTreasureList(LOT* t);
Player* AttributePersonalListTreasure(LOT *t,Player* p,Gameboard g);
void PrintPlayersPersonalList(Player* p,Gameboard g);
void AnnounceTurn(Player* p, Gameboard g);
Player* LoadImagePlayer(char txt1[],char txt2[],char txt3[],Player* p, SDL_Renderer *r,int lctionOfNmbChnge1,int lctionOfNmbChnge2,int lctionOfNmbChnge3,Gameboard g);
Player* InitiatePlayerLogos(Player* p, SDL_Renderer *r, Gameboard g);
#endif