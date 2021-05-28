#include "Coordinate.h"
Coordinate::Coordinate(int Xcor, int Ycor) {
	this->Xcor = Xcor;
	this->Ycor = Ycor;
}
void Coordinate::move(char key, int HEIGHT, int WIDTH) {
	switch (key) {
	case 'w': if (Ycor - 1 >= 0) Ycor--; break;
	case 's': if (Ycor + 1 <= HEIGHT - 1) Ycor++; break;
	case 'd': if (Xcor + 1 <= WIDTH - 1) Xcor++; break;
	case 'a': if (Xcor - 1 >= 0) Xcor--; break;
	}
}
void Coordinate::goto_cordnate(int Xcord, int Ycord) {
	Xcor = Xcord;
	Ycor = Ycord;
}
int Coordinate::get_Xcor() { return Xcor; }
int Coordinate::get_Ycor() { return Ycor; }