#include "Coordinate.h"
#include "Util.h"
#include <string>



Coordinate::Coordinate() {
	/*this->*/row = -1;
	column = -1;
	state = NONE;
}




Coordinate::Coordinate(int row, int column) {
	this->row = row;
	this->column = column;
	state = NONE;
}



Coordinate::Coordinate(string coord) {

	string aux;
	row = coord[0] - 'A';
	aux = coord.substr(1);
	column = stoi(aux) - 1;
	state = NONE;
}

int Coordinate::getRow() const {
	return row;
}

int Coordinate::getColumn() const {
	return column;
}

CellState Coordinate::getState() const {
	return state;
}

char Coordinate::getStateChar() const {
	char car;
	switch (state) {
	case NONE:
		car = 'N';
		break;
	case SHIP:
		car = 'S';
		break;
	case HIT:
		car = 'H';
		break;
	case WATER:
		car = 'W';
		break;
	}
	return car;
}

void Coordinate::setRow(int row) { // Coordinate *this;
	this->row = row;
}

void Coordinate::setColumn(int column) {
	this->column = column;
}

void Coordinate::setState(CellState state) {
	this->state = state;
}



bool Coordinate::compare(const Coordinate& coord) const {
	bool iguales = false;
	if (row == coord.row && this->column == coord.column) {
		iguales = true;
	}
	return iguales;
}


Coordinate Coordinate::addOffset(int offset, Orientation orientation) const {
	// Coordinate res = *this;	
	Coordinate res;
	res.row = row;
	res.column = column;
	switch (orientation) {
	case NORTH:
		res.row -= offset;
		break;
	case EAST:
		res.column += offset;
		break;
	case SOUTH:
		res.row += offset;
		break;
	case WEST:
		res.column -= offset;
		break;
	}
	return res;
}


Orientation Coordinate::orientationFromChar(char orientation) {

	Orientation resultado;
	switch (orientation) {
	case 'N':
		resultado = NORTH;
		break;
	case 'E':
		resultado = EAST;
		break;
	case 'S':
		resultado = SOUTH;
		break;
	case 'W':
		resultado = WEST;
		break;
	default:
		// esto cancela la ejecucion del metodo.
		throw EXCEPTION_WRONG_ORIENTATION;
		// throw 0;
		break;
	}
	return resultado;
}



ostream& operator<<(ostream& os, const Coordinate& c) {
	if (c.getColumn() != -1 && c.getRow() != -1) {
		if (c.getStateChar() != 'N') {
			os << (char)(c.row + 'A') << c.column + 1 << c.getStateChar();
		}
		else {
			os << (char)(c.row + 'A') << c.column + 1;
		}
	}
	else {
		os << "--";
	}
	return os;
}



