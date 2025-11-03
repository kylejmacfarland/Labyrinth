#ifndef DROP_HPP
#define DROP_HPP

#include "command.hpp"

class Drop: public Command {
public:
	Drop(int index, int x, int y);
	void execute(int index, Model* model) override;
private:
	int inventoryIndex;
	int xOffset, yOffset;
};

#endif