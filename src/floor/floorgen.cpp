#include "floorgen.hpp"

#include "../util.hpp"
#include "../entity/entitygen.hpp"

Floor* generateFloor(Entity* player, int floorNum) {
	FloorGenerator* floorGen = new TestGenerator();
	Floor* floor = floorGen->generate(player);
	delete floorGen;
	return floor;
}

FloorGenerator::~FloorGenerator() {
}

Floor* TestGenerator::generate(Entity* player) {
	Floor* floor = new Floor();
	floor->addPlayerAt(player, 2, 2);
	//floor.addEntityAt(EntityFactory.createStairs(false, floorNum), 31, 31);
	//floor.addEntityAt(EntityFactory.createStairs(true, floorNum), 33, 33);
	for (int i = 0; i < 2048; i++) {
		int x = randi() % floor->getWidth();
		int y = randi() % floor->getHeight();
		if (!floor->hasEntityAt(x, y)) {
			floor->addEntityAt(createSword(), x, y);
		}
	}
	return floor;
}