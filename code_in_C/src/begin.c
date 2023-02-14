#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structenum.h"
#include "begin.h"
//the table of treasures to get
const char Treasureset[25][20]={"Exit","Dacia","Gallia","Britannia","Hispania","Egypt","Mesopotamia","Babylonia","Tripolitania","Armenia","Dalmetia","Macedonia","Thrace","Assyria","Numidia","Mauritania","Moesia","Galatia","Judaea","Panonia","Aquitannia","Raetia","Corsica","Sicilia","Sardinia"};
//the converter of colours table
const char ANSI[5][8]={ANSI_COLOUR_RED,ANSI_COLOUR_BLUE,ANSI_COLOUR_GREEN,ANSI_COLOUR_MAGENTA,ANSI_COLOUR_RESET};

//function that exits automatically if it is summoned (along with a message that you type out to know where it failed)
void SDL_ExitWithError(const char *message)
{
  SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
  SDL_Quit();
  exit(EXIT_FAILURE);
}
//function that forces exit with video in mind
void SDL_ForceExit(SDL_Window *app, SDL_Renderer *rend)
{
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(app);
}


//function that asks the number of players
int askNumber()
{

  int number;
 
  printf("How many players are you ?\n");
  fflush(stdout);
  scanf("%d", &number);
  while (number < 2 || number > 4)
  {
    printf("How many players are you (between 2 and 4) ?\n");
    fflush(stdout);
    scanf("%d", &number);
  }
  return number;
}

//function that creates the player data table
Player *createtable(int numPlayer)
{
  Player *players = (Player *)malloc(sizeof(Player) * numPlayer);
  return players;
}

//function that asks the name of the player and inputs it in the player data table
Player *askName(Player *player, int numplayer)
{
  //
  for (int i = 0; i < numplayer; i++)
  {
    player[i].Name = (char *)malloc(50);
    printf("%sWhat is player %d's name ?\n",ANSI[i], i + 1);
    fflush(stdout);
    scanf("%s", player[i].Name);
    if(i<numplayer-1)
      printf("%sAlright, next...\n",ANSI[4]);
    else
      printf("%sThank you for the names...\n",ANSI[4]);
  }

  return player;
}

//function that prints the player list
void PrintfPlayerList(Player *player, int NumPlayer)
{
  printf("Here is the list of Players\n");
  for (int i = 0; i < NumPlayer; i++)
  {
    printf("%sPlayer %d's Name : %s %s\n", ANSI[i],i + 1, player[i].Name,ANSI[4]);
  }
}

