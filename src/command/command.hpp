#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../mvc/model.hpp"

class Command {
public:
	Command();
	Command(bool f);
	virtual ~Command();
	virtual void execute(int index, Model* model) = 0;
	bool isFreeAction();
private:
	bool isFree;
};

#endif