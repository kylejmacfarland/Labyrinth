#ifndef MOVE_HPP
#define MOVE_HPP

#include "command.hpp"

class Move: public Command {
public:
	Move(int x, int y);
	void execute(int index, Model* model) override;
private:
	int xOffset, yOffset;
};

#endif