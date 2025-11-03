#include "view.hpp"

#include <sstream>
#include "../util.hpp"

/**
 * Renders visuals based on Model class.
 */
void View::render(Model* model) {
	clearScreen();
	renderEntities(model);
	switch (model->getState()) {
	case Model::State::INVENTORY:
		renderInventory(model->getPlayer(), model->getInventoryMenu());
		break;
	case Model::State::PICKUP:
		renderText("Choose pickup direction.", HEADER_X, HEADER_Y);
		break;
	case Model::State::DROP:
		renderText("Choose drop direction.", HEADER_X, HEADER_Y);
		break;
	default:
		break;
	}
	renderPresent();
}

/**
 * Renders a semi-transparent background for menus.
 */
void View::renderMenuBG() {
	setDrawColor(71, 45, 60, 192);
	fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**
 * Renders entities in the player's view.
 */
void View::renderEntities(Model* model) {
	Floor* floor = model->getFloor();
	for (pair<int, Entity*> e: floor->getEntities()) {
		renderTile(e.second->getTileX(), e.second->getTileY(), floor->getCellX(e.first), floor->getCellY(e.first));
	}	
}

/**
 * Renders Inventory Menu.
 */
void View::renderInventory(Entity* player, InventoryMenu* invMenu) {
	renderMenuBG();
	renderText("-INVENTORY-", HEADER_X, HEADER_Y);
	if (invMenu->size() == 0) {
		renderText("Inventory empty.", HEADER_X + 2, HEADER_Y + 2);
		renderText("Pick up items to add them to inventory.", HEADER_X + 2, HEADER_Y + 4);
	} else {
		int menuOffset = invMenu->getSelection() / 10 * 10;
		renderText(">", HEADER_X + 3, (invMenu->getSelection() - menuOffset) * 2 + HEADER_Y + 5);
		for (int i = 0; i + menuOffset < invMenu->size() && i < 10; i++) {
			Entity* e = invMenu->getItem(i + menuOffset);
			renderTilePlusHalf(e->getTileX(), e->getTileY(), 3, i + 3);
			renderText(e->getName(), HEADER_X + 6, i * 2 + HEADER_Y + 5);
		}
		renderStats(invMenu->getSelectedItem());
	}
	stringstream eStr;
	eStr << "Encumbrance: " << player->getFreeWeight() << " / " << player->getEncumbrance() << " lb.";
	renderText(eStr.str(), HEADER_X + 2, 34);
}

/**
 * Renders an Entity's stats.
 * Used when displaying the Inventory Menu.
 */
void View::renderStats(Entity* e) {
	const int STAT_X = 27;
	const int STAT_Y = 7;
	stringstream ss;
	ss << "-" << e->getName() << "-";
	renderText(ss.str(), STAT_X - 2, STAT_Y);
	ss.str("");
	ss << "Level:     " << e->getLevel();
	renderText(ss.str(), STAT_X, STAT_Y + 2);
	ss.str("");
	ss << "Strength:  " << e->getStrength();
	renderText(ss.str(), STAT_X, STAT_Y + 3);
	ss.str("");
	ss << "Agility:   " << e->getAgility();
	renderText(ss.str(), STAT_X, STAT_Y + 4);
	ss.str("");
	ss << "Stamina:   " << e->getStamina();
	renderText(ss.str(), STAT_X, STAT_Y + 5);
	ss.str("");
	ss << "Intellect: " << e->getIntellect();
	renderText(ss.str(), STAT_X, STAT_Y + 6);
	ss.str("");
	ss << "Wisdom:    " << e->getWisdom();
	renderText(ss.str(), STAT_X, STAT_Y + 7);
	ss.str("");
	ss << "Charisma:  " << e->getCharisma();
	renderText(ss.str(), STAT_X, STAT_Y + 8);
	ss.str("");
	ss << "Weight:    " << e->getWeight() << " lb.";
	renderText(ss.str(), STAT_X, STAT_Y + 10);
}