#include "Item.h"
Item::Item() {}
Item::~Item() { delete this; }
Item::Item(char pic, int Xcor, int Ycor)
	:coordinate(Xcor, Ycor) {
	this->pic = pic;
}
void Item::set_pic(char& mark) { pic = mark; }
char& Item::get_pic() { return pic; }
Coordinate& Item::get_coordinate() { return coordinate; }