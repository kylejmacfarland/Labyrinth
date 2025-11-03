#include "controller.hpp"

#include "../command/move.hpp"
#include "../command/pickup.hpp"
#include "../command/drop.hpp"

void Controller::setModel(Model* m) {
	model = m;
}

bool Controller::inventoryDisplayed() {
	return model->getState() == Model::State::DROP;
}

void Controller::checkInput(bool* running) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			*running = false;
		} else if (e.type == SDL_KEYDOWN) {
			checkState(&e);
			switch (model->getState()) {
			case Model::State::DEFAULT:
				checkMove(&e);
				break;
			case Model::State::INVENTORY:
				checkInventoryInput(&e);
				break;
			case Model::State::PICKUP:
				checkPickupDir(&e);
				break;
			case Model::State::DROP:
				checkDropDir(&e);
				break;
			default:
				break;
			}
		}
	}
}

void Controller::checkState(SDL_Event* e) {
	switch (model->getState()) {
	case Model::State::INVENTORY:
		if (e->key.keysym.sym == SDLK_d) {
			if (!model->isPlayerInventoryEmpty()) {
				model->setState(Model::State::DROP);
			}
		} else if (e->key.keysym.sym == SDLK_ESCAPE || e->key.keysym.sym == SDLK_i) {
			model->setState(Model::State::DEFAULT);
		}
		break;
	case Model::State::PICKUP:
		if (e->key.keysym.sym == SDLK_ESCAPE) {
			model->setState(Model::State::DEFAULT);
		}
		break;
	case Model::State::DROP:
		if (e->key.keysym.sym == SDLK_ESCAPE) {
			model->setState(Model::State::DEFAULT);
		}
		break;
	case Model::State::DEFAULT:
	default:
		if (e->key.keysym.sym == SDLK_p) {
			model->setState(Model::State::PICKUP);
		} else if (e->key.keysym.sym == SDLK_i) {
			model->setState(Model::State::INVENTORY);
		}
		break;
	}
}

Controller::Direction Controller::checkDir(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN) {
		switch (e->key.keysym.sym) {
		case SDLK_UP:
			if (isModPressed(e, KMOD_SHIFT)) {
				return Direction::NORTHEAST;
			}
		case SDLK_KP_8:
		case SDLK_k:
			return Direction::NORTH;
		case SDLK_DOWN:
			if (isModPressed(e, KMOD_SHIFT)) {
				return Direction::SOUTHWEST;
			}
		case SDLK_KP_2:
		case SDLK_j:
			return Direction::SOUTH;
		case SDLK_LEFT:
			if (isModPressed(e, KMOD_SHIFT)) {
				return Direction::NORTHWEST;
			}
		case SDLK_KP_4:
		case SDLK_h:
			return Direction::WEST;
		case SDLK_RIGHT:
			if (isModPressed(e, KMOD_SHIFT)) {
				return Direction::SOUTHEAST;
			}
		case SDLK_KP_6:
		case SDLK_l:
			return Direction::EAST;
		case SDLK_KP_7:
		case SDLK_y:
			return Direction::NORTHWEST;
		case SDLK_KP_9:
		case SDLK_u:
			return Direction::NORTHEAST;
		case SDLK_KP_1:
		case SDLK_b:
			return Direction::SOUTHWEST;
		case SDLK_KP_3:
		case SDLK_n:
			return Direction::SOUTHEAST;
		default:
			break;
		}
	}
	return Direction::NODIRECTION;
}

bool Controller::isModPressed(SDL_Event* e, SDL_Keymod modID) {
	return e->key.keysym.mod & modID;
}

void Controller::checkMove(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN) {
		// Check for wait command.
		if (e->key.keysym.sym == SDLK_KP_5 || e->key.keysym.sym == SDLK_SPACE) {
			addPlayerCommand(new Move(0, 0));
			return;
		}
		// Check for movement.
		Direction d = checkDir(e);
		switch (d) {
		case Direction::NORTH:
			addPlayerCommand(new Move(0, -1));
			break;
		case Direction::NORTHEAST:
			addPlayerCommand(new Move(1, -1));
			break;
		case Direction::EAST:
			addPlayerCommand(new Move(1, 0));
			break;
		case Direction::SOUTHEAST:
			addPlayerCommand(new Move(1, 1));
			break;
		case Direction::SOUTH:
			addPlayerCommand(new Move(0, 1));
			break;
		case Direction::SOUTHWEST:
			addPlayerCommand(new Move(-1, 1));
			break;
		case Direction::WEST:
			addPlayerCommand(new Move(-1, 0));
			break;
		case Direction::NORTHWEST:
			addPlayerCommand(new Move(-1, -1));
			break;
		default:
			break;
		}
	}
}

void Controller::checkInventoryInput(SDL_Event* e) {
	Controller::Direction dir = checkDir(e);
	if (dir == Direction::NORTH) {
		model->scrollMenuUp();
	} else if (dir == Direction::SOUTH) {
		model->scrollMenuDown();
	}
}

void Controller::checkPickupDir(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN) {
		Direction d = checkDir(e);
		switch (d) {
		case Direction::NORTH:
			addPlayerCommand(new Pickup(0, -1));
			break;
		case Direction::NORTHEAST:
			addPlayerCommand(new Pickup(1, -1));
			break;
		case Direction::EAST:
			addPlayerCommand(new Pickup(1, 0));
			break;
		case Direction::SOUTHEAST:
			addPlayerCommand(new Pickup(1, 1));
			break;
		case Direction::SOUTH:
			addPlayerCommand(new Pickup(0, 1));
			break;
		case Direction::SOUTHWEST:
			addPlayerCommand(new Pickup(-1, 1));
			break;
		case Direction::WEST:
			addPlayerCommand(new Pickup(-1, 0));
			break;
		case Direction::NORTHWEST:
			addPlayerCommand(new Pickup(-1, -1));
			break;
		default:
			return;
		}
		model->setState(Model::State::DEFAULT);
	}
}

void Controller::checkDropDir(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN) {
		Direction d = checkDir(e);
		int s = model->getPlayerInventorySelection();
		switch (d) {
		case Direction::NORTH:
			addPlayerCommand(new Drop(s, 0, -1));
			break;
		case Direction::NORTHEAST:
			addPlayerCommand(new Drop(s, 1, -1));
			break;
		case Direction::EAST:
			addPlayerCommand(new Drop(s, 1, 0));
			break;
		case Direction::SOUTHEAST:
			addPlayerCommand(new Drop(s, 1, 1));
			break;
		case Direction::SOUTH:
			addPlayerCommand(new Drop(s, 0, 1));
			break;
		case Direction::SOUTHWEST:
			addPlayerCommand(new Drop(s, -1, 1));
			break;
		case Direction::WEST:
			addPlayerCommand(new Drop(s, -1, 0));
			break;
		case Direction::NORTHWEST:
			addPlayerCommand(new Drop(s, -1, -1));
			break;
		default:
			return;
		}
		model->setState(Model::State::DEFAULT);
	}
}

void Controller::addPlayerCommand(Command* c) {
	c->execute(model->getFloor()->getPlayerIndex(), model);
	if (!c->isFreeAction()) {
		model->updateAllEntities();
	}
	delete c;
}