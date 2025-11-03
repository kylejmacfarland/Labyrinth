#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SDL2/SDL.h>
#include "model.hpp"
#include "../command/command.hpp"

class Controller {
public:
	void setModel(Model* m);
	bool inventoryDisplayed();
	void checkInput(bool* running);
private:
	enum class Direction {
		NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST, NODIRECTION
	};
	Model* model;
	void checkState(SDL_Event* e);
	Direction checkDir(SDL_Event* e);
	bool isModPressed(SDL_Event* e, SDL_Keymod modID);
	void checkMove(SDL_Event* e);
	void checkInventoryInput(SDL_Event* e);
	void checkPickupDir(SDL_Event* e);
	void checkDropDir(SDL_Event* e);
	void addPlayerCommand(Command* c);
};

#endif