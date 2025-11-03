#ifndef PICKUP_HPP
#define PICKUP_HPP

#include "command.hpp"

class Pickup: public Command {
public:
	Pickup(int x, int y);
	void execute(int index, Model* model) override;
private:
	int xOffset, yOffset;
};

#endif