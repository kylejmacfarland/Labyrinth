#include "move.hpp"

Move::Move(int x, int y) {
	xOffset = x;
	yOffset = y;
}

void Move::execute(int index, Model* model) {
	model->getFloor()->moveEntity(index, xOffset, yOffset);
}