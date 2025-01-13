#pragma once
#ifndef COORDINATE_H_
#define COORDINATE_H_
#include <iostream>
using namespace std;


enum CellState {
	NONE,
	SHIP,
	HIT,
	WATER
};

enum Orientation {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Coordinate {
	friend ostream& operator<<(ostream& os, const Coordinate& c);
protected:
	int row;
	int column;
	CellState state;
public:
	Coordinate();
	Coordinate(int row, int column);
	Coordinate(string coord);
	int getRow() const;
	int getColumn() const;
	CellState getState() const;

	char getStateChar() const;

	void setRow(int row);
	void setColumn(int column);
	void setState(CellState state);

	bool compare(const Coordinate& coord) const;
	Coordinate addOffset(int offset, Orientation orientation) const;

	static Orientation orientationFromChar(char orientation);

};
#endif