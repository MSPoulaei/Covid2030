
#ifndef _ITEM_INTERFACE_
#define _ITEM_INTERFACE_
//#ifndef _ITEM_
#include "Item.h"
//#endif
//#ifndef _ARRAY_
#include "Array.h"
//#endif

class Item_Interface {
public:
	Item_Interface();
	//~Item_Interface();
	Item_Interface(char, int, int);
	void set_pic(char);
	char get_pic();
	Coordinate& get_coordinate();
	bool operator==(Item_Interface&);
	static Array<Item_Interface> Ammunition;
	static Array<Item_Interface> Zombies;
	static Array<Item_Interface> Vaccines;
private:
	Item* ptr;
};
static Item_Interface Player(PLAYER_CHAR, 0, 0);
static Item_Interface Door(DOOR_CHAR, WIDTH - 1, HEIGHT - 1);
void print_screen();
void get_level_info_from_file(int);
#endif