#include "componentmap.hpp"

ComponentMap::~ComponentMap() {
	for (pair<ComponentID, forward_list<Component*>*> l: components) {
		for (Component* c: *l.second) {
			delete c;
		}
		delete l.second;
	}
	components.clear();
}

void ComponentMap::add(Component* c) {
	if (!hasComponent(c->getID())) {
		components[c->getID()] = new forward_list<Component*>();
	}
	components[c->getID()]->push_front(c);
}

bool ComponentMap::hasComponent(ComponentID id) {
	return components.find(id) != components.end();
}