#include "command.hpp"

Command::Command() {
	isFree = false;
}

Command::Command(bool f) {
	isFree = f;
}

Command::~Command() {
}

bool Command::isFreeAction() {
	return isFree;
}