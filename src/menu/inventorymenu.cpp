#include "inventorymenu.hpp"

#include "../util.hpp"

void InventoryMenu::setInventory(vector<Entity*>* i) {
	inventory = i;
}

int InventoryMenu::size() {
	if (inventory == NULL) {
		return 0;
	}
	return inventory->size();
}

Entity* InventoryMenu::getItem(int i) {
	return (*inventory)[i];
}

Entity* InventoryMenu::getSelectedItem() {
	return (*inventory)[selection];
}

int InventoryMenu::getSelection() {
	return selection;
}

void InventoryMenu::setSelection(int s) {
	selection = 0;
}

void InventoryMenu::scrollUp() {
	if (inventory == NULL || size() == 0) {
		return;
	}
	selection--;
	if (selection < 0) {
		selection = inventory->size() - 1;
	}
}

void InventoryMenu::scrollDown() {
	if (inventory == NULL || size() == 0) {
		return;
	}
	selection = (selection + 1) % inventory->size();
}