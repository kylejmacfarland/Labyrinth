#include "floor.hpp"

#include "../util.hpp"

Floor::Floor() {
}

Floor::~Floor() {
	for (pair<int, Entity*> e: entities) {
		if (e.first != playerIndex) {
			delete e.second;
		}
	}
	entities.clear();
}

int Floor::getPlayerIndex() {
	return playerIndex;
}

int Floor::getWidth() {
	return WIDTH;
}

int Floor::getHeight() {
	return HEIGHT;
}

int Floor::getCellX(int index) {
	return index % WIDTH;
}

int Floor::getCellY(int index) {
	return index / WIDTH;
}

Entity* Floor::getEntityAtIndex(int index) {
	return entities[index];
}

unordered_map<int, Entity*> Floor::getEntities() {
	return entities;
}

void Floor::moveEntity(int index, int xOffset, int yOffset) {
	if (xOffset == 0 && yOffset == 0) {
		return;
	}
	int endX = getCellX(index) + xOffset;
	int endY = getCellY(index) + yOffset;
	if (endX >= 0 && endY >= 0 && endX < WIDTH && endY < HEIGHT) {
		if (hasEntityAt(endX, endY)) {
			attack(index, getIndex(endX, endY));
		} else {
			Entity* e = entities[index];
			entities.erase(index);
			addEntityAt(e, endX, endY);
			if (playerIndex == index) {
				playerIndex = getIndex(endX, endY);
			}
		}
	}
}

void Floor::pickup(int index, int xOffset, int yOffset) {
	int x = getCellX(index);
	int y = getCellY(index);
	int pickupX = x + xOffset;
	int pickupY = y + yOffset;
	if (pickupX >= 0 && pickupX < WIDTH && pickupY >= 0 && pickupY < HEIGHT) {
		if (hasEntityAt(pickupX, pickupY)) {
			if (getEntityAtIndex(index)->pickup(getEntityAt(pickupX, pickupY))) {
				entities.erase(getIndex(pickupX, pickupY));
			}
		}
	}
}

void Floor::drop(int index, int inventoryIndex, int xOffset, int yOffset) {
	return;
}

void Floor::addPlayerAt(Entity* player, int x, int y) {
	playerIndex = getIndex(x, y);
	addEntityAt(player, x, y);
}

void Floor::addEntityAt(Entity* e, int x, int y) {
	entities[getIndex(x, y)] = e;
}

Entity* Floor::getEntityAt(int x, int y) {
	return entities[getIndex(x, y)];
}

int Floor::getIndex(int x, int y) {
	return y * WIDTH + x;
}

bool Floor::hasEntityAt(int x, int y) {
	return hasEntityAtIndex(getIndex(x, y));
}

bool Floor::hasEntityAtIndex(int index) {
	return entities.find(index) != entities.end() && entities[index] != NULL;
}

/**
 * An attack function should normally be in the Entity class.
 * However, it is in the Floor class to allow for dead defenders to be removed from the Floor's hashmap.
 * Function takes indices as parameters rather than pointers to Entities for the same reason.
 */
void Floor::attack(int attackerIndex, int defenderIndex) {
	Entity* attacker = entities[attackerIndex];
	Entity* defender = entities[defenderIndex];
	int damage = (20 - (defender->getAgility() + defender->getLevel()) + (attacker->getStrength() + attacker->getLevel())) * (95 + randi() % 11) * attacker->getStrength() / 2000;
	if (damage < 1) {
		damage = 1;
	}
	// Check for critical hit.
	if (randi() % 20 == 0) {
		damage *= 2;
	}
	defender->takeDamage(damage);
	//View.addMessage(String.format("%s hits %s for %d damage.\n", attacker, defender, damage));
	if (defender->getHp() <= 0) {
		attacker->addXp(defender->getXpYield());
		if (defender->isChaotic()) {
			attacker->increaseLaw();
		} else {
			attacker->increaseChaos();
		}
		if (defenderIndex == playerIndex) {
			// Game Over
		} else {
			delete defender;
		}
		entities.erase(defenderIndex);
		//View.addMessage(String.format("%s dies.\n", defender));
	}
}