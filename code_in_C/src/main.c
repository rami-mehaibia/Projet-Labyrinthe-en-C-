#include "../include/SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../unity/src/unity.h"
#include "hello.h"
#include "structenum.h"
#include "begin.h"
#include "audio.h"
#include "middle.h"


#define FPS 33
#define DEG 360
#define TAILLE_Inspi 0.6

/*
SDL_RENDERER_SOFTWARE
SDL_RENDERER_ACCELERATED
SDL_RENDERER_PRESENTVSYNC
SDL_RENDERER_TARGETTEXTURE
add nothing
what
*/

//Test


int main(int argc, char *argv[])
{

  /*printf(    "%sThis text is RED!"     ANSI_COLOUR_RESET "\n",ANSI[0]);
  printf(ANSI_COLOUR_GREEN   "This text is GREEN!"   ANSI_COLOUR_RESET "\n");
  printf(ANSI_COLOUR_YELLOW  "This text is YELLOW!"  ANSI_COLOUR_RESET "\n");
  printf(ANSI_COLOUR_BLUE    "This text is BLUE!"    ANSI_COLOUR_RESET "\n");
  printf(ANSI_COLOUR_MAGENTA "This text is MAGENTA!" ANSI_COLOUR_RESET "\n");
  printf(ANSI_COLOUR_CYAN    "This text is CYAN!"    ANSI_COLOUR_RESET "\n");*/
  
  
  // Initialisation of everything :
  
  Gameboard g;
  Player *p;
  printf("Welcome to the Labyrinth Game\n");

  SDL_version test;
  SDL_VERSION(&test);
  SDL_Window *app = NULL;
  SDL_Renderer *rend = NULL;
  SDL_Surface *beginsrfc=SDL_LoadBMP("sprites\\Title_Screen_final.bmp");
  SDL_Texture *begintxtr=NULL;
  SDL_Rect beginrect;
  beginrect.x=0;
  beginrect.y=0;
    
  
  printf("Welcome to SDL version %d.%d.%d\n\n\nIn order to play the game here are the rules...:\nIf you want to rotate the piece in your hand, use the right and left arrow keys.\nWhen you are done, press 'I' to enter Insert mode (using the arrow keys) to insert the tile\nNext you press 'M' in order to enter Moving mode to move your piece\nOnce you moved your piece, end the turn by pressing 'Enter'\n\n\n", test.major, test.minor, test.patch);
  
  //Initialisation of SDL video and audio
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    SDL_ExitWithError("Initialision SDL");
  
  //Window creation
  app = SDL_CreateWindow("Labyrinth : The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (app == NULL)
    SDL_ExitWithError("Création de fenêtre échoué");
  
  
  rend = SDL_CreateRenderer(app, -1, SDL_RENDERER_SOFTWARE);
  
  if (rend == NULL)
    SDL_ExitWithError("Création rendu échouée");

  
  //Audio creation
  AudioShenanigans a;
  a.dvce=0;
  a.success=0;
  a.wavLength=0;
  a=AUDIOLOAAAAAD("sfx\\menu.wav",a);
  
  
  if (beginsrfc == NULL)
    {
        printf("Entry point did not load...\n");
    }
    begintxtr = SDL_CreateTextureFromSurface(rend, beginsrfc);
    if(begintxtr==NULL){
      printf("problème là !\n");
    }
    SDL_FreeSurface(beginsrfc);
    if (SDL_QueryTexture(begintxtr, NULL, NULL, &beginrect.w, &beginrect.h) != 0)
    {
        SDL_ExitWithError("Why though2...");
    }
  if(SDL_RenderCopy(rend,begintxtr,NULL,&beginrect)!=0){
    SDL_ExitWithError("Pas pu mettre l'écran de base...\n");
  }
  //Setting the window app icon, but it doesn't work 100% of the time
  SDL_Surface *windowappicon=SDL_LoadBMP("sprites\\player4.bmp");
  
  
  if(windowappicon==NULL){
    SDL_ExitWithError("Error d'icône\n");
  }
  SDL_SetWindowIcon(app,windowappicon);
  SDL_RenderPresent(rend);
  
  //Initialisation of every numerical variable that serve a purpose in the begining of the game
  g.treasureget=0;
  g.jukebox=0;
  
  g.turn = 0;
  g.IBA=1;
  g.MBA=0;
  g.RBA=0;
  //printf("Original turn = %d\n",gameboard->turn);
  int P1T=0,P2T=0,P3T=0,P4T=0,IBA=0,MBA=0,RBA=0;
  g.insert = 0;
  g.insertcoord = 0;
  g.move = 0;
  g.rotation = 0;
  
  g.playerturn = 0;
  
  g.quit=0;
  
  g.testdebugmodethingy=0;

  g.insertcoordinates[0] = 1;
  g.insertcoordinates[1] = 3;
  g.insertcoordinates[2] = 5;
  g.insertcoordinates[3] = 13;
  g.insertcoordinates[4] = 27;
  g.insertcoordinates[5] = 41;
  g.insertcoordinates[6] = 47;
  g.insertcoordinates[7] = 45;
  g.insertcoordinates[8] = 43;
  g.insertcoordinates[9] = 35;
  g.insertcoordinates[10] = 21;
  g.insertcoordinates[11] = 7;

  for (int i = 0; i < 12; i++)
  {
    g.insertcheck[i] = 0;
  }
  
    //Asking the players their number and names in order to begin the game
    g.numplayer = askNumber();
    g = createGameboard(g, rend);
    p = (Player *)malloc(g.numplayer * sizeof(Player));
    p = createtable(g.numplayer);
    p = askName(p, g.numplayer);
    PrintfPlayerList(p, g.numplayer);
    LOT *tr = FillTreasureList();

    //PrintRandomTreasureList(tr);
    //test
    p = AttributePersonalListTreasure(tr, p, g);
    PrintPlayersPersonalList(p, g);
    p = InitiatePlayerLogos(p, rend, g);
  
  SDL_bool prg_launch = SDL_TRUE;

  /* This was the first loading of a texture

  SDL_Surface *image=NULL;
  SDL_Texture *txtr=NULL;
  image=SDL_LoadBMP("sprites\\T.bmp");
  if(image==NULL){
    SDL_ForceExit(app,rend);
    SDL_ExitWithError("Impossible de charger l'image\n");
  }
  txtr=SDL_CreateTextureFromSurface(rend,image);
  SDL_FreeSurface(image);
  if(txtr==NULL){
    SDL_ForceExit(app,rend);
    SDL_ExitWithError("Impossible de charger l'image\n");
  }
  SDL_Rect rect2;
  if(SDL_QueryTexture(txtr,NULL,NULL,&rect2.w,&rect2.h)!=0){
    SDL_ForceExit(app,rend);
    SDL_ExitWithError("Impossible de charger l'image\n");
  }
  rect2.w*=TAILLE_Inspi;
  rect2.h*=TAILLE_Inspi;
  rect2.x=500;
  rect2.y=500;
  //(WINDOW_WIDTH-rect2.w/h)/2
  */
 
 
 //Setting up the window in order to play the game
  if (SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
    SDL_ExitWithError("Pas pu changer la couleur du rendu");
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = WINDOW_WIDTH;
  rect.h = WINDOW_HEIGHT;
  
  //Fill pour remplir et Draw pour dessiner contour
  if (SDL_RenderFillRect(rend, &rect) != 0)
  {
    SDL_ExitWithError("Pas pu dessiné un rectangle");
  }

  

  SDL_RenderPresent(rend);
  //SDL_Delay(10000);
  
  int stage = 0;
  printf("Number of players : %d\n", g.numplayer);
  if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
  {
    SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
  }
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (g.gameboard[i][j].txtr != NULL)
      {
        //printf("On peut load cette image... aux coordonnées : %d,%d et aux tailles : %d,%d\n",g.gameboard[i][j].rect.x,g.gameboard[i][j].rect.y,g.gameboard[i][j].rect.w,g.gameboard[i][j].rect.h);
        if (g.gameboard[i][j].IsExit == 1)
        {
          if (SDL_RenderCopy(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect))
          {
            SDL_ExitWithError("Problème d'initialisation des persos...\n");
          }
        }
        else
        {

          if (SDL_RenderCopyEx(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect, ConvertOrientationToDegrees(g.gameboard[i][j].orientation), NULL, SDL_FLIP_NONE) != 0)
          {
            SDL_ExitWithError("Problème de rotation\n");
          }
        }
      }
    }
  }
  for (int i = 0; i < g.numplayer; i++)
  {
    if (SDL_RenderCopy(rend, p[i].txt, NULL, &p[i].point))
    {
      SDL_ExitWithError("Problème d'initialisation des persos...\n");
    }
  }
  for (int i = 0; i < g.numplayer; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      for (int k = 0; k < 7; k++)
      {
        if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure && p[i].treasurenumber != p[i].Maxtreasure)
        {
          p[i].rectforTr.x = BASEPOS + 60 * k;
          p[i].rectforTr.y = BASEPOS + 60 * j;
          if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
          {
            SDL_ExitWithError("Problème pour dessiner les trésors\n");
          }
        }
      }
    }
  }
  SDL_DestroyTexture(begintxtr);
  printf("%s%s's turn.\nYou have to conquer %s !!!%s\n",ANSI[g.playerturn], p[g.playerturn].Name,Treasureset[p[g.playerturn].personalListTreasures[p[g.playerturn].treasurenumber]],ANSI[4]);
  
  
  
  
  
  //THE MAIN GAME LOOP !
  
  while (prg_launch)
  {
    //printf("prgrlnch=%d\n",prg_launch);
    SDL_Event event;
    if(SDL_RenderCopy(rend,p[g.playerturn].txtrforTurn,NULL,&p[g.playerturn].rectforTurn)!=0){
      SDL_ExitWithError("Erreur de tour...");
    }
    for(int i=0;i<g.numplayer;i++){
      if(p[i].treasurenumber<=p[i].Maxtreasure && p[i].treasurenumber>=0){
        p[i].rectforSPQR.y=- p[i].treasurenumber*700/p[i].Maxtreasure;
      }
    }
    if(SDL_RenderCopy(rend,p[g.playerturn].txtrforSPQR,NULL,&p[g.playerturn].rectforSPQR)!=0){
      SDL_ExitWithError("Erreur de SPQR...");
    }
    while (SDL_PollEvent(&event))
    {
      switch (event.type) //switch corresponding to the type of click you do
      {
      case SDL_MOUSEMOTION:
        //event.motion.x
        //printf("(%d,%d)\n",event.motion.x,event.motion.y);
        break;
      case SDL_MOUSEBUTTONDOWN: //Useless but left it here cause why not, it was experimentation
        /*
          SDL_BUTTON_LEFT
          SDL_BUTTON_MIDDLE
          SDL_BUTTON_RIGHT
          */

        printf("Click at this coordinate : (%d,%d)\n", event.button.x, event.button.y);
        if (stage == 0 && event.button.button == SDL_BUTTON_LEFT && event.button.x >= WINDOW_WIDTH / 2 - 100 && event.button.x <= WINDOW_WIDTH / 2 + 100 && event.button.y >= WINDOW_HEIGHT / 2 - 100 && event.button.y <= WINDOW_HEIGHT / 2 + 100)
        {
          printf("I left clicked in the middle !!!\n");
        }
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) // switch to determine which key you press
        {
        
        case SDLK_b: //Well even though you get rick rolled by pressing B, the thing is... it was the first audio that worked. At first it was also the first key that worked in general.
          printf("You pressed the B button ! Nice !\nYou got Rick Rolled !\n");
          a=AUDIOLOAAAAAD("sfx\\secret.wav",a);
          
          continue;
        case SDLK_j: //Jukebox mode
          if(g.jukebox==0){
            g.jukebox=1;
            printf("Jukebox activated !\n");
          }
          else{
            g.jukebox=0;
            printf("Jukebox deactivated !\n");
          }
          continue;
        case SDLK_d: //Debug mode
          
          if(g.testdebugmodethingy==0){
            g.testdebugmodethingy=1;
            printf("Debug/test mode activated !\n");
            IBA=g.IBA;
            MBA=g.MBA;
            RBA=g.RBA;
            switch(g.numplayer){
              case 2:
                P1T=p[0].treasurenumber;
                P2T=p[1].treasurenumber;
                break;
              case 3:
                P1T=p[0].treasurenumber;
                P2T=p[1].treasurenumber;
                P3T=p[2].treasurenumber;
                break;
              case 4:
                P1T=p[0].treasurenumber;
                P2T=p[1].treasurenumber;
                P3T=p[2].treasurenumber;
                P4T=p[3].treasurenumber;
                break;
              default:
                printf("erreur de nombre de joueurs...\n");
                break;
            }            
            printf("Everything has been saved !\n");
          }
          else{
            g.testdebugmodethingy=0;
            printf("Debug/test mode deactivated !\n");
            g.IBA=IBA;
            g.MBA=MBA;
            g.RBA=RBA;
            g.playerturn=g.turn%g.numplayer;
            switch(g.numplayer){
              case 2:
                p[0].treasurenumber=P1T;
                p[1].treasurenumber=P2T;
                break;
              case 3:
                p[0].treasurenumber=P1T;
                p[1].treasurenumber=P2T;
                p[2].treasurenumber=P3T;
                break;
              case 4:
                p[0].treasurenumber=P1T;
                p[1].treasurenumber=P2T;
                p[2].treasurenumber=P3T;
                p[3].treasurenumber=P4T;
                break;
              default:
                printf("erreur de nombre de joueurs...\n");
                break;
            }
            printf("Everything has been reestablished !\n");
          }
          continue;
        
        
        //Keys that work for the jukebox
        case SDLK_KP_0:
        case SDLK_0:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\menu.wav",a);
            printf("menu\n");
          }
          continue;
        case SDLK_KP_1:
        case SDLK_1:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\rotate.wav",a);
            printf("rotate\n");
          }
          continue;
        case SDLK_KP_2:
        case SDLK_2:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\insert_mode.wav",a);
            printf("insert_mode\n");
          }
          continue;
        case SDLK_KP_3:
        case SDLK_3:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\insert.wav",a);
            printf("insert\n");
          }
          continue;
        case SDLK_KP_4:
        case SDLK_4:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\moving_mode.wav",a);
            printf("moving_mode\n");
          }
          continue;
        case SDLK_KP_5:
        case SDLK_5:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\move.wav",a);
            printf("move\n");
          }
          continue;
        case SDLK_KP_6:
        case SDLK_6:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\endturn_mode.wav",a);
            printf("endturn_mode\n");
          }
          continue;
        case SDLK_KP_7:
        case SDLK_7:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\treasureget1.wav",a);
            printf("treasureget1\n");
          }
          continue;
        case SDLK_KP_8:
        case SDLK_8:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
            printf("treasureget2\n");
          }
          continue;
        case SDLK_KP_9:
        case SDLK_9:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\treasureget3.wav",a);
            printf("treasureget3\n");
          }
          continue;

        case SDLK_SPACE:
          if(g.jukebox==1){
            a=AUDIOLOAAAAAD("sfx\\end.wav",a);
            printf("end\n");
          }
          continue;
        
        case SDLK_p: //secret key for the teacher to press, an hommage to him and this wonderful project !
          if(g.jukebox==1 && g.testdebugmodethingy==1){
            a=AUDIOLOAAAAAD("sfx\\sweet_release_of_death.wav",a);
            printf("sweet_release_of_death also known as the End of the Trilogy of Phoenix Wright...\nThank you sir for this project... it was a blast !\n");
          }
          continue;

        


        // Keys for the Debug mode
        case SDLK_w: //Automatic random win (but only with the number of available players, you can't have Player 3 win in a 2 player game)
          if(g.testdebugmodethingy==1){
            srand(time(NULL));
            int random=rand()%g.numplayer;
            //printf("random = %d\n",random);
            p[random].win=1;
            printf("%s%s wins randomly in debug/test mode !!!%s\n",ANSI[random],p[random].Name,ANSI[4]);
            g.insert=2;
            g.move=2;

            prg_launch=SDL_FALSE;
          }
          
          break;
        case SDLK_KP_PLUS://To raise player's flag
          if(g.testdebugmodethingy==1){
            if(p[g.playerturn].treasurenumber<=p[g.playerturn].Maxtreasure){
              p[g.playerturn].treasurenumber++;
              printf("%sPlayer %d has now %d treasures...%s\n",ANSI[g.playerturn],g.playerturn+1,p[g.playerturn].treasurenumber,ANSI[4]);
            }
          }
          continue;
        case SDLK_KP_MINUS://To lower player's flag
          if(g.testdebugmodethingy==1){
            if(p[g.playerturn].treasurenumber>=0){
              p[g.playerturn].treasurenumber--;
              printf("%sPlayer %d has now %d treasures...%s\n",ANSI[g.playerturn],g.playerturn+1,p[g.playerturn].treasurenumber,ANSI[4]);
            }
          }
          continue;
        case SDLK_KP_MULTIPLY://Move turn up
          if(g.testdebugmodethingy==1){
            g.playerturn++;
            if(g.playerturn>=g.numplayer){
              g.playerturn=0;
            }
            printf("Player %d's turn\n",g.playerturn+1);
          }
          continue;
        case SDLK_KP_DIVIDE://Move turn down
          if(g.testdebugmodethingy==1){
            g.playerturn--;
            if(g.playerturn<0){
              g.playerturn=g.numplayer-1;
            }
            printf("Player %d's turn\n",g.playerturn+1);
          }
          continue;
        

        //Main Game buttons
        case SDLK_i://insert button
          
          if (g.move == 0 && g.IBA==1 && g.testdebugmodethingy==0)
          {
            a=AUDIOLOAAAAAD("sfx\\insert_mode.wav",a);
            printf("Insert mode engaged !\n");
            g.insert = 1;
            p[g.playerturn].rectforIn.x = BASEPOS + g.insertcoordinates[g.insertcoord] % 7 * 60;
            p[g.playerturn].rectforIn.y = 20 + g.insertcoordinates[g.insertcoord] / 7 * 60;
            if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
            {
              SDL_ExitWithError("Problème de cible insertion\n");
            }
            g.IBA=0;
            g.MBA=1;
          }
          continue;


        case SDLK_m://move button
          if (g.insert == 1 && g.move == 0 && g.MBA==1 && g.testdebugmodethingy==0)
          {
            //Updating everything
            
            if (g.insertcheck[g.insertcoord] == 0)
            {
              a=AUDIOLOAAAAAD("sfx\\moving_mode.wav",a);
              for (int i = 0; i < 12; i++)
              {
                g.insertcheck[i] = 0;
              }
              switch (g.insertcoord)
              {
              case 0:
                g.insertcheck[8] = 1;
                break;
              case 1:
                g.insertcheck[7] = 1;
                break;
              case 2:
                g.insertcheck[6] = 1;
                break;
              case 3:
                g.insertcheck[11] = 1;
                break;
              case 4:
                g.insertcheck[10] = 1;
                break;
              case 5:
                g.insertcheck[9] = 1;
                break;
              case 6:
                g.insertcheck[2] = 1;
                break;
              case 7:
                g.insertcheck[1] = 1;
                break;
              case 8:
                g.insertcheck[0] = 1;
                break;
              case 9:
                g.insertcheck[5] = 1;
                break;
              case 10:
                g.insertcheck[4] = 1;
                break;
              case 11:
                g.insertcheck[3] = 1;
                break;
              default:
                printf("Il y a eu une erreur pour la lecture de l'insertion...\n");
                break;
              }
              g.Outside.positionOfTile.x = g.insertcoordinates[g.insertcoord] % 7;
              g.Outside.positionOfTile.y = g.insertcoordinates[g.insertcoord] / 7;
              //printf("The new inside is %d %d\n", g.Outside.positionOfTile.x, g.Outside.positionOfTile.y);
              g.Outside.rect.x = 50 + 60 * g.Outside.positionOfTile.x;
              g.Outside.rect.y = 50 + 60 * g.Outside.positionOfTile.y;

              Tile tmp1, tmp2;

              if (g.Outside.positionOfTile.y == 0)
              {
                for(int i=0;i<g.numplayer;i++){
                  if(p[i].positionPlayer.x==g.Outside.positionOfTile.x){
                    if(p[i].positionPlayer.y<6){
                      p[i].positionPlayer.y++;
                      p[i].point.y+=60;
                    }
                    else{
                      p[i].positionPlayer.y=0;
                      p[i].point.y=BASEPOS;
                    }
                  }
                }
                for (int i = 0; i < 7; i++)
                {
                  if (i == 0)
                  {
                    tmp2 = g.gameboard[i][g.Outside.positionOfTile.x];
                    g.gameboard[i][g.Outside.positionOfTile.x] = g.Outside;
                    //printf("Accessiblity of piece : N=%d, S=%d, E=%d, W=%d after insertion\n", g.gameboard[i][g.Outside.positionOfTile.x].N, g.gameboard[i][g.Outside.positionOfTile.x].S, g.gameboard[i][g.Outside.positionOfTile.x].E, g.gameboard[i][g.Outside.positionOfTile.x].W);
                  }
                  else if (i == 6)
                  {
                    tmp1 = tmp2;
                    tmp2 = g.gameboard[i][g.Outside.positionOfTile.x];
                    g.gameboard[i][g.Outside.positionOfTile.x] = tmp1;
                    g.gameboard[i][g.Outside.positionOfTile.x].rect.y += 60;
                    g.Outside = tmp2;
                    g.Outside.positionOfTile.x = 7;
                    g.Outside.positionOfTile.y = 7;
                    g.Outside.rect.x = 500;
                    g.Outside.rect.y = 500;
                    g.Outside.orientation = Same;
                    g.Outside.N = 0;
                    g.Outside.S = 0;
                    g.Outside.E = 0;
                    g.Outside.W = 0;
                  }
                  else
                  {
                    tmp1 = tmp2;
                    tmp2 = g.gameboard[i][g.Outside.positionOfTile.x];
                    g.gameboard[i][g.Outside.positionOfTile.x] = tmp1;
                    g.gameboard[i][g.Outside.positionOfTile.x].rect.y += 60;
                    g.gameboard[i][g.Outside.positionOfTile.x].positionOfTile.y++;
                  }
                }                
              }
              
              if (g.Outside.positionOfTile.y == 6)
              {
                for(int i=0;i<g.numplayer;i++){
                  if(p[i].positionPlayer.x==g.Outside.positionOfTile.x){
                    if(p[i].positionPlayer.y>0){
                      p[i].positionPlayer.y--;
                      p[i].point.y-=60;
                    }
                    else{
                      p[i].positionPlayer.y=6;
                      p[i].point.y=BASEPOS+DEG;
                    }
                  }
                }
                for (int i = 6; i >= 0; i--)
                {
                  if (i == 6)
                  {
                    tmp2 = g.gameboard[i][g.Outside.positionOfTile.x];
                    g.gameboard[i][g.Outside.positionOfTile.x] = g.Outside;
                    //printf("Accessiblity of piece : N=%d, S=%d, E=%d, W=%d after insertion\n", g.gameboard[i][g.Outside.positionOfTile.x].N, g.gameboard[i][g.Outside.positionOfTile.x].S, g.gameboard[i][g.Outside.positionOfTile.x].E, g.gameboard[i][g.Outside.positionOfTile.x].W);
                  }
                  else if (i == 0)
                  {
                    tmp1 = tmp2;
                    tmp2 = g.gameboard[i][g.Outside.positionOfTile.x];
                    g.gameboard[i][g.Outside.positionOfTile.x] = tmp1;
                    g.gameboard[i][g.Outside.positionOfTile.x].rect.y -= 60;
                    g.Outside = tmp2;
                    g.Outside.positionOfTile.x = 7;
                    g.Outside.positionOfTile.y = 7;
                    g.Outside.rect.x = 500;
                    g.Outside.rect.y = 500;
                    g.Outside.orientation = Same;
                    g.Outside.N = 0;
                    g.Outside.S = 0;
                    g.Outside.E = 0;
                    g.Outside.W = 0;
                  }
                  else
                  {
                    tmp1 = tmp2;
                    tmp2 = g.gameboard[i][g.Outside.positionOfTile.x];
                    g.gameboard[i][g.Outside.positionOfTile.x] = tmp1;
                    g.gameboard[i][g.Outside.positionOfTile.x].rect.y -= 60;
                    g.gameboard[i][g.Outside.positionOfTile.x].positionOfTile.y--;
                  }
                }
              }
              
              if (g.Outside.positionOfTile.x == 0)
              {
                for(int i=0;i<g.numplayer;i++){
                  if(p[i].positionPlayer.y==g.Outside.positionOfTile.y){
                    if(p[i].positionPlayer.x<6){
                      p[i].positionPlayer.x++;
                      p[i].point.x+=60;
                    }
                    else{
                      p[i].positionPlayer.x=0;
                      p[i].point.x=BASEPOS;
                    }
                  }
                }
                for (int i = 0; i < 7; i++)
                {
                  if (i == 0)
                  {
                    tmp2 = g.gameboard[g.Outside.positionOfTile.y][i];
                    g.gameboard[g.Outside.positionOfTile.y][i] = g.Outside;
                    //printf("Accessiblity of piece : N=%d, S=%d, E=%d, W=%d after insertion\n", g.gameboard[g.Outside.positionOfTile.y][i].N, g.gameboard[g.Outside.positionOfTile.y][i].S, g.gameboard[g.Outside.positionOfTile.y][i].E, g.gameboard[g.Outside.positionOfTile.y][i].W);
                  }
                  else if (i == 6)
                  {
                    tmp1 = tmp2;
                    tmp2 = g.gameboard[g.Outside.positionOfTile.y][i];
                    g.gameboard[g.Outside.positionOfTile.y][i] = tmp1;
                    g.gameboard[g.Outside.positionOfTile.y][i].rect.x += 60;
                    g.Outside = tmp2;
                    g.Outside.positionOfTile.x = 7;
                    g.Outside.positionOfTile.y = 7;
                    g.Outside.rect.x = 500;
                    g.Outside.rect.y = 500;
                    g.Outside.orientation = Same;
                    g.Outside.N = 0;
                    g.Outside.S = 0;
                    g.Outside.E = 0;
                    g.Outside.W = 0;
                  }
                  else
                  {
                    tmp1 = tmp2;
                    tmp2 = g.gameboard[g.Outside.positionOfTile.y][i];
                    g.gameboard[g.Outside.positionOfTile.y][i] = tmp1;
                    g.gameboard[g.Outside.positionOfTile.y][i].rect.x += 60;
                    g.gameboard[g.Outside.positionOfTile.y][i].positionOfTile.y++;
                  }
                }
              }
              if (g.Outside.positionOfTile.x == 6)
              {
                for(int i=0;i<g.numplayer;i++){
                  if(p[i].positionPlayer.y==g.Outside.positionOfTile.y){
                    if(p[i].positionPlayer.x>0){
                      p[i].positionPlayer.x--;
                      p[i].point.x-=60;
                    }
                    else{
                      p[i].positionPlayer.x=6;
                      p[i].point.x=BASEPOS+DEG;
                    }
                  }
                }
                for (int i = 6; i >= 0; i--)
                {
                  if (i == 6)
                  {
                    tmp2 = g.gameboard[g.Outside.positionOfTile.y][i];
                    g.gameboard[g.Outside.positionOfTile.y][i] = g.Outside;
                    //printf("Accessiblity of piece : N=%d, S=%d, E=%d, W=%d after insertion\n", g.gameboard[g.Outside.positionOfTile.y][i].N, g.gameboard[g.Outside.positionOfTile.y][i].S, g.gameboard[g.Outside.positionOfTile.y][i].E, g.gameboard[g.Outside.positionOfTile.y][i].W);
                  }
                  else if (i == 0)
                  {
                    tmp1 = tmp2;
                    tmp2 = g.gameboard[g.Outside.positionOfTile.y][i];
                    g.gameboard[g.Outside.positionOfTile.y][i] = tmp1;
                    g.gameboard[g.Outside.positionOfTile.y][i].rect.x -= 60;
                    g.Outside = tmp2;
                    g.Outside.positionOfTile.x = 7;
                    g.Outside.positionOfTile.y = 7;
                    g.Outside.rect.x = 500;
                    g.Outside.rect.y = 500;
                    g.Outside.orientation = Same;
                    g.Outside.N = 0;
                    g.Outside.S = 0;
                    g.Outside.E = 0;
                    g.Outside.W = 0;
                  }
                  else
                  {
                    tmp1 = tmp2;
                    tmp2 = g.gameboard[g.Outside.positionOfTile.y][i];
                    g.gameboard[g.Outside.positionOfTile.y][i] = tmp1;
                    g.gameboard[g.Outside.positionOfTile.y][i].rect.x -= 60;
                    g.gameboard[g.Outside.positionOfTile.y][i].positionOfTile.y--;
                  }
                }
              }
              
              switch (g.Outside.shape)
              {
              case Ishaped:
                g.Outside.N = 1;
                g.Outside.S = 1;
                g.Outside.E = 0;
                g.Outside.W = 0;
                
                break;
              case Lshaped:
                g.Outside.N = 1;
                g.Outside.S = 0;
                g.Outside.E = 1;
                g.Outside.W = 0;
                
                break;
              case Tshaped:
                g.Outside.N = 0;
                g.Outside.S = 1;
                g.Outside.E = 1;
                g.Outside.W = 1;
                
                break;
              default:
                printf("There has been an error in the loading of the tile Outside...\n");
                break;
              }
              printf("Moving mode engaged !\n");
              g.move = 1;
              g.insertcoord = 0;
              if (SDL_RenderFillRect(rend, &rect) != 0)
              {
                SDL_ExitWithError("Pas pu dessiné un rectangle");
              }
              if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
              {
                SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
              }
              for (int i = 0; i < 7; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  if (g.gameboard[i][j].txtr != NULL)
                  {
                    //printf("On peut load cette image... aux coordonnées : %d,%d et aux tailles : %d,%d\n",g.gameboard[i][j].rect.x,g.gameboard[i][j].rect.y,g.gameboard[i][j].rect.w,g.gameboard[i][j].rect.h);
                    if (g.gameboard[i][j].IsExit == 1)
                    {
                      if (SDL_RenderCopy(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect))
                      {
                        SDL_ExitWithError("Problème d'initialisation des persos...\n");
                      }
                    }
                    else
                    {

                      if (SDL_RenderCopyEx(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect, ConvertOrientationToDegrees(g.gameboard[i][j].orientation), NULL, SDL_FLIP_NONE) != 0)
                      {
                        SDL_ExitWithError("Problème de rotation\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (SDL_RenderCopy(rend, p[i].txt, NULL, &p[i].point))
                {
                  SDL_ExitWithError("Problème pour dessiner les autres joueurs\n");
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  for (int k = 0; k < 7; k++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                      {
                        if (p[i].positionPlayer.x == g.gameboard[j][k].positionOfTile.x && p[i].positionPlayer.y == g.gameboard[j][k].positionOfTile.y)
                        {
                          p[i].treasurenumber++;
                          //printf("\nTreasure updated for %s\n\n",p[i].Name);
                        }
                        p[i].rectforTr.x = BASEPOS + 60 * k;
                        p[i].rectforTr.y = BASEPOS + 60 * j;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (p[i].treasurenumber < p[i].Maxtreasure)
                {
                  if (p[i].personalListTreasures[p[i].treasurenumber] == g.Outside.treasure)
                  {
                    p[i].rectforTr.x = 515;
                    p[i].rectforTr.y = 515;
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner les trésors\n");
                    }
                  }
                }
              }
            g.MBA=0;
            g.RBA=1;
            }
            
            else
            {
              a=AUDIOLOAAAAAD("sfx\\error.wav",a);
              printf("Moving mode not engaged because %s is doing the same insert as the one before him or her but in reverse...\n", p[g.playerturn].Name);
              g.MBA=1;
              g.RBA=0;
            }
            
            
          }
          continue;
        
        case SDLK_RETURN://ending turn button
          //printf("You pressed ENTER...\n");
          if (g.insert == 1 && g.move == 1 && g.RBA==1 && g.testdebugmodethingy==0)
          {
            a=AUDIOLOAAAAAD("sfx\\endturn_mode.wav",a);
            g.turn++;
            printf("Turn number %d done...\n", g.turn);
            g.insert = 0;
            g.move = 0;
            g.rotation = 0;
            g.playerturn = g.turn % g.numplayer;
            if(p[g.playerturn].treasurenumber<p[g.playerturn].Maxtreasure){
              printf("%s%s's turn.\nYou have to conquer %s !!!%s\n",ANSI[g.playerturn], p[g.playerturn].Name,Treasureset[p[g.playerturn].personalListTreasures[p[g.playerturn].treasurenumber]],ANSI[4]);
            }
            else{
              printf("%s%s's turn.\nNow go back home to tell your tale !!%s\n",ANSI[g.playerturn], p[g.playerturn].Name,ANSI[4]);
            }
            //AnnounceTurn(p,g);
            g.RBA=0;
            g.IBA=1;
          }
          continue;

//***********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
        case SDLK_UP://Up key usage
          if (g.move == 1 && g.testdebugmodethingy==0)//when we're moving
          {
            g.treasureget=0;
            if (p[g.playerturn].positionPlayer.y > 0 && g.gameboard[p[g.playerturn].positionPlayer.y][p[g.playerturn].positionPlayer.x].N == 1 && g.gameboard[p[g.playerturn].positionPlayer.y - 1][p[g.playerturn].positionPlayer.x].S == 1)
            {
              p[g.playerturn].positionPlayer.y--;
              if (SDL_RenderFillRect(rend, &rect) != 0)
              {
                SDL_ExitWithError("Pas pu dessiné un rectangle");
              }
              if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
              {
                SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
              }
              for (int i = 0; i < 7; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  if (g.gameboard[i][j].txtr != NULL)
                  {
                    //printf("On peut load cette image... aux coordonnées : %d,%d et aux tailles : %d,%d\n",g.gameboard[i][j].rect.x,g.gameboard[i][j].rect.y,g.gameboard[i][j].rect.w,g.gameboard[i][j].rect.h);
                    if (g.gameboard[i][j].IsExit == 1)
                    {
                      if (SDL_RenderCopy(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect))
                      {
                        SDL_ExitWithError("Problème d'initialisation des persos...\n");
                      }
                    }
                    else
                    {

                      if (SDL_RenderCopyEx(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect, ConvertOrientationToDegrees(g.gameboard[i][j].orientation), NULL, SDL_FLIP_NONE) != 0)
                      {
                        SDL_ExitWithError("Problème de rotation\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (i != g.playerturn)
                {
                  if (SDL_RenderCopy(rend, p[i].txt, NULL, &p[i].point))
                  {
                    SDL_ExitWithError("Problème pour dessiner les autres joueurs\n");
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 6; j >= 0; j--)
                {
                  for (int k = 0; k < 7; k++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                      {
                        if (p[i].positionPlayer.x == k && p[i].positionPlayer.y == j)
                        {
                          p[i].treasurenumber++;
                          g.treasureget=1;
                          printf("%sYou have now %d land(s) left to conquer !%s\n",ANSI[i],p[i].Maxtreasure-p[i].treasurenumber,ANSI[4]);
                          if(p[i].treasurenumber<p[i].Maxtreasure/3){
                            a=AUDIOLOAAAAAD("sfx\\treasureget1.wav",a);
                          }
                          if(p[i].treasurenumber>=p[i].Maxtreasure/3 && p[i].treasurenumber<2*p[i].Maxtreasure/3){
                            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
                          }
                          if(p[i].treasurenumber>=2*p[i].Maxtreasure/3 && p[i].treasurenumber<=p[i].Maxtreasure){
                            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
                          }
                          //printf("\nTreasure updated for %s on the UP motion\n\n",p[i].Name);
                        }
                        p[i].rectforTr.x = BASEPOS + 60 * k;
                        p[i].rectforTr.y = BASEPOS + 60 * j;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 6; j >= 0; j--)
                {
                  for (int k = 0; k < 7; k++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                      {
                        
                        p[i].rectforTr.x = BASEPOS + 60 * k;
                        p[i].rectforTr.y = BASEPOS + 60 * j;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (p[i].treasurenumber < p[i].Maxtreasure)
                {
                  if (p[i].personalListTreasures[p[i].treasurenumber] == g.Outside.treasure)
                  {
                    p[i].rectforTr.x = 515;
                    p[i].rectforTr.y = 515;
                    //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,g.Outside.positionOfTile.x,g.Outside.positionOfTile.y);
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner les trésors\n");
                    }
                  }
                }
                else{
                  //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                }
              }
              p[g.playerturn].point.y -= 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txt, NULL, &p[g.playerturn].point))
              {
                SDL_ExitWithError("Problème d'aller vers le haut\n");
              }
              //printf("%s moves UP\nX position = %d, Y position=%d\n", p[g.playerturn].Name, p[g.playerturn].positionPlayer.x, p[g.playerturn].positionPlayer.y);
              if(g.treasureget==0){
                a=AUDIOLOAAAAAD("sfx\\move.wav",a);
              }
            }
            for(int i=0;i<g.numplayer;i++){
              if(p[i].treasurenumber==p[i].Maxtreasure){
                if(p[i].positionPlayer.x==p[i].positionExit.x && p[i].positionPlayer.y==p[i].positionExit.y){
                  printf("%s%s WON THE LABYRINTH GAME !!!%s\n",ANSI[i],p[i].Name,ANSI[4]);
                  p[i].win=1;
                  g.insert=2;
                  g.move=2;
                  prg_launch=SDL_FALSE;
                }
              }
            }
          }
          continue;
//***********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
        case SDLK_DOWN://Down key usage
          if (g.move == 1 && g.testdebugmodethingy==0)//when we're moving
          {
            g.treasureget=0;            
            if (p[g.playerturn].positionPlayer.y < 6 && g.gameboard[p[g.playerturn].positionPlayer.y][p[g.playerturn].positionPlayer.x].S == 1 && g.gameboard[p[g.playerturn].positionPlayer.y + 1][p[g.playerturn].positionPlayer.x].N == 1)
            {
              p[g.playerturn].positionPlayer.y++;
              if (SDL_RenderFillRect(rend, &rect) != 0)
              {
                SDL_ExitWithError("Pas pu dessiné un rectangle");
              }
              if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
              {
                SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
              }
              for (int i = 0; i < 7; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  if (g.gameboard[i][j].txtr != NULL)
                  {
                    //printf("On peut load cette image... aux coordonnées : %d,%d et aux tailles : %d,%d\n",g.gameboard[i][j].rect.x,g.gameboard[i][j].rect.y,g.gameboard[i][j].rect.w,g.gameboard[i][j].rect.h);
                    if (g.gameboard[i][j].IsExit == 1)
                    {
                      if (SDL_RenderCopy(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect))
                      {
                        SDL_ExitWithError("Problème d'initialisation des persos...\n");
                      }
                    }
                    else
                    {

                      if (SDL_RenderCopyEx(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect, ConvertOrientationToDegrees(g.gameboard[i][j].orientation), NULL, SDL_FLIP_NONE) != 0)
                      {
                        SDL_ExitWithError("Problème de rotation\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (i != g.playerturn)
                {
                  if (SDL_RenderCopy(rend, p[i].txt, NULL, &p[i].point))
                  {
                    SDL_ExitWithError("Problème pour dessiner les autres joueurs\n");
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  for (int k = 0; k < 7; k++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                      {
                        if (p[i].positionPlayer.x == k && p[i].positionPlayer.y == j)
                        {
                          p[i].treasurenumber++;
                          g.treasureget=1;
                          printf("%sYou have now %d land(s) left to conquer !%s\n",ANSI[i],p[i].Maxtreasure-p[i].treasurenumber,ANSI[4]);
                          if(p[i].treasurenumber<p[i].Maxtreasure/3){
                            a=AUDIOLOAAAAAD("sfx\\treasureget1.wav",a);
                          }
                          if(p[i].treasurenumber>=p[i].Maxtreasure/3 && p[i].treasurenumber<2*p[i].Maxtreasure/3){
                            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
                          }
                          if(p[i].treasurenumber>=2*p[i].Maxtreasure/3 && p[i].treasurenumber<=p[i].Maxtreasure){
                            
                            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
                          }
                          //printf("\nTreasure updated for %s on the DOWN position\n\n",p[i].Name);
                        }
                        p[i].rectforTr.x = BASEPOS + 60 * k;
                        p[i].rectforTr.y = BASEPOS + 60 * j;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  for (int k = 0; k < 7; k++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                      {
                        
                        p[i].rectforTr.x = BASEPOS + 60 * k;
                        p[i].rectforTr.y = BASEPOS + 60 * j;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (p[i].treasurenumber < p[i].Maxtreasure)
                {
                  if (p[i].personalListTreasures[p[i].treasurenumber] == g.Outside.treasure)
                  {
                    p[i].rectforTr.x = 515;
                    p[i].rectforTr.y = 515;
                    //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,g.Outside.positionOfTile.x,g.Outside.positionOfTile.y);
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner les trésors\n");
                    }
                  }
                }
                else{
                  //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                }
              }
              p[g.playerturn].point.y += 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txt, NULL, &p[g.playerturn].point))
              {
                SDL_ExitWithError("Problème d'aller vers le bas\n");
              }
              //printf("%s moves DOWN\nX position = %d, Y position=%d\n", p[g.playerturn].Name, p[g.playerturn].positionPlayer.x, p[g.playerturn].positionPlayer.y);
              if(g.treasureget==0){
                a=AUDIOLOAAAAAD("sfx\\move.wav",a);
              }
            }
            for(int i=0;i<g.numplayer;i++){
              if(p[i].treasurenumber==p[i].Maxtreasure){
                if(p[i].positionPlayer.x==p[i].positionExit.x && p[i].positionPlayer.y==p[i].positionExit.y){
                  printf("%s%s WON THE LABYRINTH GAME !!!%s\n",ANSI[i],p[i].Name,ANSI[4]);
                  p[i].win=1;
                  g.insert=2;
                  g.move=2;
                  prg_launch=SDL_FALSE;
                }
              }
            }
          }
          continue;
//***********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
        case SDLK_LEFT://Left key usage
          if (g.move == 1 && g.testdebugmodethingy==0)//when we're moving
          {
            g.treasureget=0;
            if (p[g.playerturn].positionPlayer.x > 0 && g.gameboard[p[g.playerturn].positionPlayer.y][p[g.playerturn].positionPlayer.x].W == 1 && g.gameboard[p[g.playerturn].positionPlayer.y][p[g.playerturn].positionPlayer.x - 1].E == 1)
            {
              p[g.playerturn].positionPlayer.x--;
              if (SDL_RenderFillRect(rend, &rect) != 0)
              {
                SDL_ExitWithError("Pas pu dessiné un rectangle");
              }
              if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
              {
                SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
              }
              for (int i = 0; i < 7; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  if (g.gameboard[i][j].txtr != NULL)
                  {
                    //printf("On peut load cette image... aux coordonnées : %d,%d et aux tailles : %d,%d\n",g.gameboard[i][j].rect.x,g.gameboard[i][j].rect.y,g.gameboard[i][j].rect.w,g.gameboard[i][j].rect.h);
                    if (g.gameboard[i][j].IsExit == 1)
                    {
                      if (SDL_RenderCopy(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect))
                      {
                        SDL_ExitWithError("Problème d'initialisation des persos...\n");
                      }
                    }
                    else
                    {

                      if (SDL_RenderCopyEx(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect, ConvertOrientationToDegrees(g.gameboard[i][j].orientation), NULL, SDL_FLIP_NONE) != 0)
                      {
                        SDL_ExitWithError("Problème de rotation\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (i != g.playerturn)
                {
                  if (SDL_RenderCopy(rend, p[i].txt, NULL, &p[i].point))
                  {
                    SDL_ExitWithError("Problème pour dessiner les autres joueurs\n");
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 6; j >= 0; j--)
                {
                  for (int k = 0; k < 7; k++)
                  {

                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[k][j].treasure)
                      {
                        if (p[i].positionPlayer.x == j && p[i].positionPlayer.y == k)
                        {
                          p[i].treasurenumber++;
                          g.treasureget=1;
                          printf("%sYou have now %d land(s) left to conquer !%s\n",ANSI[i],p[i].Maxtreasure-p[i].treasurenumber,ANSI[4]);
                          if(p[i].treasurenumber<p[i].Maxtreasure/3){
                            a=AUDIOLOAAAAAD("sfx\\treasureget1.wav",a);
                          }
                          if(p[i].treasurenumber>=p[i].Maxtreasure/3 && p[i].treasurenumber<2*p[i].Maxtreasure/3){
                            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
                          }
                          if(p[i].treasurenumber>=2*p[i].Maxtreasure/3 && p[i].treasurenumber<=p[i].Maxtreasure){
                            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
                          }
                          //printf("\nTreasure updated for %s on the LEFT position\n\n",p[i].Name);
                        }
                        p[i].rectforTr.x = BASEPOS + 60 * j;
                        p[i].rectforTr.y = BASEPOS + 60 * k;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 6; j >= 0; j--)
                {
                  for (int k = 0; k < 7; k++)
                  {

                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[k][j].treasure)
                      {
                        
                        p[i].rectforTr.x = BASEPOS + 60 * j;
                        p[i].rectforTr.y = BASEPOS + 60 * k;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (p[i].treasurenumber < p[i].Maxtreasure)
                {
                  if (p[i].personalListTreasures[p[i].treasurenumber] == g.Outside.treasure)
                  {
                    p[i].rectforTr.x = 515;
                    p[i].rectforTr.y = 515;
                    //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,g.Outside.positionOfTile.x,g.Outside.positionOfTile.y);
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner les trésors\n");
                    }
                  }
                }
                else{
                  //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                }
              }
              p[g.playerturn].point.x -= 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txt, NULL, &p[g.playerturn].point))
              {
                SDL_ExitWithError("Problème d'aller vers la gauche\n");
              }
              //printf("%s moves LEFT\nX position = %d, Y position=%d\n", p[g.playerturn].Name, p[g.playerturn].positionPlayer.x, p[g.playerturn].positionPlayer.y);
              if(g.treasureget==0){
                a=AUDIOLOAAAAAD("sfx\\move.wav",a);
              }
            }
            for(int i=0;i<g.numplayer;i++){
              if(p[i].treasurenumber==p[i].Maxtreasure){
                if(p[i].positionPlayer.x==p[i].positionExit.x && p[i].positionPlayer.y==p[i].positionExit.y){
                  printf("%s%s WON THE LABYRINTH GAME !!!%s\n",ANSI[i],p[i].Name,ANSI[4]);
                  p[i].win=1;
                  g.insert=2;
                  g.move=2;
                  prg_launch=SDL_FALSE;
                }
              }
            }
          }
          if (g.insert == 0 && g.move == 0 && g.testdebugmodethingy==0)//when we're rotating the tile
          {
            a=AUDIOLOAAAAAD("sfx\\rotate.wav",a);
            g.rotation -= 90;
            if (g.rotation < 0)
            {
              g.rotation = 270;
            }
            g.Outside.orientation = ConvertDegreesToOrientation(g.rotation);
            switch (g.Outside.shape)
            {
            case Ishaped:
              switch (g.Outside.orientation)
              {
              case Same:
              case Inverse:
                g.Outside.N = 1;
                g.Outside.S = 1;
                g.Outside.E = 0;
                g.Outside.W = 0;
                break;
              case Right:
              case Left:
                g.Outside.N = 0;
                g.Outside.S = 0;
                g.Outside.E = 1;
                g.Outside.W = 1;
                break;
              default:
                printf("Error in I shaped territory of orientation...\n");
                break;
              }
              break;
            case Lshaped:
              switch (g.Outside.orientation)
              {
              case Same:
                g.Outside.N = 1;
                g.Outside.S = 0;
                g.Outside.E = 1;
                g.Outside.W = 0;
                break;
              case Right:
                g.Outside.N = 0;
                g.Outside.S = 1;
                g.Outside.E = 1;
                g.Outside.W = 0;
                break;
              case Inverse:
                g.Outside.N = 0;
                g.Outside.S = 1;
                g.Outside.E = 0;
                g.Outside.W = 1;
                break;
              case Left:
                g.Outside.N = 1;
                g.Outside.S = 0;
                g.Outside.E = 0;
                g.Outside.W = 1;
                break;
              default:
                printf("Error in L shaped territory of orientation...\n");
                break;
              }
              break;
            case Tshaped:
              switch (g.Outside.orientation)
              {
              case Same:
                g.Outside.N = 0;
                g.Outside.S = 1;
                g.Outside.E = 1;
                g.Outside.W = 1;
                break;
              case Right:
                g.Outside.N = 1;
                g.Outside.S = 1;
                g.Outside.E = 0;
                g.Outside.W = 1;
                break;
              case Inverse:
                g.Outside.N = 1;
                g.Outside.S = 0;
                g.Outside.E = 1;
                g.Outside.W = 1;
                break;
              case Left:
                g.Outside.N = 1;
                g.Outside.S = 1;
                g.Outside.E = 1;
                g.Outside.W = 0;
                break;
              default:
                printf("Error in T shaped territory of orientation...\n");
                break;
              }
              break;
            default:
              printf("There has been an error...\n");
              break;
            }
            //printf("Accessiblity of piece : N=%d, S=%d, E=%d, W=%d\n", g.Outside.N, g.Outside.S, g.Outside.E, g.Outside.W);
            if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
            {
              SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
            }
            /*
                if(SDL_RenderCopyEx(rend,txtr,NULL,&rect2,g.rotation,NULL,SDL_FLIP_NONE)!=0){
                  SDL_ExitWithError("Problème de rotation\n");
                }*/
            for (int i=0;i<g.numplayer;i++){
               if(p[i].treasurenumber<p[i].Maxtreasure){
                 if(p[i].personalListTreasures[p[i].treasurenumber]==g.Outside.treasure){
                   p[i].rectforTr.x=515;
                   p[i].rectforTr.y=515;
                   if(SDL_RenderCopy(rend,p[i].txtrforTr,NULL,&p[i].rectforTr)!=0){
                     SDL_ExitWithError("Problème de réupdate des trésors\n");
                   }
                 }
               }
             }
          }
          if (g.insert == 1 && g.move == 0 && g.testdebugmodethingy==0)//when we're inserting the tile
          {
            a=AUDIOLOAAAAAD("sfx\\insert.wav",a);
            if (SDL_RenderFillRect(rend, &rect) != 0)
            {
              SDL_ExitWithError("Pas pu dessiné un rectangle");
            }
            if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
            {
              SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
            }
            for (int i = 0; i < 7; i++)
            {
              for (int j = 0; j < 7; j++)
              {
                if (g.gameboard[i][j].txtr != NULL)
                {
                  //printf("On peut load cette image... aux coordonnées : %d,%d et aux tailles : %d,%d\n",g.gameboard[i][j].rect.x,g.gameboard[i][j].rect.y,g.gameboard[i][j].rect.w,g.gameboard[i][j].rect.h);
                  if (g.gameboard[i][j].IsExit == 1)
                  {
                    if (SDL_RenderCopy(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect))
                    {
                      SDL_ExitWithError("Problème d'initialisation des persos...\n");
                    }
                  }
                  else
                  {

                    if (SDL_RenderCopyEx(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect, ConvertOrientationToDegrees(g.gameboard[i][j].orientation), NULL, SDL_FLIP_NONE) != 0)
                    {
                      SDL_ExitWithError("Problème de rotation\n");
                    }
                  }
                }
              }
            }
            for (int i = 0; i < g.numplayer; i++)
            {
              if (SDL_RenderCopy(rend, p[i].txt, NULL, &p[i].point))
              {
                SDL_ExitWithError("Problème pour dessiner les autres joueurs\n");
              }
            }
            for (int i = 0; i < g.numplayer; i++)
            {
              for (int j = 0; j < 7; j++)
              {
                for (int k = 0; k < 7; k++)
                {
                  if (p[i].treasurenumber < p[i].Maxtreasure)
                  {
                    if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                    {
                      if (p[i].positionPlayer.x == g.gameboard[j][k].positionOfTile.x && p[i].positionPlayer.y == g.gameboard[j][k].positionOfTile.y)
                      {
                        p[i].treasurenumber++;
                        //printf("\nTreasure updated for %s\n\n",p[i].Name);
                      }
                      p[i].rectforTr.x = BASEPOS + 60 * k;
                      p[i].rectforTr.y = BASEPOS + 60 * j;
                      //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner les trésors\n");
                      }
                    }
                  }
                  else
                  {
                    p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                    p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                    //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner l'exit\n");
                    }
                  }
                }
              }
            }
            for (int i = 0; i < g.numplayer; i++)
            {
              for (int j = 0; j < 7; j++)
              {
                for (int k = 0; k < 7; k++)
                {
                  if (p[i].treasurenumber < p[i].Maxtreasure)
                  {
                    if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                    {
                      
                      p[i].rectforTr.x = BASEPOS + 60 * k;
                      p[i].rectforTr.y = BASEPOS + 60 * j;
                      //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner les trésors\n");
                      }
                    }
                  }
                  else
                  {
                    p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                    p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                    //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner l'exit\n");
                    }
                  }
                }
              }
            }
            for (int i = 0; i < g.numplayer; i++)
            {
              if (p[i].treasurenumber < p[i].Maxtreasure)
              {
                if (p[i].personalListTreasures[p[i].treasurenumber] == g.Outside.treasure)
                {
                  p[i].rectforTr.x = 515;
                  p[i].rectforTr.y = 515;
                  if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                  {
                    SDL_ExitWithError("Problème pour dessiner les trésors\n");
                  }
                }
              }
              else{
                printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
              }
            }
            g.insertcoord--;
            if (g.insertcoord < 0)
            {
              g.insertcoord = 11;
            }
            switch (g.insertcoord)
            {
            case 0:
            case 1:
            case 2:
              p[g.playerturn].rectforIn.x = BASEPOS + g.insertcoordinates[g.insertcoord] % 7 * 60;
              p[g.playerturn].rectforIn.y = 20 + g.insertcoordinates[g.insertcoord] / 7 * 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
              {
                SDL_ExitWithError("Problème de cible insertion\n");
              }
              break;
            case 3:
            case 4:
            case 5:
              p[g.playerturn].rectforIn.x = 45 + BASEPOS + g.insertcoordinates[g.insertcoord] % 7 * 60;
              p[g.playerturn].rectforIn.y = BASEPOS + g.insertcoordinates[g.insertcoord] / 7 * 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
              {
                SDL_ExitWithError("Problème de cible insertion\n");
              }
              break;
            case 6:
            case 7:
            case 8:
              p[g.playerturn].rectforIn.x = BASEPOS + g.insertcoordinates[g.insertcoord] % 7 * 60;
              p[g.playerturn].rectforIn.y = 45 + BASEPOS + g.insertcoordinates[g.insertcoord] / 7 * 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
              {
                SDL_ExitWithError("Problème de cible insertion\n");
              }
              break;
            case 9:
            case 10:
            case 11:
              p[g.playerturn].rectforIn.x = 20 + g.insertcoordinates[g.insertcoord] % 7 * 60;
              p[g.playerturn].rectforIn.y = BASEPOS + g.insertcoordinates[g.insertcoord] / 7 * 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
              {
                SDL_ExitWithError("Problème de cible insertion\n");
              }
              break;
            default:
              break;
            }
            for (int i=0;i<g.numplayer;i++){
               if(p[i].treasurenumber<p[i].Maxtreasure){
                 if(p[i].personalListTreasures[p[i].treasurenumber]==g.Outside.treasure){
                   p[i].rectforTr.x=515;
                   p[i].rectforTr.y=515;
                   if(SDL_RenderCopy(rend,p[i].txtrforTr,NULL,&p[i].rectforTr)!=0){
                     SDL_ExitWithError("Problème de réupdate des trésors\n");
                   }
                 }
               }
             }
          }
          continue;
//***********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
        case SDLK_RIGHT://Right key usage
          if (g.move == 1 && g.testdebugmodethingy==0)//when we're moving
          {
            g.treasureget=0;
            if (p[g.playerturn].positionPlayer.x < 6 && g.gameboard[p[g.playerturn].positionPlayer.y][p[g.playerturn].positionPlayer.x].E == 1 && g.gameboard[p[g.playerturn].positionPlayer.y][p[g.playerturn].positionPlayer.x + 1].W == 1)
            {
              p[g.playerturn].positionPlayer.x++;
              if (SDL_RenderFillRect(rend, &rect) != 0)
              {
                SDL_ExitWithError("Pas pu dessiné un rectangle");
              }
              if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
              {
                SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
              }
              for (int i = 0; i < 7; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  if (g.gameboard[i][j].txtr != NULL)
                  {
                    //printf("On peut load cette image... aux coordonnées : %d,%d et aux tailles : %d,%d\n",g.gameboard[i][j].rect.x,g.gameboard[i][j].rect.y,g.gameboard[i][j].rect.w,g.gameboard[i][j].rect.h);
                    if (g.gameboard[i][j].IsExit == 1)
                    {
                      if (SDL_RenderCopy(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect))
                      {
                        SDL_ExitWithError("Problème d'initialisation des persos...\n");
                      }
                    }
                    else
                    {

                      if (SDL_RenderCopyEx(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect, ConvertOrientationToDegrees(g.gameboard[i][j].orientation), NULL, SDL_FLIP_NONE) != 0)
                      {
                        SDL_ExitWithError("Problème de rotation\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (i != g.playerturn)
                {
                  if (SDL_RenderCopy(rend, p[i].txt, NULL, &p[i].point))
                  {
                    SDL_ExitWithError("Problème pour dessiner les autres joueurs\n");
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  for (int k = 0; k < 7; k++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[k][j].treasure)
                      {
                        if (p[i].positionPlayer.x == j && p[i].positionPlayer.y == k)
                        {
                          p[i].treasurenumber++;
                          g.treasureget=1;
                          printf("%sYou have now %d land(s) left to conquer !%s\n",ANSI[i],p[i].Maxtreasure-p[i].treasurenumber,ANSI[4]);
                          if(p[i].treasurenumber<p[i].Maxtreasure/3){
                            a=AUDIOLOAAAAAD("sfx\\treasureget1.wav",a);
                          }
                          if(p[i].treasurenumber>=p[i].Maxtreasure/3 && p[i].treasurenumber<2*p[i].Maxtreasure/3){
                            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
                          }
                          if(p[i].treasurenumber>=2*p[i].Maxtreasure/3 && p[i].treasurenumber<=p[i].Maxtreasure){
                            a=AUDIOLOAAAAAD("sfx\\treasureget2.wav",a);
                          }
                          //printf("\nTreasure updated for %s on the RIGHT position\n\n",p[i].Name);
                        }
                        p[i].rectforTr.x = BASEPOS + 60 * j;
                        p[i].rectforTr.y = BASEPOS + 60 * k;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                for (int j = 0; j < 7; j++)
                {
                  for (int k = 0; k < 7; k++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[k][j].treasure)
                      {
                        
                        p[i].rectforTr.x = BASEPOS + 60 * j;
                        p[i].rectforTr.y = BASEPOS + 60 * k;
                        //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates.\nWhile %s is on %d %d\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,k,j,p[i].Name,p[i].positionPlayer.x,p[i].positionPlayer.y);
                        //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else
                    {
                      p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                      p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                      
                      //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner l'exit\n");
                      }
                    }
                  }
                }
              }
              for (int i = 0; i < g.numplayer; i++)
              {
                if (p[i].treasurenumber < p[i].Maxtreasure)
                {
                  if (p[i].personalListTreasures[p[i].treasurenumber] == g.Outside.treasure)
                  {
                    p[i].rectforTr.x = 515;
                    p[i].rectforTr.y = 515;
                    //printf("For %s there are %d treasures left and the next treasure is on %d %d coordinates\n",p[i].Name,p[i].Maxtreasure-p[i].treasurenumber,g.Outside.positionOfTile.x,g.Outside.positionOfTile.y);
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner les trésors\n");
                    }
                  }
                }
                else{
                  //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                }
              }
              p[g.playerturn].point.x += 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txt, NULL, &p[g.playerturn].point))
              {
                SDL_ExitWithError("Problème d'aller vers la droite\n");
              }
              //printf("%s moves RIGHT\nX position = %d, Y position=%d\n", p[g.playerturn].Name, p[g.playerturn].positionPlayer.x, p[g.playerturn].positionPlayer.y);
              if(g.treasureget==0){
                a=AUDIOLOAAAAAD("sfx\\move.wav",a);
              }
            }
            for(int i=0;i<g.numplayer;i++){
              if(p[i].treasurenumber==p[i].Maxtreasure){
                if(p[i].positionPlayer.x==p[i].positionExit.x && p[i].positionPlayer.y==p[i].positionExit.y){
                  printf("%s%s WON THE LABYRINTH GAME !!!%s\n",ANSI[i],p[i].Name,ANSI[4]);
                  p[i].win=1;
                  g.insert=2;
                  g.move=2;
                  prg_launch=SDL_FALSE;
                }
              }
            }
          }
          if (g.insert == 0 && g.move == 0 && g.testdebugmodethingy==0)//when we're rotating the tile
          {
            a=AUDIOLOAAAAAD("sfx\\rotate.wav",a);
            g.rotation += 90;
            if (g.rotation >= DEG)
            {
              g.rotation = 0;
            }
            g.Outside.orientation = ConvertDegreesToOrientation(g.rotation);
            switch (g.Outside.shape)
            {
            case Ishaped:
              switch (g.Outside.orientation)
              {
              case Same:
              case Inverse:
                g.Outside.N = 1;
                g.Outside.S = 1;
                g.Outside.E = 0;
                g.Outside.W = 0;
                break;
              case Right:
              case Left:
                g.Outside.N = 0;
                g.Outside.S = 0;
                g.Outside.E = 1;
                g.Outside.W = 1;
                break;
              default:
                printf("Error in I shaped territory of orientation...\n");
                break;
              }
              break;
            case Lshaped:
              switch (g.Outside.orientation)
              {
              case Same:
                g.Outside.N = 1;
                g.Outside.S = 0;
                g.Outside.E = 1;
                g.Outside.W = 0;
                break;
              case Right:
                g.Outside.N = 0;
                g.Outside.S = 1;
                g.Outside.E = 1;
                g.Outside.W = 0;
                break;
              case Inverse:
                g.Outside.N = 0;
                g.Outside.S = 1;
                g.Outside.E = 0;
                g.Outside.W = 1;
                break;
              case Left:
                g.Outside.N = 1;
                g.Outside.S = 0;
                g.Outside.E = 0;
                g.Outside.W = 1;
                break;
              default:
                printf("Error in L shaped territory of orientation...\n");
                break;
              }
              break;
            case Tshaped:
              switch (g.Outside.orientation)
              {
              case Same:
                g.Outside.N = 0;
                g.Outside.S = 1;
                g.Outside.E = 1;
                g.Outside.W = 1;
                break;
              case Right:
                g.Outside.N = 1;
                g.Outside.S = 1;
                g.Outside.E = 0;
                g.Outside.W = 1;
                break;
              case Inverse:
                g.Outside.N = 1;
                g.Outside.S = 0;
                g.Outside.E = 1;
                g.Outside.W = 1;
                break;
              case Left:
                g.Outside.N = 1;
                g.Outside.S = 1;
                g.Outside.E = 1;
                g.Outside.W = 0;
                break;
              default:
                printf("Error in T shaped territory of orientation...\n");
                break;
              }
              break;
            default:
              printf("There has been an error...\n");
              break;
            }
            //printf("Accessiblity of piece : N=%d, S=%d, E=%d, W=%d\n", g.Outside.N, g.Outside.S, g.Outside.E, g.Outside.W);
            if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
            {
              SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
            }
            /*if(SDL_RenderCopyEx(rend,txtr,NULL,&rect2,g.rotation,NULL,SDL_FLIP_NONE)!=0){
                    SDL_ExitWithError("Problème de rotation\n");
              }
              */
             for (int i=0;i<g.numplayer;i++){
               if(p[i].treasurenumber<p[i].Maxtreasure){
                 if(p[i].personalListTreasures[p[i].treasurenumber]==g.Outside.treasure){
                   p[i].rectforTr.x=515;
                   p[i].rectforTr.y=515;
                   if(SDL_RenderCopy(rend,p[i].txtrforTr,NULL,&p[i].rectforTr)!=0){
                     SDL_ExitWithError("Problème de réupdate des trésors\n");
                   }
                 }
               }
             }
          }
          if (g.insert == 1 && g.move == 0 && g.testdebugmodethingy==0)//when we're inserting the tile
          {
            a=AUDIOLOAAAAAD("sfx\\insert.wav",a);
            if (SDL_RenderFillRect(rend, &rect) != 0)
            {
              SDL_ExitWithError("Pas pu dessiné un rectangle");
            }
            if (SDL_RenderCopyEx(rend, g.Outside.txtr, NULL, &g.Outside.rect, ConvertOrientationToDegrees(g.Outside.orientation), NULL, SDL_FLIP_NONE) != 0)
            {
              SDL_ExitWithError("Problème de rotation pour la tuile de dehors\n");
            }
            for (int i = 0; i < 7; i++)
            {
              for (int j = 0; j < 7; j++)
              {
                if (g.gameboard[i][j].txtr != NULL)
                {
                  //printf("On peut load cette image... aux coordonnées : %d,%d et aux tailles : %d,%d\n",g.gameboard[i][j].rect.x,g.gameboard[i][j].rect.y,g.gameboard[i][j].rect.w,g.gameboard[i][j].rect.h);
                  if (g.gameboard[i][j].IsExit == 1)
                  {
                    if (SDL_RenderCopy(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect))
                    {
                      SDL_ExitWithError("Problème d'initialisation des persos...\n");
                    }
                  }
                  else
                  {

                    if (SDL_RenderCopyEx(rend, g.gameboard[i][j].txtr, NULL, &g.gameboard[i][j].rect, ConvertOrientationToDegrees(g.gameboard[i][j].orientation), NULL, SDL_FLIP_NONE) != 0)
                    {
                      SDL_ExitWithError("Problème de rotation\n");
                    }
                  }
                }
              }
            }
            for (int i = 0; i < g.numplayer; i++)
            {
              if (SDL_RenderCopy(rend, p[i].txt, NULL, &p[i].point))
              {
                SDL_ExitWithError("Problème pour dessiner les autres joueurs\n");
              }
            }
            for (int i = 0; i < g.numplayer; i++)
            {
              for (int j = 0; j < 7; j++)
              {
                for (int k = 0; k < 7; k++)
                {
                  if (p[i].treasurenumber < p[i].Maxtreasure)
                  {
                    if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                    {
                      if (p[i].positionPlayer.x == g.gameboard[j][k].positionOfTile.x && p[i].positionPlayer.y == g.gameboard[j][k].positionOfTile.y)
                      {
                        p[i].treasurenumber++;
                        //printf("\nTreasure updated for %s\n\n",p[i].Name);
                      }
                      p[i].rectforTr.x = BASEPOS + 60 * k;
                      p[i].rectforTr.y = BASEPOS + 60 * j;
                      //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner les trésors\n");
                      }
                    }
                  }
                  else
                  {
                    p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                    p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                    //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner l'exit\n");
                    }
                  }
                  
                  for (int i = 0; i < g.numplayer; i++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.Outside.treasure)
                      {
                        p[i].rectforTr.x = 515;
                        p[i].rectforTr.y = 515;
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else{
                      printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                    }
                  }
                }
              }
            }
            for (int i = 0; i < g.numplayer; i++)
            {
              for (int j = 0; j < 7; j++)
              {
                for (int k = 0; k < 7; k++)
                {
                  if (p[i].treasurenumber < p[i].Maxtreasure)
                  {
                    if (p[i].personalListTreasures[p[i].treasurenumber] == g.gameboard[j][k].treasure)
                    {
                      
                      p[i].rectforTr.x = BASEPOS + 60 * k;
                      p[i].rectforTr.y = BASEPOS + 60 * j;
                      //printf("Treasure location : %d %d\n",(p[i].rectforTr.x-BASEPOS)/60,(p[i].rectforTr.y-BASEPOS)/60);
                      if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                      {
                        SDL_ExitWithError("Problème pour dessiner les trésors\n");
                      }
                    }
                  }
                  else
                  {
                    p[i].rectforTr.x = BASEPOS + 60 * p[i].positionExit.x;
                    p[i].rectforTr.y = BASEPOS + 60 * p[i].positionExit.y;
                    //printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                    if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                    {
                      SDL_ExitWithError("Problème pour dessiner l'exit\n");
                    }
                  }
                  
                  for (int i = 0; i < g.numplayer; i++)
                  {
                    if (p[i].treasurenumber < p[i].Maxtreasure)
                    {
                      if (p[i].personalListTreasures[p[i].treasurenumber] == g.Outside.treasure)
                      {
                        p[i].rectforTr.x = 515;
                        p[i].rectforTr.y = 515;
                        if (SDL_RenderCopy(rend, p[i].txtrforTr, NULL, &p[i].rectforTr))
                        {
                          SDL_ExitWithError("Problème pour dessiner les trésors\n");
                        }
                      }
                    }
                    else{
                      printf("Exit location : %d %d\n", (p[i].rectforTr.x - BASEPOS) / 60, (p[i].rectforTr.y - BASEPOS) / 60);
                    }
                  }
                }
              }
            }
            g.insertcoord++;
            if (g.insertcoord > 11)
            {
              g.insertcoord = 0;
            }
            switch (g.insertcoord)
            {
            case 0:
            case 1:
            case 2:
              p[g.playerturn].rectforIn.x = BASEPOS + g.insertcoordinates[g.insertcoord] % 7 * 60;
              p[g.playerturn].rectforIn.y = 20 + g.insertcoordinates[g.insertcoord] / 7 * 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
              {
                SDL_ExitWithError("Problème de cible insertion\n");
              }
              break;
            case 3:
            case 4:
            case 5:
              p[g.playerturn].rectforIn.x = 45 + BASEPOS + g.insertcoordinates[g.insertcoord] % 7 * 60;
              p[g.playerturn].rectforIn.y = BASEPOS + g.insertcoordinates[g.insertcoord] / 7 * 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
              {
                SDL_ExitWithError("Problème de cible insertion\n");
              }
              break;
            case 6:
            case 7:
            case 8:
              p[g.playerturn].rectforIn.x = BASEPOS + g.insertcoordinates[g.insertcoord] % 7 * 60;
              p[g.playerturn].rectforIn.y = 45 + BASEPOS + g.insertcoordinates[g.insertcoord] / 7 * 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
              {
                SDL_ExitWithError("Problème de cible insertion\n");
              }
              break;
            case 9:
            case 10:
            case 11:
              p[g.playerturn].rectforIn.x = 20 + g.insertcoordinates[g.insertcoord] % 7 * 60;
              p[g.playerturn].rectforIn.y = BASEPOS + g.insertcoordinates[g.insertcoord] / 7 * 60;
              if (SDL_RenderCopy(rend, p[g.playerturn].txtrforIn, NULL, &p[g.playerturn].rectforIn) != 0)
              {
                SDL_ExitWithError("Problème de cible insertion\n");
              }
              break;
            default:
              break;
            }
            for (int i=0;i<g.numplayer;i++){
               if(p[i].treasurenumber<p[i].Maxtreasure){
                 if(p[i].personalListTreasures[p[i].treasurenumber]==g.Outside.treasure){
                   p[i].rectforTr.x=515;
                   p[i].rectforTr.y=515;
                   if(SDL_RenderCopy(rend,p[i].txtrforTr,NULL,&p[i].rectforTr)!=0){
                     SDL_ExitWithError("Problème de réupdate des trésors\n");
                   }
                 }
               }
             }
            
          }
          continue;
//***********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
        
        default:
          continue;
        }
        break;
      case SDL_QUIT://To exit the play
        g.quit=1;
        prg_launch = SDL_FALSE;
        break;
      default:
        break;
      }
    }
    SDL_RenderPresent(rend);//renders everything in real time
  }
  /*if(SDL_RenderClear(rend)!=0)
    SDL_ExitWithError("Effacement du rendu échoué");
*/

  //SDL_Delay(10000);
  //SDL_DestroyTexture(txtr);
  if(g.quit==0){//if we didn't quit manually with the X button on the top right corner
    for(int i=0;i<g.numplayer;i++){
      if(p[i].win==1){
        if(SDL_RenderCopy(rend,p[i].txtrforWin,NULL,&p[i].rectforWin)!=0){
          SDL_ExitWithError("Problem in loading win animation...\n");
        }
      }
    }
    a=AUDIOLOAAAAAD("sfx\\end.wav",a);
    SDL_RenderPresent(rend);
    SDL_Delay(5000);
  }

  //Freeing everything !!!

  for(int i=0;i<g.numplayer;i++){
    SDL_DestroyTexture(p[i].txt);
    SDL_DestroyTexture(p[i].txtrforIn);
    SDL_DestroyTexture(p[i].txtrforTr);
    SDL_DestroyTexture(p[i].txtrforWin);
    SDL_DestroyTexture(p[i].txtrforTurn);
    SDL_DestroyTexture(p[i].txtrforSPQR);
    free(p[i].Name);
    free(p[i].personalListTreasures);
  }
  free(tr);
  free(p);
  for(int i=0;i<7;i++){
    for(int j=0;j<7;j++){
      SDL_DestroyTexture(g.gameboard[i][j].txtr);
      
    }
    
  }
  SDL_DestroyTexture(g.Outside.txtr);
 
  SDL_CloseAudioDevice(a.dvce);
  SDL_FreeWAV(a.wavStart);
  SDL_FreeSurface(windowappicon);
  //SDL_CloseAudioDevice(dvce);
  //SDL_FreeWAV(wavStart1);
  
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(app);
  SDL_Quit();

  return EXIT_SUCCESS;
}
