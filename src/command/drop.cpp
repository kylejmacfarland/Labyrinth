#include "drop.hpp"

Drop::Drop(int index, int x, int y): Command(false) {
	inventoryIndex = index;
	xOffset = x;
	yOffset = y;
}

void Drop::execute(int index, Model* model) {
	model->getFloor()->drop(index, inventoryIndex, xOffset, yOffset);
}