/**
 * @file
 * 
 * This file contains the main gameplay loop and as little as possible to keep that loop running.
 * 
 * @author Kyle MacFarland
 */

#include <ctime>
#include "util.hpp"
#include "mvc/model.hpp"
#include "mvc/view.hpp"
#include "mvc/controller.hpp"

const int FPS = 60;

int ticksPerFrame = 1000 / FPS;
bool running = true;
Controller* c;
Model* m;
View v;

/**
 * Initializes Model, View, and Controller classes, calls SDL setup, and sets random seed.
 */
void init() {
	// Random funciton seeded with system time.
	// SDL_GetTicks() starts at zero with the program, so seeing with that should result with a much smaller range of random numbers.
	setRandomSeed(time(NULL));
	c = new Controller();
	m = new Model();
	c->setModel(m);
	if (!initSDL()) {
		return;
	}
}

/**
 * Limits framerate to the value of FPS.
 */
void capFrameRate(int startTicks) {
	int ticksElapsed = SDL_GetTicks() - startTicks;
	if (ticksElapsed < ticksPerFrame) {
		SDL_Delay(ticksPerFrame - ticksElapsed);
	}
}

/**
 * Main gameplay loop.
 * Allows Controller class to check user input which will then update the Model class.
 * View class will render the current floor every frame.
 * Also caps framerate.
 */
void gameLoop() {
	while (running) {
		int startTicks = SDL_GetTicks();
		c->checkInput(&running);
		v.render(m);
		capFrameRate(startTicks);
	}
	delete m;
	delete c;
}

int main(int argc, char** args) {
	init();
	gameLoop();
	destroySDL();
	return 0;
}
