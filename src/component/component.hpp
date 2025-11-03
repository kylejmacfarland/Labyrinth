#ifndef COMPONENT_HPP
#define COMPONENT_HPP

enum ComponentID {
	STAIRS, MONSTER_AI, 
};

class Component {
public:
	ComponentID getID();
protected:
	ComponentID id;
	Component(ComponentID i);
};

#endif