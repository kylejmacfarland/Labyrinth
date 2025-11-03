#include "entitygen.hpp"

#include "../util.hpp"
#include "../component/monsterai.hpp"

Entity* createTree() {
	Entity* tree = new Entity("Tree");
	tree->setTile(randi() % 8, 1);
	tree->rollWeight(1000, 5000);
	return tree;
}

Entity* createSword() {
	Entity* sword = new Entity("Sword");
	sword->setTile(randBounded(32, 36), randBounded(6, 9));
	sword->rollWeight(4, 6);
	return sword;
}

Entity* createGoblin() {
	Entity* goblin = new Entity("Goblin");
	goblin->setTile(25, 2);
	goblin->addComponent(new MonsterAI());
	goblin->rollWeight(30, 60);
	return goblin;
}