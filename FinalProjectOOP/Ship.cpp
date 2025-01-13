#include <iostream>
#include "Ship.h"
using namespace std;

Ship::Ship(ShipType type, const vector<Coordinate*>& positions) {
	// TODO EL TAMAÑO DEL BARCO (positions.size()) NO COINCIDE CON
	// EL TYPO BARCO PUES HAY QUE LANAZAR UNA EXCEPCION.!!!
	if (positions.size() != shipSize(type)) {
		throw EXCEPTION_WRONG_COORDINATES;
	}

	this->state = OK;
	this->type = type;
	this->positions = positions; // copiamos el vector en el del nuevo barco.
	for (int i = 0; i < positions.size(); i++) {
		positions[i]->setState(SHIP);
		(*positions[i]).setState(SHIP);
	}
	for (Coordinate* p : positions) {
		// p = positions[0]
		// p = positions[1]
		// p = positions[2]...
		p->setState(SHIP);
	}

}

// solo voy a utilizar el type que me pasan como parametro
unsigned Ship::shipSize(ShipType type) {
	/*unsigned size;
	switch(type){
		case BATTLESHIP:
			size = 4;
		break;
		case DESTROYER:
			size = 3;
		break;
		case CRUISE:
			size = 2;
		break;
		case SUBMARINE:
			size = 1;
		break;
	}
	return size;*/

	/*int sizes[] = {4, 3, 2, 1};
	return sizes[type];*/

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
	// coord.compare(*positions[i]);
	// coord.compare(*p)
	// positions[i]->compare(coord)
	// p->compare(coord)

	for (int i = 0; i < positions.size() && !resultado; i++) {
		if (coord.compare(*positions[i])) {
			resultado = true;
			pos = i; // me guardo la posicion		
		}
	}
	if (resultado) {
		// ya la he encontrado!!
		if (state == SUNK) {
			throw EXCEPTION_ALREADY_SUNK;
		}
		// si ya estaba hit...
		if (positions[pos]->getState() == HIT) {
			throw EXCEPTION_ALREADY_HIT;
		}
		// si no estaba hit, hitlearla y comprobar si todo esta
		// hit para sunk...
		positions[pos]->setState(HIT);
		// comprobamos si todas estan hit.
		nhits = 0;
		for (int i = 0; i < positions.size(); i++) {
			if (positions[i]->getState() == HIT) {
				nhits++;
			}
		}
		if (nhits == shipSize(type)) { // nhits == positions.size()
			state = SUNK;
		}
		else {
			state = DAMAGED;
		}
		resultado = true;
	}
	return resultado;
}

// cout << ship; ==> operator<<(cout, ship);
ostream& operator<<(ostream& os, const Ship& ship) {
	// you have to print the shiptype, state between braces and 
	// the coordinate list.

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
