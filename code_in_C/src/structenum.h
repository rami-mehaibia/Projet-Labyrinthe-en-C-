#ifndef STRUCTENUM_H
#define STRUCTENUM_H
#include "../include/SDL.h"

typedef enum {Ishaped, Lshaped, Tshaped}Shape;
//----------------

//----------------
typedef enum {Same, Left, Right, Inverse} Orientation;
//----------------
typedef enum {Nothing, Dacia, Gallia, Britannia, Hispania, Egypt, Mesopotamia, Babylonia, Tripolitania, Armenia, Dalmetia, Macedonia, Thrace, Assyria, Numidia, Mauretania, Moesia, Galatia, Judaea, Pannonia, Aquitania, Raetia, Corsica, Sicilia, Sardinia, Cyprus}LOT;
//----------------
typedef enum {Movable, Unmovable} TileStatus;
//***************
typedef enum {false,true} Bool;
//***************



//***************
typedef struct {
int x , y;
} position;



typedef struct  {
  LOT* personalListTreasures;
  char* Name;
  
  position positionPlayer;
  int treasurenumber; //aka we're at which treasure exactly rn ?
  int Maxtreasure; //the Max quantity of treasures this game...
  Bool AccessExit;
  Bool win;
  position positionExit;
  SDL_Rect point,rectforIn,rectforTr,rectforWin,rectforTurn,rectforSPQR;
  SDL_Texture *txt,*txtrforIn,*txtrforTr,*txtrforWin,*txtrforTurn,*txtrforSPQR;
  SDL_Surface *img,*srfcforIn,*srfcforTr,*srfcforWin,*srfcforTurn,*srfcforSPQR;
  
} Player;
//*********

typedef struct {
  Shape shape;
  Orientation orientation;
  int N,S,E,W; // north south east west  
  LOT treasure;
  TileStatus tilestatus;
  Bool OutOfBounds;
  
  Bool IsExit;
  
  position  positionOfTile;
  SDL_Rect rect;
  SDL_Surface *srfc;
  SDL_Texture *txtr;
}Tile;

//******

typedef struct {


Tile gameboard[7][7];

unsigned long turn ;//states the turn we're at...
int numplayer;
int insert;
int insertcoord;
int insertcoordinates[12];
int insertcheck[12];
int move;
int rotation;
int playerturn;
Tile Outside;
int treasureget;
int jukebox;
int testdebugmodethingy;
int quit;
int IBA,MBA,RBA;
} Gameboard;
//*********


#endif