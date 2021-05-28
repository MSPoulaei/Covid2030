#pragma once
#ifndef _ITEM_
#define _ITEM_
#include "Coordinate.h"
class Item {

private:
	Coordinate coordinate;
	char pic;
public:
	Item();
	~Item();
	Item(char,int, int );
	void set_pic(char&);
	char& get_pic();
	Coordinate& get_coordinate();
};
#endif