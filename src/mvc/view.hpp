#ifndef VIEW_HPP
#define VIEW_HPP

#include "model.hpp"

const int HEADER_X = 3;
const int HEADER_Y = 3;

class View {
public:
	void render(Model* model);
private:
	void renderMenuBG();
	void renderEntities(Model* model);
	void renderInventory(Entity* player, InventoryMenu* invMenu);
	void renderStats(Entity* e);
};

#endif