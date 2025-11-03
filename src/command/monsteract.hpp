#ifndef MONSTERACT_HPP
#define MONSTERACT_HPP

#include "command.hpp"

class MonsterAct: public Command {
public:
	void execute(int index, Model* model) override;
private:
	void wander(int index, Model* model);
};

#endif