#ifndef SHIP_H_
#define SHIP_H_
#include "Coordinate.h"
#include "Util.h"
#include <vector>

enum ShipType {
	BATTLESHIP,
	DESTROYER,
	CRUISE,
	SUBMARINE
};

enum ShipState {
	OK,
	DAMAGED,
	SUNK
};

class Ship {
	/// !!
	friend ostream& operator<<(ostream& os, const Ship& ship);
protected:
	ShipState state;
	ShipType type;

	vector<Coordinate*> positions;
public:
	Ship(ShipType type, const vector<Coordinate*>& positions);
	static unsigned shipSize(ShipType type);
	static ShipType typeFromChar(char type);
	Coordinate* getPosition(unsigned pos) const;
	ShipType getType() const;
	ShipState getState() const;
	bool hit(const Coordinate& coord);
};

#endif#pragma once