//function that makes a list of treasures in random order but each number is different to the previous one (in general)
LOT *FillTreasureList()
{
  srand(time(NULL));
  LOT base[TOTAL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
  LOT *treasures = (LOT *)malloc(TOTAL * sizeof(LOT));
  //printf("made table...\n");
  int k = rand() % 24;
  for (int i = 0; i < TOTAL; i++)
  {
    //printf("base of %d = %d\n",k,base[k]);
    while (base[k] == 0)
    {
      k = rand() % 24;
      //printf("redo\n");
    }
    //printf("base of %d = %d after while\n",k,base[k]);
    treasures[i] = base[k];
    base[k] = 0;
    k = rand() % 24;
  }
  return treasures;
}

//prints the random treasure list
void PrintRandomTreasureList(LOT *t)
{
  printf("[");
  for (int i = 0; i < TOTAL; i++)
  {
    if (i == TOTAL - 1)
      printf("%d]\n", t[i]);
    else
      printf("%d, ", t[i]);
  }
}

//Attributes an equal part of the main random treasure list (in order for each to not have the same treasure). For example if we have 2 players we give the first 12 treasures of the random treasure list to Player 1 and the other 12 to Player 2.
Player *AttributePersonalListTreasure(LOT *t, Player *p, Gameboard g)
{

  for (int i = 0; i < g.numplayer; i++)
  {
    p[i].Maxtreasure = TOTAL / g.numplayer;
    p[i].treasurenumber = 0;
    p[i].personalListTreasures = (LOT *)malloc((int)(TOTAL / g.numplayer) * sizeof(LOT));
    p[i].img = NULL;
    p[i].txt = NULL;
    p[i].srfcforTr = NULL;
    p[i].txtrforTr = NULL;
    p[i].srfcforIn = NULL;
    p[i].txtrforIn = NULL;
    p[i].win=0;

    for (int j = (int)(i * TOTAL / g.numplayer); j < (int)(i + 1) * TOTAL / g.numplayer; j++)
    {
      p[i].personalListTreasures[j - (i * TOTAL / g.numplayer)] = t[j];
      //printf("j=%d et [j]=%d et t[j]=%d\n",j,p[i].personalListTreasures[j-(i*TOTAL/g.numplayer)],t[j]);
    }
  }
  //we also at the same time place the players to their respective initial positions
  switch (g.numplayer)
  {
  case 2:
    p[0].positionPlayer.x = 0;
    p[0].positionPlayer.y = 0;
    p[1].positionPlayer.x = 6;
    p[1].positionPlayer.y = 0;

    p[0].positionExit.x = 0;
    p[0].positionExit.y = 0;
    p[1].positionExit.x = 6;
    p[1].positionExit.y = 0;

    break;
  case 3:
    p[0].positionPlayer.x = 0;
    p[0].positionPlayer.y = 0;
    p[1].positionPlayer.x = 6;
    p[1].positionPlayer.y = 0;
    p[2].positionPlayer.x = 6;
    p[2].positionPlayer.y = 6;

    p[0].positionExit.x = 0;
    p[0].positionExit.y = 0;
    p[1].positionExit.x = 6;
    p[1].positionExit.y = 0;
    p[2].positionExit.x = 6;
    p[2].positionExit.y = 6;

    break;
  case 4:
    p[0].positionPlayer.x = 0;
    p[0].positionPlayer.y = 0;
    p[1].positionPlayer.x = 6;
    p[1].positionPlayer.y = 0;
    p[2].positionPlayer.x = 6;
    p[2].positionPlayer.y = 6;
    p[3].positionPlayer.x = 0;
    p[3].positionPlayer.y = 6;

    p[0].positionExit.x = 0;
    p[0].positionExit.y = 0;
    p[1].positionExit.x = 6;
    p[1].positionExit.y = 0;
    p[2].positionExit.x = 6;
    p[2].positionExit.y = 6;
    p[3].positionExit.x = 0;
    p[3].positionExit.y = 6;
    break;
  default:
    break;
  }

  return p;
}
/*
printf("We're loading player 1's icon...\n");
    p[0]->img=SDL_LoadBMP("sprites\\1.bmp");
    
    if(p[0]->img==NULL){
      printf("It did not load here !\n");
    }
    printf("We're loading player 1's icon...\n");
    p[0]->txt=SDL_CreateTextureFromSurface(rend,p[0]->img);
    printf("We're loading player 1's icon...\n");
    SDL_FreeSurface(p[0]->img);
    printf("We're loading player 1's icon...\n");
    
    
    if(p[0]->txt==NULL){
      SDL_ExitWithError("Why though1...");
      return -1;
    }
    if(SDL_QueryTexture(p[0]->txt,NULL,NULL,&p[0]->point.w,&p[0]->point.h)!=0){
      SDL_ExitWithError("Why though2...");
      return -1;

    }
    p[0]->point.w*=0.5;
    p[0]->point.h*=0.5;
*/
//function that prints the players personal list of treasures.
void PrintPlayersPersonalList(Player *p, Gameboard g)
{ 
  for (int i = 0; i < g.numplayer; i++)
  {
    printf("%s%s's personal list :\n[",ANSI[i], p[i].Name);

    for (int j = 0; j < TOTAL / g.numplayer; j++)
    {
      
      if (j == TOTAL / g.numplayer - 1)
        printf("%s]%s\n", Treasureset[p[i].personalListTreasures[j]],ANSI[4]);
      else
        printf("%s, ", Treasureset[p[i].personalListTreasures[j]]);
    }
  }
}
//function that announces the player's turn
void AnnounceTurn(Player *p, Gameboard g)
{
  printf("It's %s's turn... if you want to end the turn... press Space bar !\n", p[g.playerturn].Name);
}

//failed function
Player *LoadImagePlayer(char txt1[], char txt2[], char txt3[], Player *p, SDL_Renderer *r, int lctionOfNmbChnge1, int lctionOfNmbChnge2, int lctionOfNmbChnge3, Gameboard g)
{
  for (int i = 0; i < g.numplayer; i++)
  {
    p[i].img = SDL_LoadBMP(txt1);
    if (p[i].img == NULL)
    {
      printf("Player %d's image did not load...\n", i + 1);
    }
    p[i].txt = SDL_CreateTextureFromSurface(r, p[i].img);
    SDL_FreeSurface(p[i].img);
    if (SDL_QueryTexture(p[i].txt, NULL, NULL, &p[i].point.w, &p[i].point.h) != 0)
    {
      SDL_ExitWithError("Why though2...");
    }
    p[i].point.w *= 0.6;
    p[i].point.h *= 0.6;
    printf("%sWe loaded Player %d's logo...%s\n",ANSI[i], i + 1,ANSI[4]);
    txt1[lctionOfNmbChnge1] += 1;

    p[i].srfcforTr = SDL_LoadBMP(txt2);
    printf("Did something load ?\n");
    if (p[i].srfcforTr == NULL)
    {
      printf("Player %d's Treasure image did not load...\n", i + 1);
    }
    p[i].txtrforTr = SDL_CreateTextureFromSurface(r, p[i].srfcforTr);
    SDL_FreeSurface(p[i].srfcforTr);
    if (SDL_QueryTexture(p[i].txtrforTr, NULL, NULL, &p[i].rectforTr.w, &p[i].rectforTr.h) != 0)
    {
      SDL_ExitWithError("Why though2...");
    }
    p[i].rectforTr.w *= 0.6;
    p[i].rectforTr.h *= 0.6;
    printf("%sWe loaded Player %d's Treasure Image...%s\n",ANSI[i], i + 1,ANSI[4]);
    txt2[lctionOfNmbChnge2] += 1;

    p[i].srfcforIn = SDL_LoadBMP(txt3);
    if (p[i].srfcforIn == NULL)
    {
      printf("Player %d's Insert image did not load...\n", i + 1);
    }
    p[i].txtrforIn = SDL_CreateTextureFromSurface(r, p[i].srfcforIn);
    SDL_FreeSurface(p[i].srfcforIn);
    if (SDL_QueryTexture(p[i].txtrforIn, NULL, NULL, &p[i].rectforIn.w, &p[i].rectforIn.h) != 0)
    {
      SDL_ExitWithError("Why though2...");
    }
    p[i].rectforIn.w *= 0.6;
    p[i].rectforIn.h *= 0.6;
    printf("%sWe loaded Player %d's Treasure Image...%s\n",ANSI[i], i + 1,ANSI[i]);
    txt3[lctionOfNmbChnge3] += 1;
  }
  return p;
}
//function that loads every image related to each player
Player *InitiatePlayerLogos(Player *p, SDL_Renderer *r, Gameboard g)
{
  char text[] = "sprites\\P1.bmp";
  char text2[] = "sprites\\Tr1.bmp";
  char text3[] = "sprites\\In1.bmp";
  char text4[]= "sprites\\P1win.bmp";
  char text5[]= "sprites\\P1turn.bmp";
  char text6[]= "sprites\\P1SPQR.bmp";
  for (int i = 0; i < g.numplayer; i++)
  {
    p[i].img = SDL_LoadBMP(text);
    if (p[i].img == NULL)
    {
      printf("Player %d's image did not load...\n", i + 1);
    }
    p[i].txt = SDL_CreateTextureFromSurface(r, p[i].img);
    SDL_FreeSurface(p[i].img);
    if (SDL_QueryTexture(p[i].txt, NULL, NULL, &p[i].point.w, &p[i].point.h) != 0)
    {
      SDL_ExitWithError("Why though2...");
    }
    p[i].point.w *= 0.6;
    p[i].point.h *= 0.6;
    printf("%sWe loaded Player %d's logo...%s\n",ANSI[i], i + 1,ANSI[4]);
    text[9] += 1;
    p[i].srfcforTr = SDL_LoadBMP(text2);
    if (p[i].srfcforTr == NULL)
    {
      printf("Player %d's Treasure image did not load...\n", i + 1);
    }
    p[i].txtrforTr = SDL_CreateTextureFromSurface(r, p[i].srfcforTr);
    SDL_FreeSurface(p[i].srfcforTr);
    if (SDL_QueryTexture(p[i].txtrforTr, NULL, NULL, &p[i].rectforTr.w, &p[i].rectforTr.h) != 0)
    {
      SDL_ExitWithError("Why though2...");
    }
    p[i].rectforTr.w *= 0.6;
    p[i].rectforTr.h *= 0.6;
    printf("%sWe loaded Player %d's Treasure Image...%s\n",ANSI[i], i + 1,ANSI[4]);
    text2[10] += 1;
    p[i].srfcforIn = SDL_LoadBMP(text3);
    if (p[i].srfcforIn == NULL)
    {
      printf("Player %d's Insert image did not load...\n", i + 1);
    }
    p[i].txtrforIn = SDL_CreateTextureFromSurface(r, p[i].srfcforIn);
    SDL_FreeSurface(p[i].srfcforIn);
    if (SDL_QueryTexture(p[i].txtrforIn, NULL, NULL, &p[i].rectforIn.w, &p[i].rectforIn.h) != 0)
    {
      SDL_ExitWithError("Why though2...");
    }
    p[i].rectforIn.w *= 0.6;
    p[i].rectforIn.h *= 0.6;
    printf("%sWe loaded Player %d's Insert Image...%s\n",ANSI[i], i + 1,ANSI[4]);
    text3[10] += 1;
    p[i].srfcforWin = SDL_LoadBMP(text4);
    if (p[i].srfcforWin == NULL)
    {
      printf("Player %d's Win did not load...\n", i + 1);
    }
    p[i].txtrforWin = SDL_CreateTextureFromSurface(r, p[i].srfcforWin);
    SDL_FreeSurface(p[i].srfcforWin);
    if (SDL_QueryTexture(p[i].txtrforWin, NULL, NULL, &p[i].rectforWin.w, &p[i].rectforWin.h) != 0)
    {
      SDL_ExitWithError("Why though2...");
    }
    p[i].rectforWin.x = 0;
    p[i].rectforWin.y = 0;
    printf("%sWe loaded Player %d's Win...%s\n",ANSI[i], i + 1,ANSI[4]);
    text4[9] += 1;
    p[i].srfcforTurn = SDL_LoadBMP(text5);
    if (p[i].srfcforTurn == NULL)
    {
      printf("Player %d's Turn did not load...\n", i + 1);
    }
    p[i].txtrforTurn = SDL_CreateTextureFromSurface(r, p[i].srfcforTurn);
    SDL_FreeSurface(p[i].srfcforTurn);
    if (SDL_QueryTexture(p[i].txtrforTurn, NULL, NULL, &p[i].rectforTurn.w, &p[i].rectforTurn.h) != 0)
    {
      SDL_ExitWithError("Why though2...");
    }
    p[i].rectforTurn.x = 0;
    p[i].rectforTurn.y = 500;
    p[i].rectforTurn.w*=0.6;
    p[i].rectforTurn.h*=0.5;
    printf("%sWe loaded Player %d's Turn...%s\n",ANSI[i], i + 1,ANSI[4]);
    text5[9] += 1;
    p[i].srfcforSPQR = SDL_LoadBMP(text6);
    if (p[i].srfcforSPQR == NULL)
    {
      printf("Player %d's SPQR did not load...\n", i + 1);
    }
    p[i].txtrforSPQR = SDL_CreateTextureFromSurface(r, p[i].srfcforSPQR);
    SDL_FreeSurface(p[i].srfcforSPQR);
    if (SDL_QueryTexture(p[i].txtrforSPQR, NULL, NULL, &p[i].rectforSPQR.w, &p[i].rectforSPQR.h) != 0)
    {
      SDL_ExitWithError("Why though3...");
    }
    //p[i].rectforSPQR.w=140;
    //p[i].rectforSPQR.h=1400;
    //printf("SPQR : %d %d\n",p[i].rectforSPQR.w,p[i].rectforSPQR.h);
    p[i].rectforSPQR.x = 560;
    p[i].rectforSPQR.y = 0;
    
    printf("%sWe loaded Player %d's SPQR...%s\n",ANSI[i], i + 1,ANSI[4]);
    text6[9] += 1;
  }

  //p=LoadImagePlayer("sprites\\P1.bmp","sprites\\Tr1.bmp","sprites\\In1.bmp",p,r,9,10,10,g); does not work
  switch (g.numplayer)
  {
  case 2:
    p[0].point.x = BASEPOS;
    p[0].point.y = BASEPOS;
    p[1].point.x = MSIZE + BASEPOS;
    p[1].point.y = BASEPOS;
    break;
  case 3:
    p[0].point.x = BASEPOS;
    p[0].point.y = BASEPOS;
    p[1].point.x = MSIZE + BASEPOS;
    p[1].point.y = BASEPOS;
    p[2].point.x = MSIZE + BASEPOS;
    p[2].point.y = MSIZE + BASEPOS;
    break;
  case 4:
    p[0].point.x = BASEPOS;
    p[0].point.y = BASEPOS;
    p[1].point.x = MSIZE + BASEPOS;
    p[1].point.y = BASEPOS;
    p[2].point.x = MSIZE + BASEPOS;
    p[2].point.y = MSIZE + BASEPOS;
    p[3].point.x = BASEPOS;
    p[3].point.y = MSIZE + BASEPOS;
    break;
  default:
    break;
  }
  return p;
}
