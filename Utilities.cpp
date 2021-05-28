#include "Utilities.h"

bool just_play = false, is_exit = false, mute = false;
int WIDTH = 15, HEIGHT = 15, END_LEVEL = 20,
level = 1, health = 3, ammo = 0, charged = 3,
vaccine = 0, kill = 0, range_gun = 5, credit = 0,
round_num = 0, magazine_capacity = 3;

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
	cout << question_with_enter << "type y for yes or n for no:" << endl;
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
