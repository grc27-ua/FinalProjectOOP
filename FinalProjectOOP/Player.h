#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Coordinate.h"
#include "Ship.h"
#include "Util.h"
#include <vector>
#include <iostream>
using namespace std;

const int BOARDSIZE = 10;
class Player {
	friend ostream& operator<<(ostream& os, const Player& player);
protected:
	string name;
	Coordinate board[BOARDSIZE][BOARDSIZE];
	vector<Ship> ships;
public:
	Player(string name);
	string getName() const;
	void addShip(const Coordinate& pos, ShipType type, Orientation orientation);
	void addShips(string ships);
	bool attack(const Coordinate& coord);
	bool attack(string coord);
};

#endif#pragma once
