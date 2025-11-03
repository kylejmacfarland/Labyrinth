#include "util.hpp"

const int TILE_SIZE = 16;
const int FONT_SIZE = 8;
unsigned int seed;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* tiles;
SDL_Texture* font;

SDL_Texture* loadTexture(string path) {
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if (surface == NULL) {
		printf("Unable to load image \"%s\". SDL_Error: %s\n", path.c_str(), SDL_GetError());
		return NULL;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (tex == NULL) {
		printf("Unable to create texture from \"%s\". SDL_Error: %s\n", path.c_str(), SDL_GetError());
		return NULL;
	}
	return tex;
}

bool initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	window = SDL_CreateWindow("Labyrinth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Could not create window. SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		printf("Could not create renderer. SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 71, 45, 60, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	tiles = loadTexture("../asset/tiles.bmp");
	font = loadTexture("../asset/font.bmp");
	return true;
}

void destroySDL() {
	SDL_DestroyTexture(tiles);
	SDL_DestroyTexture(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void clearScreen() {
	SDL_SetRenderDrawColor(renderer, 71, 45, 60, 255);
	SDL_RenderClear(renderer);
}

void setDrawColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void fillRect(int x0, int y0, int x1, int y1) {
	SDL_Rect r{x0, y0, x1, y1};
	SDL_RenderFillRect(renderer, &r);
}

void renderTile(int tileX, int tileY, int x, int y) {
	SDL_Rect srcrect = {tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstrect = {x * TILE_SIZE * 2, y * TILE_SIZE * 2, TILE_SIZE * 2, TILE_SIZE * 2};
	SDL_RenderCopy(renderer, tiles, &srcrect, &dstrect);
}

void renderTilePlusHalf(int tileX, int tileY, int x, int y) {
	SDL_Rect srcrect = {tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstrect = {x * TILE_SIZE * 2 + TILE_SIZE, y * TILE_SIZE * 2 + TILE_SIZE + TILE_SIZE / 2, TILE_SIZE * 2, TILE_SIZE * 2};
	SDL_RenderCopy(renderer, tiles, &srcrect, &dstrect);
}

void renderText(string s, int x, int y) {
	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		SDL_Rect srcrect = {(c - 32) * FONT_SIZE, 0, FONT_SIZE, FONT_SIZE};
		SDL_Rect dstrect = {(x + i) * FONT_SIZE * 2, y * FONT_SIZE * 2, FONT_SIZE * 2, FONT_SIZE * 2};
		SDL_RenderCopy(renderer, font, &srcrect, &dstrect);
	}
}

void renderPresent() {
	SDL_RenderPresent(renderer);
}

void setRandomSeed(unsigned int s) {
	seed = s;
}

unsigned int randi() {
	unsigned int x = seed;
	seed = x * 6264136223846793005 + 1442695040888963407;
	x ^= x >> 18;
	int r = x >> 27;
	return x >> r | x << (-r & 31);
}

int randBounded(int min, int max) {
	return min + randi() % (max - min + 1);
}
