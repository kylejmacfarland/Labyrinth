#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Texture* loadTexture(string path);

bool initSDL();

void destroySDL();

void clearScreen();

void setDrawColor(int r, int g, int b, int a);

void fillRect(int x0, int y0, int x1, int y1);

void renderText(string s, int x, int y);

void renderTile(int tileX, int tileY, int x, int y);

void renderTilePlusHalf(int tileX, int tileY, int x, int y);

void renderPresent();

void setRandomSeed(unsigned int s);

unsigned int randi();

int randBounded(int min, int max);

#endif