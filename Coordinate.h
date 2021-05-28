
#ifndef _COORDINATE_
#define _COORDINATE_
class Coordinate {
	friend class Item;
	friend class Item_Interface;
	friend void print_screen();
private:
	int Xcor;
	int Ycor;
public:
	Coordinate();
	~Coordinate();
	Coordinate(int, int);
	void move(char, int, int);
	void goto_cordnate(int, int);
	int get_Xcor();
	int get_Ycor();
};
#endif