#include "pickup.hpp"

Pickup::Pickup(int x, int y): Command(false) {
	xOffset = x;
	yOffset = y;
}

void Pickup::execute(int index, Model* model) {
	model->getFloor()->pickup(index, xOffset, yOffset);
}