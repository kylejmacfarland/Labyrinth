#include "entity.hpp"

#include "../util.hpp"

Entity::Entity() {
	components = new ComponentMap();
}

Entity::Entity(string n): Entity() {
	setName(n);
}

Entity::~Entity() {
	delete components;
	components = NULL;
}

void Entity::setTile(int x, int y) {
	tileX = x;
	tileY = y;
}

void Entity::addComponent(Component* c) {
	components->add(c);
}

bool Entity::hasComponent(ComponentID id) {
	return components->hasComponent(id);
}

void Entity::addXp(int x) {
	xp += x;
	while (xp > toNext) {
		level++;
		calcToNext();
	}
}

void Entity::takeDamage(int damage) {
	hp -= damage;
}

void Entity::increaseLaw() {
	alignment++;
	if (alignment > MAX_ALIGNMENT) {
		alignment = MAX_ALIGNMENT;
	}
}

void Entity::increaseChaos() {
	alignment--;
	if (alignment < -MAX_ALIGNMENT) {
		alignment = -MAX_ALIGNMENT;
	}
}

void Entity::setName(string n) {
	name = n;
}

string Entity::getName() {
	return name;
}

int Entity::getTileX() {
	return tileX;
}

int Entity::getTileY() {
	return tileY;
}

int Entity::getLevel() {
	return level;
}

int Entity::getHp() {
	return hp;
}

int Entity::getStrength() {
	return strength;
}

void Entity::setStrength(int s) {
	strength = s;
	setEncumbrance(strength * 10);
}

int Entity::getAgility() {
	return agility;
}

int Entity::getStamina() {
	return stamina;
}

int Entity::getIntellect() {
	return intellect;
}


int Entity::getWisdom() {
	return wisdom;
}

int Entity::getCharisma() {
	return charisma;
}

int Entity::getWeight() {
	return weight;
}

void Entity::setEncumbrance(int e) {
	encumbrance = e;
	calcFreeWeight();
}

int Entity::getEncumbrance() {
	return encumbrance;
}

int Entity::getFreeWeight() {
	return freeWeight;
}

int Entity::getXpYield() {
	return toNext / 10;
}

vector<Entity*>* Entity::getInventory() {
	return &inventory;
}

bool Entity::isLawful() {
	return alignment > 0;
}

bool Entity::isChaotic() {
	return alignment < 0;
}

void Entity::rollWeight(int min, int max) {
	weight = randBounded(min, max);
}

bool Entity::pickup(Entity* e) {
	if (e->weight > freeWeight) {
		return false;
	}
	inventory.push_back(e);
	calcFreeWeight();
	return true;
}

void Entity::calcToNext() {
	toNext = level * level * 10 + level * 40;
}

void Entity::calcHP() {
	maxHP = stamina * level + 6 * level + 4;
}

void Entity::calcFreeWeight() {
	freeWeight = encumbrance;
	for (Entity* e: inventory) {
		freeWeight -= e->weight;
	}
}