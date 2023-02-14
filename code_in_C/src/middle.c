#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "structenum.h"
#include "middle.h"
#include "begin.h"
/*
Movable :  12 I-shaped tiles , 16 L-shaped tiles , 6 T-shaped tiles . (1 of em being outside)
Unmovable : 0 I-shaped tiles , 4 L-shaped tiles , 12 T-shaped tiles .
24 treasures total : 12 Unmovable Tshaped tiles, 6 Movable Tshaped tiles, 6 Movable Lshaped tiles
*/

//function that loads a tile with the BMP texture called txt in the render r
Tile LoadImageGameboard(char *txt, Tile t, SDL_Renderer *r)
{
    t.srfc = SDL_LoadBMP(txt);
    if (t.srfc == NULL)
    {
        printf("%s entry point did not load...\n", txt);
    }
    t.txtr = SDL_CreateTextureFromSurface(r, t.srfc);
    SDL_FreeSurface(t.srfc);
    if (SDL_QueryTexture(t.txtr, NULL, NULL, &t.rect.w, &t.rect.h) != 0)
    {
        SDL_ExitWithError("Why though2...");
    }
    
    t.rect.w *= 0.6;
    t.rect.h *= 0.6;
    return t;
}

//function that creates the gameboard
Gameboard createGameboard(Gameboard g, SDL_Renderer *r)
{
    srand(time(NULL));
    int IM = 12, LM = 16, TM = 6, tmp = 0;
    LOT base[TOTAL / 2] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    char mnbrsys[33] = {1, 3, 5, 7, 8, 9, 10, 11, 12, 13, 15, 17, 19, 21, 22, 23, 24, 25, 26, 27, 29, 31, 33, 35, 36, 37, 38, 39, 40, 41, 43, 45, 47};
    for (int i = 0; i < MATRICE; i++)
    {
        for (int j = 0; j < MATRICE; j++)
        {
            g.gameboard[i][j].shape = 0;
            g.gameboard[i][j].srfc = NULL;
            g.gameboard[i][j].txtr = NULL;
            g.gameboard[i][j].treasure = 0;
            g.gameboard[i][j].orientation = Same;
            g.gameboard[i][j].N = 0;
            g.gameboard[i][j].S = 0;
            g.gameboard[i][j].E = 0;
            g.gameboard[i][j].W = 0;
            g.gameboard[i][j].IsExit = 0;
            if (i % 2 == 0 && j % 2 == 0)
            {
                g.gameboard[i][j].tilestatus = Unmovable;
            }
            else
            {
                g.gameboard[i][j].tilestatus = Movable;
            }
            g.gameboard[i][j].positionOfTile.x = j;
            g.gameboard[i][j].positionOfTile.y = i;
        }
    }
    g.gameboard[0][0].shape = Lshaped;
    g.gameboard[0][0].orientation = Right;
    g.gameboard[0][0].E = 1;
    g.gameboard[0][0].S = 1;

    g.gameboard[0][2].shape = Tshaped;
    g.gameboard[0][2].orientation = Same;
    g.gameboard[0][2].E = 1;
    g.gameboard[0][2].W = 1;
    g.gameboard[0][2].S = 1;

    g.gameboard[0][4].shape = Tshaped;
    g.gameboard[0][4].orientation = Same;
    g.gameboard[0][4].E = 1;
    g.gameboard[0][4].W = 1;
    g.gameboard[0][4].S = 1;

    g.gameboard[0][6].shape = Lshaped;
    g.gameboard[0][6].orientation = Inverse;
    g.gameboard[0][6].W = 1;
    g.gameboard[0][6].S = 1;

    g.gameboard[2][0].shape = Tshaped;
    g.gameboard[2][0].orientation = Left;
    g.gameboard[2][0].E = 1;
    g.gameboard[2][0].N = 1;
    g.gameboard[2][0].S = 1;

    g.gameboard[2][2].shape = Tshaped;
    g.gameboard[2][2].orientation = Left;
    g.gameboard[2][2].E = 1;
    g.gameboard[2][2].N = 1;
    g.gameboard[2][2].S = 1;

    g.gameboard[2][4].shape = Tshaped;
    g.gameboard[2][4].orientation = Same;
    g.gameboard[2][4].E = 1;
    g.gameboard[2][4].W = 1;
    g.gameboard[2][4].S = 1;

    g.gameboard[2][6].shape = Tshaped;
    g.gameboard[2][6].orientation = Right;
    g.gameboard[2][6].W = 1;
    g.gameboard[2][6].N = 1;
    g.gameboard[2][6].S = 1;

    g.gameboard[4][0].shape = Tshaped;
    g.gameboard[4][0].orientation = Left;
    g.gameboard[4][0].E = 1;
    g.gameboard[4][0].N = 1;
    g.gameboard[4][0].S = 1;

    g.gameboard[4][2].shape = Tshaped;
    g.gameboard[4][2].orientation = Inverse;
    g.gameboard[4][2].E = 1;
    g.gameboard[4][2].W = 1;
    g.gameboard[4][2].N = 1;

    g.gameboard[4][4].shape = Tshaped;
    g.gameboard[4][4].orientation = Right;
    g.gameboard[4][4].W = 1;
    g.gameboard[4][4].N = 1;
    g.gameboard[4][4].S = 1;

    g.gameboard[4][6].shape = Tshaped;
    g.gameboard[4][6].orientation = Right;
    g.gameboard[4][6].W = 1;
    g.gameboard[4][6].N = 1;
    g.gameboard[4][6].S = 1;

    g.gameboard[6][0].shape = Lshaped;
    g.gameboard[6][0].orientation = Same;
    g.gameboard[6][0].E = 1;
    g.gameboard[6][0].N = 1;

    g.gameboard[6][2].shape = Tshaped;
    g.gameboard[6][2].orientation = Inverse;
    g.gameboard[6][2].E = 1;
    g.gameboard[6][2].W = 1;
    g.gameboard[6][2].N = 1;

    g.gameboard[6][4].shape = Tshaped;
    g.gameboard[6][4].orientation = Inverse;
    g.gameboard[6][4].E = 1;
    g.gameboard[6][4].W = 1;
    g.gameboard[6][4].N = 1;

    g.gameboard[6][6].shape = Lshaped;
    g.gameboard[6][6].orientation = Left;
    g.gameboard[6][6].W = 1;
    g.gameboard[6][6].N = 1;

    switch (g.numplayer)
    {
    case 2:
        g.gameboard[0][0].IsExit = 1;
        g.gameboard[0][6].IsExit = 1;
        break;
    case 3:
        g.gameboard[0][0].IsExit = 1;
        g.gameboard[0][6].IsExit = 1;
        g.gameboard[6][6].IsExit = 1;
        break;
    case 4:
        g.gameboard[0][0].IsExit = 1;
        g.gameboard[0][6].IsExit = 1;
        g.gameboard[6][6].IsExit = 1;
        g.gameboard[6][0].IsExit = 1;
        break;
    default:
        printf("Erreur d'attribution de sortie !\n");
        break;
    }
    g.Outside.srfc = NULL;
    g.Outside.txtr = NULL;
    g.Outside.treasure = 0;
    g.Outside.shape = 0;
    g.Outside.orientation = Same;
    g.Outside.positionOfTile.x = 7;
    g.Outside.positionOfTile.y = 7;

    //(i!=0 && j!=0) || (i!=0 && j!=6) || (i!=6 && j!=0) || (i!=6 && j!=6)
    int m = 13;
    for (int i = 0; i < 7; i += 2)
    {
        for (int j = 0; j < 7; j += 2)
        {
            if (g.gameboard[i][j].shape == Tshaped)
            {
                g.gameboard[i][j].treasure = m;
                //printf("The Unmovable Tshaped tile at %d,%d has treasure %d\n", g.gameboard[i][j].positionOfTile.x, g.gameboard[i][j].positionOfTile.y, m);
                m++;
            }
        }
    }

    //printf("IM=%d,LM=%d,TM=%d\n", IM, LM, TM);
    for (int i = 0; i < MATRICE; i++)
    {
        for (int j = 0; j < MATRICE; j++)
        {
            if (i % 2 == 1 || j % 2 == 1)
            {
                if (IM > 0 && LM > 0 && TM > 0)
                {
                    tmp = rand() % 3;
                }
                else if (IM > 0 && LM > 0 && TM == 0)
                {
                    tmp = rand() % 2;
                }
                else if (IM > 0 && LM == 0 && TM > 0)
                {
                    tmp = rand() % 2;
                    if (tmp == 1)
                    {
                        tmp = 2;
                    }
                }
                else if (IM == 0 && LM > 0 && TM > 0)
                {
                    tmp = (rand() % 2) + 1;
                }
                else if (IM > 0 && LM == 0 && TM == 0)
                {
                    tmp = 0;
                }
                else if (IM == 0 && LM > 0 && TM == 0)
                {
                    tmp = 1;
                }
                else if (IM == 0 && LM == 0 && TM > 0)
                {
                    tmp = 2;
                }
                else if (IM == 0 && LM == 0 && TM == 0)
                {
                    printf("Normalement ça devrait pas se passer comme ça !\n");
                }
                /*
                while(tmp==0 && IM==0){
                    tmp=rand()%3;
                }
                while(tmp==0 && LM==0){
                    tmp=rand()%3;
                }
                while(tmp==0 && TM==0){
                    tmp=rand()%3;
                }*/

                switch (tmp)
                {
                case 0:
                    g.gameboard[i][j].shape = Ishaped;
                    g.gameboard[i][j].orientation = rand() % 4;
                    IM--;
                    break;
                case 1:
                    g.gameboard[i][j].shape = Lshaped;
                    g.gameboard[i][j].orientation = rand() % 4;
                    LM--;
                    break;
                case 2:
                    g.gameboard[i][j].shape = Tshaped;
                    g.gameboard[i][j].orientation = rand() % 4;
                    TM--;
                    break;
                default:
                    printf("Error of tmp...\n");
                    break;
                }
                //printf("IM=%d,LM=%d,TM=%d\n", IM, LM, TM);
            }
        }
    }

    if (IM == 1)
    {
        g.Outside.shape = Ishaped;
    }
    if (LM == 1)
    {
        g.Outside.shape = Lshaped;
    }
    if (TM == 1)
    {
        g.Outside.shape = Tshaped;
    }

    int k = rand() % 12;
    int l = rand() % 33;
    int tmp1 = 0, tmp2 = 0;
    for (int i = 0; i < TOTAL / 2; i++)
    {
        //printf("base of %d = %d before while\n", k, base[k]);
        while (base[k] == 0)
        {
            k = rand() % 12;
            //printf("redo\n");
        }
        //printf("base of %d = %d after while\n", k, base[k]);
        //printf("base of %d = %d before while\n",l,mnbrsys[l]);
        while (mnbrsys[l] == 0 || g.gameboard[mnbrsys[l] / 7][mnbrsys[l] % 7].shape == Ishaped)
        {
            l = rand() % 33;
        }
        //printf("base of %d = %d after while\n",l,mnbrsys[l]);
        tmp1 = mnbrsys[l] / 7;
        tmp2 = mnbrsys[l] % 7;
        g.gameboard[tmp1][tmp2].treasure = base[k];
        //printf("The tile at %d,%d which corresponds to %d has treasure %d\n", tmp2, tmp1, mnbrsys[l], g.gameboard[tmp1][tmp2].treasure);
        base[k] = 0;
        mnbrsys[l] = 0;
        k = rand() % 12;
        l = rand() % 33;
    }

    printf("Gameboard initiated !\n");
    g.Outside.orientation = Same;
    g.Outside.rect.x = 500;
    g.Outside.rect.y = 500;
    switch (g.Outside.shape)
    {
    case Ishaped:
        g.Outside.N=1;
        g.Outside.S=1;
        g.Outside.E=0;
        g.Outside.W=0;
        g.Outside = LoadImageGameboard("sprites\\I.bmp", g.Outside, r);
        break;
    case Lshaped:
        g.Outside.N=1;
        g.Outside.S=0;
        g.Outside.E=1;
        g.Outside.W=0;
        g.Outside = LoadImageGameboard("sprites\\L.bmp", g.Outside, r);
        break;
    case Tshaped:
        g.Outside.N=0;
        g.Outside.S=1;
        g.Outside.E=1;
        g.Outside.W=1;
        g.Outside = LoadImageGameboard("sprites\\T.bmp", g.Outside, r);
        break;
    default:
        printf("There has been an error in the loading of the tile Outside...\n");
        break;
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            g.gameboard[i][j].rect.x = (BASEPOS - 15) + (BASEPOS - 5) * j;
            g.gameboard[i][j].rect.y = (BASEPOS - 15) + (BASEPOS - 5) * i;
            g.gameboard[i][j] = LoadImageGameboard("sprites\\L.bmp", g.gameboard[i][j], r);
            switch (g.gameboard[i][j].shape)
            {
            case Ishaped:
                switch (g.gameboard[i][j].orientation)
                {
                case Same:
                case Inverse:
                    g.gameboard[i][j] = LoadImageGameboard("sprites\\I.bmp", g.gameboard[i][j], r);
                    g.gameboard[i][j].N = 1;
                    g.gameboard[i][j].S = 1;
                    break;
                case Left:
                case Right:
                    g.gameboard[i][j] = LoadImageGameboard("sprites\\I.bmp", g.gameboard[i][j], r);
                    g.gameboard[i][j].E = 1;
                    g.gameboard[i][j].W = 1;
                    break;
                default:
                    printf("Error in I shapes territory...\n");
                    break;
                }
                break;
            case Lshaped:
                if (g.gameboard[i][j].tilestatus == Unmovable)
                {
                    if (g.gameboard[i][j].IsExit == 1)
                    {
                        //printf("%d %d is an exit\n", i, j);
                        switch (g.gameboard[i][j].orientation)
                        {
                        case Same:

                            g.gameboard[i][j] = LoadImageGameboard("sprites\\entree\\violet.bmp", g.gameboard[i][j], r);

                            printf("%sWe loaded Player 4's entry...%s\n",ANSI[3],ANSI[4]);
                            break;
                        case Left:
                            g.gameboard[i][j] = LoadImageGameboard("sprites\\entree\\vert.bmp", g.gameboard[i][j], r);

                            printf("%sWe loaded Player 3's entry...%s\n",ANSI[2],ANSI[4]);
                            break;
                        case Right:
                            g.gameboard[i][j] = LoadImageGameboard("sprites\\entree\\rouge.bmp", g.gameboard[i][j], r);

                            printf("%sWe loaded Player 1's entry...%s\n",ANSI[0],ANSI[4]);
                            break;
                        case Inverse:
                            g.gameboard[i][j] = LoadImageGameboard("sprites\\entree\\bleu.bmp", g.gameboard[i][j], r);

                            printf("%sWe loaded Player 2's entry...%s\n",ANSI[1],ANSI[4]);
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        switch (g.gameboard[i][j].orientation)
                        {
                        case Same:
                            g.gameboard[i][j].N = 1;
                            g.gameboard[i][j].E = 1;
                            break;
                        case Right:
                            g.gameboard[i][j].E = 1;
                            g.gameboard[i][j].S = 1;
                            break;
                        case Inverse:
                            g.gameboard[i][j].S = 1;
                            g.gameboard[i][j].W = 1;
                            break;
                        case Left:
                            g.gameboard[i][j].W = 1;
                            g.gameboard[i][j].N = 1;
                            break;
                        default:
                            printf("Problem in L territory concerning the access...\n");
                            break;
                        }
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\L.bmp", g.gameboard[i][j], r);
                    }
                }
                else
                {
                    switch (g.gameboard[i][j].orientation)
                    {
                    case Same:
                        g.gameboard[i][j].N = 1;
                        g.gameboard[i][j].E = 1;
                        break;
                    case Right:
                        g.gameboard[i][j].E = 1;
                        g.gameboard[i][j].S = 1;
                        break;
                    case Inverse:
                        g.gameboard[i][j].S = 1;
                        g.gameboard[i][j].W = 1;
                        break;
                    case Left:
                        g.gameboard[i][j].W = 1;
                        g.gameboard[i][j].N = 1;
                        break;
                    default:
                        printf("Problem in L territory concerning the access...\n");
                        break;
                    }
                    switch (g.gameboard[i][j].treasure)
                    {
                    case 0:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\L.bmp", g.gameboard[i][j], r);
                        break;
                    case 1:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Dacia_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 2:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Gallia_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 3:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Britannia_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 4:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Hispania_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 5:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Egypt_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 6:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Mesopotamia_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 7:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Babylonia_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 8:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Tripolitania_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 9:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Armenia_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 10:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Dalmetia_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 11:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Macedonia_L.bmp", g.gameboard[i][j], r);
                        break;
                    case 12:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Thrace_L.bmp", g.gameboard[i][j], r);
                        break;
                    default:
                        printf("Problem in L territory concerning the sprites...\n");
                        break;
                    }
                }
                break;
            case Tshaped:
                if (g.gameboard[i][j].tilestatus == Unmovable)
                {
                    switch (g.gameboard[i][j].treasure)
                    {
                    case 13:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Assyria_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 14:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Numidia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 15:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Mauritania_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 16:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Moesia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 17:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Galatia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 18:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Judaea_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 19:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Pannonia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 20:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Aquitania_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 21:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Raetia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 22:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Corsica_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 23:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Sicilia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 24:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Sardinia_T.bmp", g.gameboard[i][j], r);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    switch (g.gameboard[i][j].orientation)
                    {
                    case Same:
                        g.gameboard[i][j].S = 1;
                        g.gameboard[i][j].E = 1;
                        g.gameboard[i][j].W = 1;
                        break;
                    case Right:
                        g.gameboard[i][j].W = 1;
                        g.gameboard[i][j].N = 1;
                        g.gameboard[i][j].S = 1;
                        break;
                    case Inverse:
                        g.gameboard[i][j].N = 1;
                        g.gameboard[i][j].E = 1;
                        g.gameboard[i][j].W = 1;
                        break;
                    case Left:
                        g.gameboard[i][j].E = 1;
                        g.gameboard[i][j].N = 1;
                        g.gameboard[i][j].S = 1;
                        break;
                    default:
                        printf("Problem in T territory concerning the access...\n");
                        break;
                    }
                    switch (g.gameboard[i][j].treasure)
                    {
                    case 0:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\T.bmp", g.gameboard[i][j], r);
                        break;
                    case 1:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Dacia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 2:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Gallia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 3:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Britannia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 4:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Hispania_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 5:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Egypt_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 6:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Mesopotamia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 7:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Babylonia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 8:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Tripolitania_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 9:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Armenia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 10:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Dalmetia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 11:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Macedonia_T.bmp", g.gameboard[i][j], r);
                        break;
                    case 12:
                        g.gameboard[i][j] = LoadImageGameboard("sprites\\tresores\\Thrace_T.bmp", g.gameboard[i][j], r);
                        break;
                    default:
                        printf("Problem in T territory concerning the sprites...\n");
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    return g;
}

//function that converts degrees into orientation
Orientation ConvertDegreesToOrientation(int deg)
{
    Orientation i = 0;
    switch (deg)
    {
    case 0:
        i = Same;
        break;
    case 90:
        i = Right;
        break;
    case 180:
        i = Inverse;
        break;
    case 270:
        i = Left;
        break;
    default:
        printf("Erreur d'orientation !\n");
        break;
    }
    return i;
}

//function that converts orientation into degrees
int ConvertOrientationToDegrees(Orientation i)
{
    int deg = 0;
    switch (i)
    {
    case Same:
        deg = 0;
        break;
    case Right:
        deg = 90;
        break;
    case Inverse:
        deg = 180;
        break;
    case Left:
        deg = 270;
        break;
    default:
        printf("Erreur d'orientation !\n");
        break;
    }
    return deg;
}