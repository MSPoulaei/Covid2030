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
 Item_Interface Player(PLAYER_CHAR, 0, 0);
 Item_Interface Door(DOOR_CHAR, WIDTH - 1, HEIGHT - 1);
 string itos(int num) {
	 string res = "", revert;
	 while (num > 0) {
		 revert += char(num % 10 + 48);
		 num /= 10;
	 }
	 for (int i = revert.size() - 1; i >= 0; i--) {
		 res += revert[i];
	 }
	 return res;
 }
void get_level_info_from_file(int level)
{
	//clear last items
	Item_Interface::Zombies.clear();
	Item_Interface::Vaccines.clear();
	Item_Interface::Ammunition.clear();

	string p1 = "Assets/levels/file_level_"; p1 += itos(level); /*char(level + 48);*/ string address = p1 + ".txt";
	ifstream infile(address, ios::in);
	if (!infile) {
		cerr << "file not found!" << endl;
		exit(1);
	}
	infile >> WIDTH >> HEIGHT;
	int x, y;
	for (int i = 0; i < level; i++) {
		infile >> x >> y;
		Item_Interface::Zombies.push_back(Item_Interface(ZOMBIE_CHAR, x, y));
	}
	for (int i = 0; i < level; i++) {
		infile >> x >> y;
		Item_Interface::Vaccines.push_back(Item_Interface(VACCINE_CHAR, x, y));
	}
	for (int i = 0; i < level; i++) {
		if (i % 2 == 1)
			continue;
		infile >> x >> y;
		Item_Interface::Ammunition.push_back(Item_Interface(AMMO_CHAR, x, y));
	}
	infile.close();
	//reset Player and door position
	Player.get_coordinate().goto_cordnate(0, 0);
	Door.get_coordinate().goto_cordnate(WIDTH - 1, HEIGHT - 1);
}
void print_screen() {
	//if(round!=0)
	//cout << "a" << endl;//
	//system("cls");
	Clear_scr();
	/*if(!first_run)
		cout << "\033[2J\033[1;1H";*/

	print_score_board();
	for (int i = 0; i < WIDTH + 2; ++i)
		cout << '-';
	cout << endl;
	//
	for (int i = 0; i < HEIGHT; ++i) {//print row
		cout << '|';
		for (int j = 0; j < WIDTH; ++j) {
			if (Player.get_coordinate().Xcor == j && Player.get_coordinate().Ycor == i) {
				cout << GREEN << Player.get_pic() << RESET;
				continue;
			}
			else if (Door.get_coordinate().Xcor == j && Door.get_coordinate().Ycor == i) {
				cout << MAGENTA << Door.get_pic() << RESET;
				continue;
			}
			bool broken = false;
			for (int a = 0; a < Item_Interface::Zombies.size(); a++)
			{
				if (Item_Interface::Zombies[a].get_coordinate().Xcor == j && Item_Interface::Zombies[a].get_coordinate().Ycor == i) {
					cout << RED << Item_Interface::Zombies[a].get_pic() << RESET;
					broken = true;
					break;
				}
			}
			if (broken)
				continue;
			for (int c = 0; c < Item_Interface::Vaccines.size(); c++)
			{

				if (Item_Interface::Vaccines[c].get_coordinate().Xcor == j && Item_Interface::Vaccines[c].get_coordinate().Ycor == i) {
					cout << YELLOW << Item_Interface::Vaccines[c].get_pic() << RESET;
					broken = true;
					break;
				}

			}
			if (broken)
				continue;
			for (int c = 0; c < Item_Interface::Ammunition.size(); c++)
			{

				if (Item_Interface::Ammunition[c].get_coordinate().Xcor == j && Item_Interface::Ammunition[c].get_coordinate().Ycor == i) {

					cout << BLUE << Item_Interface::Ammunition[c].get_pic() << RESET;
					broken = true;
					break;
				}

			}
			if (broken)
				continue;
			cout << EMPTY_CHAR;
		}
		cout << '|' << endl;
	}
	for (int i = 0; i < WIDTH + 2; ++i)
		cout << '-';
	cout << endl;
}