#include "Item_Interface.h"
Item_Interface::Item_Interface() {}
//Item_Interface::~Item_Interface() { delete ptr; }
Item_Interface::Item_Interface(char pic, int Xcor, int Ycor) :ptr(new Item(pic, Xcor, Ycor)) {}
void Item_Interface::set_pic(char mark) {
	ptr->set_pic(mark);
}
char Item_Interface::get_pic() {
	return ptr->get_pic();
}
Coordinate& Item_Interface::get_coordinate() { return ptr->get_coordinate(); }
bool Item_Interface::operator==(Item_Interface& item2) {
	return (ptr->get_coordinate().Xcor == item2.get_coordinate().Xcor &&
		ptr->get_coordinate().Ycor == item2.get_coordinate().Ycor);
}


Array<Item_Interface> Item_Interface::Zombies;
Array<Item_Interface> Item_Interface::Vaccines;
Array<Item_Interface> Item_Interface::Ammunition;