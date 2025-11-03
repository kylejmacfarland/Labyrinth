#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <vector>
#include "../component/componentmap.hpp"

using namespace std;

class Entity {
public:
	Entity();
	Entity(string n);
	~Entity();
	void setTile(int x, int y);
	void addComponent(Component* c);
	bool hasComponent(ComponentID id);
	void addXp(int x);
	void takeDamage(int damage);
	void increaseLaw();
	void increaseChaos();
	void setName(string n);
	string getName();
	int getTileX();
	int getTileY();
	int getLevel();
	int getHp();
	int getStrength();
	void setStrength(int s);
	int getAgility();
	int getStamina();
	int getIntellect();
	int getWisdom();
	int getCharisma();
	int getWeight();
	void setEncumbrance(int e);
	int getEncumbrance();
	int getXpYield();
	vector<Entity*>* getInventory();
	int getFreeWeight();
	bool isLawful();
	bool isChaotic();
	void rollWeight(int min, int max);
	bool pickup(Entity* e);
private:
	const int MAX_ALIGNMENT = 100;
	int tileX = 0;
	int tileY = 0;
	int level = 1;
	int xp = 0;
	int toNext = 50;
	int strength = 5;
	int agility = 5;
	int stamina = 5;
	int intellect = 5;
	int wisdom = 5;
	int charisma = 5;
	int hp = 15;
	int maxHP = 15;
	int weight = 1;
	int encumbrance = 50;
	int freeWeight = 50;
	int alignment = 0;
	string name;
	ComponentMap* components;
	vector<Entity*> inventory;
	void calcToNext();
	void calcHP();
	void calcFreeWeight();
};

#endif