#ifndef FLOOR_HPP
#define FLOOR_HPP

#include <unordered_map>
#include "../entity/entity.hpp"

using namespace std;

class Floor {
public:
	Floor();
	~Floor();
	void addPlayerAt(Entity* player, int x, int y);
	void addEntityAt(Entity* e, int x, int y);
	int getPlayerIndex();
	int getWidth();
	int getHeight();
	int getCellX(int index);
	int getCellY(int index);
	bool hasEntityAt(int x, int y);
	bool hasEntityAtIndex(int index);
	Entity* getEntityAtIndex(int index);
	unordered_map<int, Entity*> getEntities();
	void moveEntity(int index, int xOffset, int yOffset);
	void pickup(int index, int xOffset, int yOffset);
	void drop(int index, int inventoryIndex, int xOffset, int yOffset);
private:
	static const int WIDTH = 64;
	static const int HEIGHT = 64;
	int playerIndex = 0;
	unordered_map<int, Entity*> entities;
	int getIndex(int x, int y);
	Entity* getEntityAt(int x, int y);
	void attack(int attackerIndex, int defenderIndex);
};

#endif