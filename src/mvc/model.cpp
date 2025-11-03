#include "model.hpp"

#include <ctime>
#include "../util.hpp"
#include "../floor/floorgen.hpp"
#include "../command/monsteract.hpp"

Model::Model() {
	currentState = State::DEFAULT;
	player.setTile(25, 0);
	player.rollWeight(150, 200);
	player.setName("Player");
	floor = generateFloor(&player, floorNum);
}

Model::State Model::getState() {
	return currentState;
}

void Model::setState(Model::State s) {
	currentState = s;
	if (currentState == State::INVENTORY) {
		invMenu.setInventory(player.getInventory());
		invMenu.setSelection(0);
	}
}

void Model::genFloor() {
	delete floor;
	floor = generateFloor(&player, floorNum);
}

void Model::updateAllEntities() {
	// Compile list of indices to ensure that Entities are not updated twice if one moves to a different space.
	forward_list<int> indices;
	for (pair<int, Entity*> e: floor->getEntities()) {
		indices.push_front(e.first);
	}
	for (int i: indices) {
		if (i != floor->getPlayerIndex() && floor->hasEntityAtIndex(i)) {
			Entity* e = floor->getEntityAtIndex(i);
			if (e != NULL && e->hasComponent(MONSTER_AI)) {
				MonsterAct* ma = new MonsterAct();
				ma->execute(i, this);
				delete ma;
			}
		}
	}
}

Floor* Model::getFloor() {
	return floor;
}

Entity* Model::getPlayer() {
	return &player;
}

bool Model::isPlayerInventoryEmpty() {
	return player.getInventory()->size() == 0;
}

int Model::getPlayerInventorySelection() {
	return invMenu.getSelection();
}

InventoryMenu* Model::getInventoryMenu() {
	return &invMenu;
}

void Model::scrollMenuUp() {
	invMenu.scrollUp();
}

void Model::scrollMenuDown() {
	invMenu.scrollDown();
}