#ifndef MIDDLE_H
#define MIDDLE_H
#define MATRICE 7
#include <stdlib.h>
#include <stdlib.h>
#include "begin.h"
#include "structenum.h"
Tile LoadImageGameboard(char *txt,Tile t, SDL_Renderer *r);
Gameboard createGameboard(Gameboard g,SDL_Renderer *r);
Orientation ConvertDegreesToOrientation(int deg);
int ConvertOrientationToDegrees(Orientation i);
#endif