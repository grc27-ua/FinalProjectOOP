#include "Player.h"

Player::Player(string name) {
	this->name = name;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j].setRow(i);
			board[i][j].setColumn(j);
			// board[i][j] = Coordinate(i, j);
		}
	}
}

string Player::getName() const {
	return name;
}

void Player::addShip(const Coordinate& pos, ShipType type, Orientation orientation) {
	int r, c;
	int tam, cuantos;
	cuantos = 0;
	for (int i = 0; i < ships.size(); i++) {
		if (type == ships[i].getType()) {
			cuantos++;
		}
	}
	if (type == BATTLESHIP && cuantos == 1) {
		throw EXCEPTION_MAX_SHIP_TYPE;
	}
	if (type == DESTROYER && cuantos == 2) {
		throw EXCEPTION_MAX_SHIP_TYPE;
	}
	if (type == CRUISE && cuantos == 3) {
		throw EXCEPTION_MAX_SHIP_TYPE;
	}
	if (type == SUBMARINE && cuantos == 4) {
		throw EXCEPTION_MAX_SHIP_TYPE;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j].getState() == WATER || board[i][j].getState() == HIT) {
				throw EXCEPTION_GAME_STARTED;
			}
		}
	}

	r = pos.getRow();
	c = pos.getColumn();
	tam = Ship::shipSize(type);	
	vector<Coordinate*> positions;
	switch (orientation) {
	case NORTH:
		for (int i = 1; i <= tam; i++) {
			if (r < 0 || r > 9 || c < 0 || c > 9) {
				throw EXCEPTION_OUTSIDE;
			}
			if (board[r][c].getState() == SHIP) {
				throw EXCEPTION_NONFREE_POSITION;
			}
			positions.push_back(&board[r][c]);
			r--;
		}
		break;
	case SOUTH:
		for (int i = 1; i <= tam; i++) {
			if (r < 0 || r > 9 || c < 0 || c > 9) {
				throw EXCEPTION_OUTSIDE;
			}
			if (board[r][c].getState() == SHIP) {
				throw EXCEPTION_NONFREE_POSITION;
			}
			positions.push_back(&board[r][c]);
			r++;
		}
		break;
	case EAST:
		for (int i = 1; i <= tam; i++) {
			if (r < 0 || r > 9 || c < 0 || c > 9) {
				throw EXCEPTION_OUTSIDE;
			}
			if (board[r][c].getState() == SHIP) {
				throw EXCEPTION_NONFREE_POSITION;
			}
			positions.push_back(&board[r][c]);
			c++;
		}
		break;
	case WEST:
		for (int i = 1; i <= tam; i++) {
			if (r < 0 || r > 9 || c < 0 || c > 9) {
				throw EXCEPTION_OUTSIDE;
			}
			if (board[r][c].getState() == SHIP) {
				throw EXCEPTION_NONFREE_POSITION;
			}
			positions.push_back(&board[r][c]);
			c--;
		}
		break;
	}
	Ship nuevo(type, positions);
	ships.push_back(nuevo);
}

#include <sstream>
// "B-B3-E     S-J10-N        C-D7-W D-A1-S"
void Player::addShips(string ships) {
	Coordinate origen;
	int row, column;
	ShipType tipo;
	Orientation orientacion;
	stringstream ss;
	string cadena;

	ss << ships;
	while (!ss.eof()) {
		cadena = "";
		ss >> cadena;
		if (cadena != "") {
			tipo = Ship::typeFromChar(cadena[0]);
			row = cadena[2] - 'A';
			int i = 3;
			string aux = "";
			while (cadena[i] != '-') {
				aux += cadena[i];
				i++;
			}
			column = stoi(aux) - 1;
			i++;
			orientacion = Coordinate::orientationFromChar(cadena[i]);
			origen = Coordinate(row, column);
			addShip(origen, tipo, orientacion);
		}
	}
	
}

bool Player::attack(const Coordinate& coord) {
	int posHit;
	bool isHit, allSunk;

	try {
		posHit = -1;
		for (int i = 0; i < ships.size() && posHit == -1; i++) {
			isHit = ships[i].hit(coord);
			if (isHit == true) { 
				posHit = i;
			}
		}
		if (posHit == -1) {
			isHit = false;
			board[coord.getRow()][coord.getColumn()].setState(WATER);
		}
		else {
			if (ships[posHit].getState() == SUNK) {
			
				allSunk = true;
				for (Ship ship : ships) {
					if (ship.getState() != SUNK) {
						allSunk = false;
					}
				}
				if (allSunk) {
					throw EXCEPTION_GAME_OVER;
				}
			}
		}
	}
	catch (Exception e) { // ya estaba hit o sunk
		isHit = false;
	}
	return isHit;
}

bool Player::attack(string coord) {
	Coordinate coordinate(coord);
	bool a = attack(coordinate);
	return a;
}


ostream& operator<<(ostream& os, const Player& player) {
	os << player.name << endl;
	os << " ";
	for (int i = 1; i <= 10; i++) {
		os << " ";
		os << i;
		if (i != 10) {
			os << " ";
		}
	}
	os << endl;

	for (int i = 0; i < 10; i++) {
		os << (char)('A' + i);
		for (int j = 0; j < 10; j++) {
			os << " ";
			if (player.board[i][j].getState() != NONE) {
				os << player.board[i][j].getStateChar();
			}
			else {
				os << " ";
			}
			os << " ";
		}
		os << endl;
	}

	for (int i = 0; i < player.ships.size(); i++) {
		os << player.ships[i] << endl;
	}

	return os;
}




