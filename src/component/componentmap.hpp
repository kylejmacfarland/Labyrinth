#ifndef COMPONENTMAP_HPP
#define COMPONENTMAP_HPP

#include <unordered_map>
#include <forward_list>
#include "component.hpp"

using namespace std;

/**
 * ComponentMap is a data structure for storing Components in an Entity.
 * The data structure is a hashmap using Component ID as a key to access a linked list which contains the Component pointers.
 * This allows for a quick lookup to see if an Entity has a specified Component and also allows for a multiple Components of the same type.
 */
class ComponentMap {
public:
	~ComponentMap();
	void add(Component* c);
	bool hasComponent(ComponentID id);
private:
	unordered_map<ComponentID, forward_list<Component*>*> components;
};

#endif