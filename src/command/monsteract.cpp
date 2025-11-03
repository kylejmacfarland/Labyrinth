#include "monsteract.hpp"

#include "../util.hpp"

void MonsterAct::execute(int index, Model* model) {
	// Move in a random direction for now.
	wander(index, model);
}

void MonsterAct::wander(int index, Model* model) {
	int xOffset = randi() % 3 - 1;
	int yOffset = randi() % 3 - 1;
	model->getFloor()->moveEntity(index, xOffset, yOffset);
}