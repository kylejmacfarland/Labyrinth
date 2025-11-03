/**
 * @file
 * 
 * 
 * 
 * @author Kyle MacFarland
 */

#ifndef FLOORGEN_HPP
#define FLOORGEN_HPP

#include "floor.hpp"

Floor* generateFloor(Entity* player, int floorNum);

class FloorGenerator {
public:
	virtual ~FloorGenerator();
	virtual Floor* generate(Entity* player) = 0;
};

class TestGenerator: public FloorGenerator {
public:
	Floor* generate(Entity* player) override;
};

#endif