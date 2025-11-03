#ifndef MODEL_HPP
#define MODEL_HPP

#include "../floor/floor.hpp"
#include "../menu/inventorymenu.hpp"

class Model {
public:
	enum class State {
		DEFAULT, INVENTORY, PICKUP, DROP, 
	};
	Model();
	State getState();
	void setState(State s);
	void genFloor();
	void updateAllEntities();
	Floor* getFloor();
	Entity* getPlayer();
	bool isPlayerInventoryEmpty();
	int getPlayerInventorySelection();
	InventoryMenu* getInventoryMenu();
	void scrollMenuUp();
	void scrollMenuDown();
private:
	int floorNum = 1;
	Floor* floor;
	Entity player;
	InventoryMenu invMenu;
	State currentState;
};

#endif