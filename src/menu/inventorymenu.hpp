#ifndef INVENTORYMENU_HPP
#define INVENTORYMENU_HPP

#include "../entity/entity.hpp"

class InventoryMenu {
public:
	void setInventory(vector<Entity*>* i);
	int size();
	Entity* getItem(int i);
	Entity* getSelectedItem();
	int getSelection();
	void setSelection(int s);
	void scrollUp();
	void scrollDown();
private:
	vector<Entity*>* inventory = NULL;
	int selection = 0;
};

#endif