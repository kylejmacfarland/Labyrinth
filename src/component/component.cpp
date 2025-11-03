#include "component.hpp"

Component::Component(ComponentID i) {
	id = i;
}

ComponentID Component::getID() {
	return id;
}