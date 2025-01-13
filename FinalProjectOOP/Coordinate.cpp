#include "Coordinate.h"
#include "Util.h"
#include <string>

// Coordinate c1;
//	this = &c1
// Coordinate c2;
//	this = &c2

Coordinate::Coordinate() {
	/*this->*/row = -1;
	column = -1;
	state = NONE;
}

// this contiene la direccion del objeto que invoca el metodo
// esta implicita en todos los metodos de instancias
//	En los constructores contiene la direccion dle objeto que estamos
// 	inicializando.

// Coordinate c1(3, 4);
//		this = &c1
//		row = 3
//		colum = 4
//	this->row = 3
//	this->column = 4;
Coordinate::Coordinate(int row, int column) {
	this->row = row;
	this->column = column;
	state = NONE;
}

// la cadena siempre es correcta.
//  012
// -----------------------------------------
// "A1"		row = 0		column = 0
// "A7"		row ='A'-'A'	column = '7'(56) - '0'(49) - 1 = 6
// "B12"	row = 1		column = 11
// "C12"	row = 2		column = 11
// "D34"	row = 3		column = 33

Coordinate::Coordinate(string coord) {
	/*	row = coord[0] - 'A';
		if(coord.length() == 2){
			column = coord[1] - '0' - 1;
		}
		else{
			column = (coord[1] - '0') * 10 + (coord[2] - '0') - 1;
		}*/
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

char Coordinate::getStateChar() const { // const Coordinate *this;
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

// Coordinate c1(1, 2);
// Coordinate c2(1, 2);
// Coordinate c3(3, 6);
// cout << c1.compare(c2) << endl;
//		const Coordinate *this = &c1
//		const Coordinate &coord = c2;

// cout << c3.compare(c1) << endl;
//		const Coordinate *this = &c3;
//		const Coordinate &coord =c1;


bool Coordinate::compare(const Coordinate& coord) const {
	bool iguales = false;
	if (row == coord.row && this->column == coord.column) {
		iguales = true;
	}
	return iguales;
}

// Coordinate c("T20");
// Coordinate r = c1.addOffset(3, NORTH);
//			const Coordinate *this = &c1;
//			int offset = 3;
//			Orientation orientation = orientation;

// cout << r.getRow() << ", " << r.getColumn() << endl; // 16
// cout << c1.getRow() << ", " << c1.getColumn() << endl // 19
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


// cout << Coordinate::orientationFromChar('N'); // 0
Orientation Coordinate::orientationFromChar(char orientation) {
	// NO NECESITO UNA COORDENADA, SOLO USO EL PARAMETRO, orientation
	// => static
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

// Coordinate c1;
// operator<<(cout, c1);

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



