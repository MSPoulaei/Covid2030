#include "Utilities.h"
#include "User.h"
using namespace std;

void Exit_game() {
	play_sound(L"Assets/sound/dornandaz.wav");
	//PlaySound(L"Assets/sound/dornandaz.wav", NULL, SND_ASYNC | SND_FILENAME);
	cout << "Good Bye!" << endl;
	if (!mute)
		sleep_sec(15);
	//exit(1);
}
template<typename T1>
void reset_value(T1& name, T1 value) {
	name = value;
}
void reset_values() {
	reset_value(level, 1);
	reset_value(vaccine, 0);
	reset_value(health, 3);
	reset_value(ammo, 0);
	reset_value(charged, 3);
	reset_value(kill, 0);
	reset_value(range_gun, 5);
	reset_value(credit, 0);
	reset_value(round_num, 0);
	reset_value(magazine_capacity, 3);
}
void Upgrade_item(const int& credit_needed, int& item, const int max_item, string item_text) {
	if (item < max_item) {
		if (credit >= credit_needed) {
			credit -= credit_needed;
			cout << "Upgrade done successfully.Your " << item_text << " is now " << ++item << "." << endl;
		}
		else
			cout << "Unfortunately, your credit is not enough to get this item. Please gain " << credit_needed - credit << " more credit by playing." << endl;;
	}
	else
		cout << "The selected item is maximum." << endl;
}
void base_menu() {
	bool broken = false;
	while (!broken) {

		Clear_scr();
		print_score_board();
		int mag_credit = magazine_capacity * level,
			range_credit = range_gun + level,
			health_credit = health * (level + 1);
		char input_menu;
		enum upgrade_menu_items { Return_to_game = 48, Upgrade_capacity_of_magazine, Upgrade_range_of_shotgun, Get_an_additional_health };
		cout << "0 - Return to game" << endl
			<< "1 - Upgrade capacity of magazine : 1 bullet (maximum is " << MAX_MAG_CAP << " bullets, now is " << magazine_capacity << ") , Credit required: " << mag_credit << endl
			<< "2 - Upgrade range of shotgun : 1 times the size of the person himself (maximum is " << MAX_GUN_RANGE << " times, now is " << range_gun << ") , Credit required: " << range_credit << endl
			<< "3 - Get an additional health (maximum is " << MAX_HEALTH << " healths, now is " << health << ") , Credit required: " << health_credit << endl;

		cin >> input_menu;
		switch (input_menu)
		{
		case Return_to_game:
			broken = true;
			break;
		case Upgrade_capacity_of_magazine://magazine
			Upgrade_item(mag_credit, magazine_capacity, MAX_MAG_CAP, "magazine capacity");
			break;
		case Upgrade_range_of_shotgun://range_gun
			Upgrade_item(range_credit, range_gun, MAX_GUN_RANGE, "shotgun range");
			break;
		case Get_an_additional_health://health
			Upgrade_item(health_credit, health, MAX_HEALTH, "health");
			break;
		default:
			cout << "Please just enter the numbers in the menu:" << endl;
			break;
		}
		if (!broken)
			sleep_sec(2);
	}
}
void print_score_board() {
	//score board
	cout << "Level: " << level << "  Vaccine: " << vaccine << "  Credit: " << credit << "  Round: " << round_num << endl;
	cout << "Health: [ ";
	for (int i = 0; i < health; i++)
		cout << "| ";
	cout << "] ";

	cout << "Ammo: " << charged << '/' << ammo << " Kill: " << kill << endl; ;

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
void Clear_scr()
{
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif
}
void sleep_sec(float seconds) {
	clock_t startClock = clock();
	float secondsAhead = seconds * CLOCKS_PER_SEC;
	// do nothing until the elapsed time has passed.
	while (clock() < startClock + secondsAhead);
	return;
}
void char_to_lower(char& character) {
	if (character <= 'Z' && character >= 'A')
		character -= ('A' - 'a');
	return;
}
void get_level_info_from_file(int level)
{
	//clear last items
	Item_Interface::Zombies.clear();
	Item_Interface::Vaccines.clear();
	Item_Interface::Ammunition.clear();

	string p1 = "Assets/levels/file_level_"; p1 += char(level + 48); string address = p1 + ".txt";
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
void write_max_level(int& max_level)
{
	ofstream f("Assets/data/max_level_file.dat", ios::out);
	f.write(reinterpret_cast<char*>(&max_level), sizeof(int));
	f.close();
}
void read_max_level()
{
	ifstream in_max_level_file("Assets/data/max_level_file.dat", ios::in);
	if (!in_max_level_file) {
		write_max_level(END_LEVEL);
		return;
	}
	in_max_level_file.read(reinterpret_cast<char*>(&END_LEVEL), sizeof(int));
	in_max_level_file.close();
}
void Credits_print() {
	string text = "\t\t\tMohammad Sadegh Poulaei\n\t\t\t     Mousa Salehi\n\t\t\tMohammadReza SaemiPour";

	for (int i = 20; i > 0; i--)
	{
		Clear_scr();
		for (int j = 0; j < i; j++)
		{
			cout << '\n';
		}
		cout << text << endl;
		sleep_sec(0.1);
	}
	sleep_sec(2);
}
void Reset_game() {
	reset_values();
	read_max_level();
	get_level_info_from_file(level);
}
void Settings_menu() {
	cout << "Final level is: " << END_LEVEL << endl;
	cout << ((mute) ? "Sound is mute!" : "Sound is not mute!") << endl;
	if (ask_yn(((mute) ? "Do you want to unmute the sound?\n" : "Do you want to mute the sound?\n"))) {
		mute = !mute;
		if (!just_play && ask_yn("Are you sure you want to save current stage?"))
			user.Save();
	}

	else
		;
}
bool play_sound(LPCWSTR  path) {
	bool work_good = false;
	if (!mute) {
		if (PlaySound(path, NULL, SND_ASYNC | SND_FILENAME))
			work_good = true;
		else
			cout << "file not found!" << endl;
	}
	return work_good;
}
bool ask_yn(string question_with_enter) {
	cout << question_with_enter;
	char yn;
	bool broken = false, result;
	do {
		cin >> yn;
		char_to_lower(yn);
		switch (yn)
		{
		case 'y':
			result = true;
			broken = true;
			break;
		case 'n':
			result = false;
			broken = true;
			break;
		default:
			cout << "Please just enter y for yes or n for no:" << endl;
			break;
		}
	} while (!broken);
	return result;
}
void Register() {
	bool passed_reg_stage = false;
	user = User();
	do {
		if (ask_yn("Are you a new user?\n")) {
			if (ask_yn("Would you like to sign up?\n")) {
				passed_reg_stage = user.Sign_up();
				just_play = !passed_reg_stage;
			}
			else {
				just_play = true;
				passed_reg_stage = true;
			}
		}
		else {
			passed_reg_stage = user.Login();
			just_play = !passed_reg_stage;
		}
	} while (!passed_reg_stage);
}