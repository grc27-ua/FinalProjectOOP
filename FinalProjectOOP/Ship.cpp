#include <iostream>
#include "Ship.h"
using namespace std;

Ship::Ship(ShipType type, const vector<Coordinate*>& positions) {

	if (positions.size() != shipSize(type)) {
		throw EXCEPTION_WRONG_COORDINATES;
	}

	this->state = OK;
	this->type = type;
	this->positions = positions; 
	for (int i = 0; i < positions.size(); i++) {
		positions[i]->setState(SHIP);
		(*positions[i]).setState(SHIP);
	}
	for (Coordinate* p : positions) {

		p->setState(SHIP);
	}

}

unsigned Ship::shipSize(ShipType type) {


	return (unsigned)(4 - type);
}

ShipType Ship::typeFromChar(char type) {
	ShipType st;
	switch (type) {
	case 'B':
		st = BATTLESHIP;
		break;
	case 'C':
		st = CRUISE;
		break;
	case 'D':
		st = DESTROYER;
		break;
	case 'S':
		st = SUBMARINE;
		break;
	default:
		throw EXCEPTION_WRONG_SHIP_TYPE;
		break;
	}
	return st;
}

Coordinate* Ship::getPosition(unsigned pos) const {
	Coordinate* r = NULL;
	if (pos >= 0 && pos < positions.size()) {
		r = positions[pos];
	}
	return r;
}

ShipType Ship::getType() const {
	return type;
}

ShipState Ship::getState() const {
	return state;
}

bool Ship::hit(const Coordinate& coord) {
	bool resultado = false;
	int pos, nhits;


	for (int i = 0; i < positions.size() && !resultado; i++) {
		if (coord.compare(*positions[i])) {
			resultado = true;
			pos = i; 
		}
	}
	if (resultado) {
		if (state == SUNK) {
			throw EXCEPTION_ALREADY_SUNK;
		}
		if (positions[pos]->getState() == HIT) {
			throw EXCEPTION_ALREADY_HIT;
		}
		
		positions[pos]->setState(HIT);
		nhits = 0;
		for (int i = 0; i < positions.size(); i++) {
			if (positions[i]->getState() == HIT) {
				nhits++;
			}
		}
		if (nhits == shipSize(type)) { 
			state = SUNK;
		}
		else {
			state = DAMAGED;
		}
		resultado = true;
	}
	return resultado;
}

ostream& operator<<(ostream& os, const Ship& ship) {
	

	string nombres[] = { "BATTLESHIP", "DESTROYER", "CRUISE", "SUBMARINE" };
	string barquitos[] = { "O", "D", "S" };

	os << nombres[ship.type]
		<< " (" << barquitos[ship.state]
		<< "): ";
	for (int i = 0; i < ship.positions.size(); i++) {
		os << *ship.positions[i] << " ";
	}
	return os;
}
