#include <iostream>
#include <fstream>
//#include <stdlib.h>
#include <ctime>
//#include <cstdlib>
//#include <stdlib.h>
#include <vector>
#include <Windows.h>
#include <string>
#include <MMSystem.h>
#include <algorithm>
#include <wchar.h>
//#define WIDTH 30
//#define HEIGHT 30

#define PLAYER_CHAR 'P'
#define ZOMBIE_CHAR 'Z'
#define VACCINE_CHAR 'V'
#define AMMO_CHAR 'A'
#define DOOR_CHAR 'D'
#define EMPTY_CHAR ' '
#define MAX_MAG_CAP 7
#define MAX_GUN_RANGE 10
#define MAX_HEALTH 5
#define LOGO " ######   #######  ##     ## #### ########      #######    #####    #######    #####   \n\
##    ## ##     ## ##     ##  ##  ##     ##    ##     ##  ##   ##  ##     ##  ##   ##  \n\
##       ##     ## ##     ##  ##  ##     ##           ## ##     ##        ## ##     ## \n\
##       ##     ## ##     ##  ##  ##     ##     #######  ##     ##  #######  ##     ## \n\
##       ##     ##  ##   ##   ##  ##     ##    ##        ##     ##        ## ##     ## \n\
##    ## ##     ##   ## ##    ##  ##     ##    ##         ##   ##  ##     ##  ##   ##  \n\
######   #######     ###    #### ########     #########   #####    #######    #####   "
//#include <unistd.h>
//#include <termios.h>
using namespace std;
bool just_play = false, is_exit = false, mute = false;
int WIDTH = 15, HEIGHT = 15, END_LEVEL = 15;
int level = 1, health = 3, ammo = 0, charged = 3,
vaccine = 0, kill = 0, range_gun = 5, credit = 0,
round_num = 0, magazine_capacity = 3;
//char keys_chars[12] = { 'w','a','s','d','t','f','g','h','r','e','u','m'};
//char getch() {
//    char buf = 0;
//    struct termios old = { 0 };
//    if (tcgetattr(0, &old) < 0)
//        perror("tcsetattr()");
//    old.c_lflag &= ~ICANON;
//    old.c_lflag &= ~ECHO;
//    old.c_cc[VMIN] = 1;
//    old.c_cc[VTIME] = 0;
//    if (tcsetattr(0, TCSANOW, &old) < 0)
//        perror("tcsetattr ICANON");
//    if (read(0, &buf, 1) < 0)
//        perror("read()");
//    old.c_lflag |= ICANON;
//    old.c_lflag |= ECHO;
//    if (tcsetattr(0, TCSADRAIN, &old) < 0)
//        perror("tcsetattr ~ICANON");
//    return (buf);
//}
bool file_exist(string path) {
	bool exist;
	ifstream inFile(path, ios::in);
	if (!inFile)
		exist = false;
	else
		exist = true;
	inFile.close();
	return exist;
}
template<typename T>
class Array {
private:
	int max_size;
	int add_size;
	int size_num;
	T* arr = new T[max_size];
public:
	Array(int max_siz = 30, int add_siz = 30) :max_size(max_siz), add_size(add_siz), size_num(0) {}
	~Array() { delete[] arr; }
	void push_back(const T& v) {
		if (size_num == max_size) {
			max_size += add_size;
			T* arra = new T[max_size];
			for (int i = 0; i < size_num; i++)
				arra[i] = arr[i];
			arr = arra;
		}
		arr[size_num++] = T(v);// copy constructor
	}
	void erase(const int& index) {
		for (int i = index; i < size_num - 1; i++)
			arr[i] = arr[i + 1];
		size_num--;
	}
	int size() {
		return size_num;
	}
	void clear() {
		size_num = 0;
	}
	T& operator[](const int& index) {
		return arr[index];
	}
	void operator=(const Array& v) {
		this->size_num = v.size_num;
		//for(int i=0;i<v.size_num;i++)
            //this->arr[i] = v.arr[i];
        this->arr = v.arr;
        this->add_size = v.add_size;
        this->max_size = v.max_size;
	}
	int begin() { return 0; }
	int end() { return size_num - 1; }
};
class Coordinate {
	friend class Item;
	friend class Item_Interface;
	friend void print_screen();
private:
	int Xcor;
	int Ycor;
public:
	Coordinate() {}
	~Coordinate() {}
	Coordinate(int Xcor, int Ycor) {
		this->Xcor = Xcor;
		this->Ycor = Ycor;
	}
	void move(char key, int HEIGHT, int WIDTH) {
		switch (key) {
		case 'w': if (Ycor - 1 >= 0) Ycor--; break;
		case 's': if (Ycor + 1 <= HEIGHT - 1) Ycor++; break;
		case 'd': if (Xcor + 1 <= WIDTH - 1) Xcor++; break;
		case 'a': if (Xcor - 1 >= 0) Xcor--; break;
		}
	}
	void goto_cordnate(int Xcor, int Ycor) {
		this->Xcor = Xcor;
		this->Ycor = Ycor;
	}
	int get_Xcor() { return Xcor; }
	int get_Ycor() { return Ycor; }
};
class Item {

private:
	Coordinate coordinate;
	char pic;
public:
	Item() {}
	~Item() { delete this; }
	Item(char pic, int Xcor = rand() % (WIDTH - 5) + 5, int Ycor = rand() % (HEIGHT - 5) + 5)
		:coordinate(Xcor, Ycor) {
		this->pic = pic;
	}
	/*static Item Player;
	static Item Door;*/


	void set_pic(char& mark) { pic = mark; }
	char& get_pic() { return pic; }
	Coordinate& get_coordinate() { return coordinate; }
	/*bool operator==(Item& item2) {
		return (this->coordinate.Xcor == item2.coordinate.Xcor &&
			this->coordinate.Ycor == item2.coordinate.Ycor);
	}*/

};
class Item_Interface {
public:
	Item_Interface() {}
	//~Item_Interface() { delete ptr; }
	Item_Interface(char pic, int Xcor, int Ycor) :ptr(new Item(pic, Xcor, Ycor)) {}
	void set_pic(char mark) {
		ptr->set_pic(mark);
	}
	char get_pic() {
		return ptr->get_pic();
	}
	Coordinate& get_coordinate() { return ptr->get_coordinate(); }
	void goto_cordnate(Coordinate& c) {
	    ptr->get_coordinate().goto_cordnate(c.Xcor, c.Ycor);
	}
	bool operator==(Item_Interface& item2) {
		return (ptr->get_coordinate().Xcor == item2.get_coordinate().Xcor &&
			ptr->get_coordinate().Ycor == item2.get_coordinate().Ycor);
	}
	static Array<Item_Interface> Ammunition;
	static Array<Item_Interface> Zombies;
	static Array<Item_Interface> Vaccines;
private:
	Item* ptr;
};

static Item_Interface Player(PLAYER_CHAR, 0, 0);
static Item_Interface Door(DOOR_CHAR, WIDTH - 1, HEIGHT - 1);
Array<Item_Interface> Item_Interface::Zombies;
Array<Item_Interface> Item_Interface::Vaccines;
Array<Item_Interface> Item_Interface::Ammunition;

class User {
	//friend string Login_user_name();
private:
	string user_name;
	string password;
	string file_path;
	bool _mute;
	int _level, _health, _ammo, _charged, _vaccine,
		_kill, _range_gun, _credit, _round_num, _magazine_capacity;
	//char keys[12];
	static const int max_user_pass_length;
	static const int min_user_pass_length;
	Item_Interface _Player;
	Array<Item_Interface> _Zombies;
	Array<Item_Interface> _Vaccines;
	Array<Item_Interface> _Ammunition;
	void reset_values() {
		_level = 1;
		_vaccine = 0;
		_health = 3;
		_ammo = 0;
		_charged = 3;
		_kill = 0;
		_range_gun = 5;
		_credit = 0;
		_round_num = 0;
		_magazine_capacity = 3;
		_mute = false;
		/*keys[0] = 'w';
		keys[1] = 'a';
		keys[2] = 's';
		keys[3] = 'd';
		keys[4] = 't';
		keys[5] = 'f';
		keys[6] = 'g';
		keys[7] = 'h';
		keys[8] = 'r';
		keys[9] = 'e';
		keys[10] = 'u';
		keys[11] = 'm';*/
	}
	static bool string_check_numeric(string text) {
		for (int i = 0; i < text.length(); i++)
			if (!(text[i] >= '0' && text[i] <= '9'))
				return false;
		return true;
	}
	static bool check_user_name(string user_name) {
		if (user_name.length() > max_user_pass_length || user_name.length() < min_user_pass_length)
			{
				cout << "invalid input! try again:" << endl;
				return false;
			}
		for (int i = 0; i < user_name.length(); i++)
			if (!(
				(user_name[i] >= 'a' && user_name[i] <= 'z') ||
				(user_name[i] >= 'A' && user_name[i] <= 'Z') ||
				(user_name[i] >= '0' && user_name[i] <= '9')
				)) {
				cout << "invalid input! try again:" << endl;
				return false;
			}
		return true;
	};
	static bool check_password(string password) {
		if (password.length() > max_user_pass_length || password.length() < min_user_pass_length)
			{
				cout << "invalid input! try again:" << endl;
				return false;
			}
		if (string_check_numeric(password)) {
			cout << "password should't contain only numbers!" << endl;
			return false;
		}
		for (int i = 0; i < password.length(); i++)
			if (!(
				(password[i] >= 'a' && password[i] <= 'z') ||
				(password[i] >= 'A' && password[i] <= 'Z') ||
				(password[i] >= '0' && password[i] <= '9') ||
				(password[i] >= '#' && password[i] <= '&') ||
				(password[i] >= '(' && password[i] <= '-') ||
				(password[i] >= '^' && password[i] <= '_') ||
				(password[i] == '=')
				)) {
				cout << "invalid input! try again:" << endl;
				return false;
			}
		return true;
	};
    void Save_file(){
        string address = "Assets/users/" + user_name + ".txt";
        ofstream f(address, ios::out);
        f << password << endl;
        f << _level << " " << _vaccine << " " << _credit << " " << _round_num << endl;
        f << _health << " " << _ammo << " " << _charged << " " << _kill << endl;
        int mute = _mute;
        f << _range_gun << " " << _magazine_capacity << " " << mute << endl;
        f << _Player.get_coordinate().get_Xcor() << " " << _Player.get_coordinate().get_Ycor() << endl;
        f << _Zombies.size() << " " << _Vaccines.size() << " " << _Ammunition.size() << endl;
        for(int i=0;i<_Zombies.size();i++)
            f << _Zombies[i].get_coordinate().get_Xcor() << " " << _Zombies[i].get_coordinate().get_Ycor() << endl;
        for(int i=0;i<_Vaccines.size();i++)
            f << _Vaccines[i].get_coordinate().get_Xcor() << " " << _Vaccines[i].get_coordinate().get_Ycor() << endl;
        for(int i=0;i<_Ammunition.size();i++)
            f << _Ammunition[i].get_coordinate().get_Xcor() << " " << _Ammunition[i].get_coordinate().get_Ycor() << endl;
        f.close();
    }
    void Load_file(){
        string address = "Assets/users/" + user_name + ".txt";
        ifstream f(address, ios::in);
        f >> password;
        f >> _level >> _vaccine >> _credit >> _round_num;
        f >> _health >> _ammo >> _charged >> _kill;
        int mute;
        f >> _range_gun >> _magazine_capacity >> mute;
        _mute = false;
        if(mute)    _mute = true;
        int x, y;
        f >> x >> y;
        _Player = Item_Interface(PLAYER_CHAR, x, y);
        int zombie_size, vaccine_size, ammunition_size;
        f >> zombie_size >> vaccine_size >> ammunition_size;
        _Zombies.clear();_Vaccines.clear();_Ammunition.clear();
        for(int i=0;i<zombie_size;i++){
            f >> x >> y;
            _Zombies.push_back(Item_Interface(ZOMBIE_CHAR, x, y));
        }
        for(int i=0;i<vaccine_size;i++){
            f >> x >> y;
            _Vaccines.push_back(Item_Interface(VACCINE_CHAR, x, y));
        }
        for(int i=0;i<ammunition_size;i++){
            f >> x >> y;
            _Ammunition.push_back(Item_Interface(AMMO_CHAR, x, y));
        }
        f.close();
    }
public:
	User() {}
	~User() {}
	bool Sign_up() {
		cout << "(notes: username or password should contain at least " << min_user_pass_length
			<< " and at most" << max_user_pass_length
			<< "characters, legal chars for username {a-z,A-Z,0-9} space is illegal, " << endl
			<< "legal chars for password {a-z,A-Z,0-9,@#$%^&*()_+=-,} space is illegal and it should't contain only numbers)" << endl;
		cout << "Enter your User Name:" << endl;
		do {
			cin >> user_name;
		} while (!check_user_name(user_name));
		file_path = "Assets/users/" + user_name + ".txt";
		if (file_exist(file_path)) {
			cout << "User with the same user name found! please log in" << endl;
			return false;
		}
		cout << "Enter your password:" << endl;
		do {
			cin >> password;
		} while (!check_password(password));
		//reset_values();
		Save();
		cout << "User with username:" << user_name << " and password:" << password << " has been registered successfully" << endl;
		return true;
	}
	bool Login() {
		string password;
		cout << "(notes: username or password should contain at least " << User::min_user_pass_length
			<< " and at most" << User::max_user_pass_length
			<< "characters, legal chars for username {a-z,A-Z,0-9} space is illegal, " << endl
			<< "legal chars for password {a-z,A-Z,0-9,@#$%^&*()_+=-,} space is illegal and it should't contain only numbers)" << endl;
		cout << "Enter your User Name:" << endl;
		do {
			cin >> user_name;
		} while (!User::check_user_name(user_name));
		file_path = "Assets/users/" + user_name + ".txt";
		if (!file_exist(file_path)) {
			cout << "User name not found! please sign up!" << endl;
			return false;
		}

        Load();

		cout << "Enter your password:" << endl;
		do {
			cin >> password;
		} while (!check_password(password));
		if (password == this->password) {
			cout << "password is correct" << endl
				<< "All your data is loaded!" << endl;
			Load();
			return true;
		}
		else
			cout << "password is incorrect" << endl;
		return false;
	}
	void Load() {
	    Load_file();
		level = _level;
		health = _health;
		ammo = _ammo;
		charged = _charged;
		vaccine = _vaccine;
		kill = _kill;
		range_gun = _range_gun;
		credit = _credit;
		round_num = _round_num;
		magazine_capacity = _magazine_capacity;
		mute = _mute;

		Player.goto_cordnate(_Player.get_coordinate());
        for(int i=0;i<_Zombies.size();i++)
            Item_Interface::Zombies[i].goto_cordnate(_Zombies[i].get_coordinate());
        if(Item_Interface::Zombies.size() > _Zombies.size()){
            int i = _Zombies.size();
            while(Item_Interface::Zombies.size() > _Zombies.size()){
                Item_Interface::Zombies.erase(Item_Interface::Zombies.begin() + i);
                i++;
            }
        }

        for(int i=0;i<_Vaccines.size();i++)
            Item_Interface::Vaccines[i].goto_cordnate(_Vaccines[i].get_coordinate());
        if(Item_Interface::Vaccines.size() > _Vaccines.size()){
            int i = _Vaccines.size();
            while(Item_Interface::Vaccines.size() > _Vaccines.size()){
                Item_Interface::Vaccines.erase(Item_Interface::Vaccines.begin() + i);
                i++;
            }
        }

        for(int i=0;i<_Ammunition.size();i++)
            Item_Interface::Ammunition[i].goto_cordnate(_Ammunition[i].get_coordinate());
        if(Item_Interface::Ammunition.size() > _Ammunition.size()){
            int i = _Ammunition.size();
            while(Item_Interface::Ammunition.size() > _Ammunition.size()){
                Item_Interface::Ammunition.erase(Item_Interface::Ammunition.begin() + i);
                i++;
            }
        }
	}
	void Save() {
		_level = level;
		_health = health;
		_ammo = ammo;
		_charged = charged;
		_vaccine = vaccine;
		_kill = kill;
		_range_gun = range_gun;
		_credit = credit;
		_round_num = round_num;
		_magazine_capacity = magazine_capacity;
		_mute = mute;

		/*_Player.goto_cordnate(Player.get_coordinate());
        for(int i=0;i<Item_Interface::Zombies.size();i++)
            _Zombies[i].goto_cordnate(Item_Interface::Zombies[i].get_coordinate());
        if(_Zombies.size() > Item_Interface::Zombies.size())
            for(int i=Item_Interface::Zombies.size();i<_Zombies.size();i++)
                _Zombies.erase(_Zombies.begin() + i);
        for(int i=0;i<Item_Interface::Vaccines.size();i++)
            _Vaccines[i].goto_cordnate(Item_Interface::Vaccines[i].get_coordinate());
        if(_Vaccines.size() > Item_Interface::Vaccines.size())
            for(int i=Item_Interface::Vaccines.size();i<_Vaccines.size();i++)
                _Vaccines.erase(_Vaccines.begin() + i);
        for(int i=0;i<Item_Interface::Ammunition.size();i++)
            _Ammunition[i].goto_cordnate(Item_Interface::Ammunition[i].get_coordinate());
        if(_Ammunition.size() > Item_Interface::Ammunition.size())
            for(int i=Item_Interface::Ammunition.size();i<_Ammunition.size();i++)
                _Ammunition.erase(_Ammunition.begin() + i);*/
		Save_file();
	}

};

const int User::max_user_pass_length = 20;
const int User::min_user_pass_length = 4;
User user;


//string Login_user_name() {
//	string user_name;
//	cout << "(notes: username or password should contain at least " << User::min_user_pass_length
//		<< " and at most" << User::max_user_pass_length
//		<< "characters, legal chars for username {a-z,A-Z,0-9} space is illegal, " << endl
//		<< "legal chars for password {a-z,A-Z,0-9,@#$%^&*()_+=-,} space is illegal and it should't contain only numbers)" << endl;
//	cout << "Enter your User Name:" << endl;
//	do {
//		cin >> user_name;
//	} while (!User::check_user_name(user_name));
//	string file_path = "Assets/users/" + user_name + ".bin";
//	if (!file_exist(file_path)) {
//		cout << "User name not found! please sign up!" << endl;
//		return "";
//	}
//	return file_path;
//}
//void reset_keys();
void Reset_game();
void Exit_game();
void print_screen();
void print_score_board();
void Upgrade_item(const int&, int&, const int, string);
void base_menu();
void reset_values();
void get_level_info_from_file(int);
void Clear_scr();
void sleep_sec(float);
void char_to_lower(char&);
void read_max_level();
void write_max_level(int& max_level);
void Credits_print();
bool ask_yn(string question_with_enter = "") {
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
			}
			else {
				just_play = true;
				passed_reg_stage = true;
			}
		}
		else {
			passed_reg_stage = user.Login();
		}
	} while (!passed_reg_stage);
}

//bool play_sound(LPCWSTR  path) {
//	return PlaySound(path, NULL, SND_ASYNC | SND_FILENAME);
//}
int main() {

	cout << LOGO << endl;
	cout << "Welcome to Covid 2030 game!\n";
	Register();

	while (!is_exit) {
		char yn = ' ', main_menu;			//'0'
		enum main_menu_items { Register_stage = 48, New_Game, Settings, Credits, Exit };
		//srand(time(0));//srand(10);//quera
		Clear_scr();
		cout << "0 - Register\n"
			<< "1 - New Game\n"
			<< "2 - Settings\n"
			<< "3 - Credits\n"
			<< "4 - Exit" << endl;
		cin >> main_menu;
		switch (main_menu)
		{
		case Register_stage:
			if (ask_yn("Warning: if you have already loged in you'll be loged out and your unsaved data will be lost.Would you like to continue?\n"))
				Register();
			break;
		case New_Game:
			//if (main_menu != Load)
				reset_values();
			//while bazi
			while (true) {

				read_max_level();
				get_level_info_from_file(level);

				bool game_is_on = true, won = false;
				round_num = 0;
				while (game_is_on) {
					print_screen();
					char key;
					cin >> key;//key = getch();
					char_to_lower(key);
					round_num++;
					//first_run = false;
					enum keys {
						MV_UP = 'w', MV_DOWN = 's', MV_RIGHT = 'd', MV_LEFT = 'a',
						SH_UP = 't', SH_DOWN = 'g', SH_RIGHT = 'h', SH_LEFT = 'f',
						RELOAD_KEY = 'r', EXIT_KEY = 'e', UPGRADE_KEY = 'u', MENU_KEY = 'm'
					};

					switch (key) {
					case MV_UP: case MV_LEFT: case MV_DOWN: case MV_RIGHT:
						Player.get_coordinate().move(key, HEIGHT, WIDTH);//player
						break;
					case SH_UP: case SH_DOWN: case SH_RIGHT:case SH_LEFT: {
						if (charged > 0) {
							charged--;
							//PlaySound(L"Assets/sound/gun shot.wav", NULL, SND_ASYNC | SND_FILENAME);
							//-//-//PlaySound(TEXT("Assets/sound/gun shot.wav"), NULL, SND_ASYNC | SND_FILENAME);
							//LPCWSTR  a1 = L"Assets/sound/gun shot.wav";
							//PlaySound((a1), NULL, SND_ASYNC | SND_FILENAME);
							int index = -1;
							bool found = false;
							bool not_in_range = false;
							vector < int > cor_diff;
							vector < int > indexes;
							for (int i = 0; i < Item_Interface::Zombies.size(); i++)
							{
								if (key == SH_DOWN) {
									if (Item_Interface::Zombies[i].get_coordinate().get_Xcor() == Player.get_coordinate().get_Xcor()
										&& Item_Interface::Zombies[i].get_coordinate().get_Ycor() >= Player.get_coordinate().get_Ycor()) {

										if (Item_Interface::Zombies[i].get_coordinate().get_Ycor() - Player.get_coordinate().get_Ycor() <= range_gun) {
											cor_diff.push_back(Item_Interface::Zombies[i].get_coordinate().get_Ycor() - Player.get_coordinate().get_Ycor());
											indexes.push_back(i);
											found = true;
										}
										else
											not_in_range = true;
									}
								}

								else if (key == SH_UP) {
									if (Item_Interface::Zombies[i].get_coordinate().get_Xcor() == Player.get_coordinate().get_Xcor()
										&& Item_Interface::Zombies[i].get_coordinate().get_Ycor() <= Player.get_coordinate().get_Ycor()) {
										if (Player.get_coordinate().get_Ycor() - Item_Interface::Zombies[i].get_coordinate().get_Ycor() <= range_gun) {
											cor_diff.push_back(Player.get_coordinate().get_Ycor() - Item_Interface::Zombies[i].get_coordinate().get_Ycor());
											indexes.push_back(i);
											found = true;
										}
										else
											not_in_range = true;
									}
								}
								else if (key == SH_RIGHT) {
									if (Item_Interface::Zombies[i].get_coordinate().get_Ycor() == Player.get_coordinate().get_Ycor()
										&& Item_Interface::Zombies[i].get_coordinate().get_Xcor() >= Player.get_coordinate().get_Xcor()) {
										if (Item_Interface::Zombies[i].get_coordinate().get_Xcor() - Player.get_coordinate().get_Xcor() <= range_gun) {
											cor_diff.push_back(Item_Interface::Zombies[i].get_coordinate().get_Xcor() - Player.get_coordinate().get_Xcor());
											indexes.push_back(i);
											found = true;
										}
										else
											not_in_range = true;
									}
								}
								else if (key == SH_LEFT) {
									if (Item_Interface::Zombies[i].get_coordinate().get_Ycor() == Player.get_coordinate().get_Ycor()
										&& Item_Interface::Zombies[i].get_coordinate().get_Xcor() <= Player.get_coordinate().get_Xcor()) {
										if (Player.get_coordinate().get_Xcor() - Item_Interface::Zombies[i].get_coordinate().get_Xcor() <= range_gun) {
											cor_diff.push_back(Player.get_coordinate().get_Xcor() - Item_Interface::Zombies[i].get_coordinate().get_Xcor());
											indexes.push_back(i);
											found = true;
										}
										else
											not_in_range = true;
									}
								}


							}
							if (found) {
								auto min = min_element(cor_diff.begin(), cor_diff.end());
								index = indexes[min - cor_diff.begin()];
							}
							if (index != -1 && found) {
								Item_Interface::Zombies.erase(Item_Interface::Zombies.begin() + index);


								wchar_t wcs[80];
								wcscpy_s(wcs, L"Assets/sound/Shot/");
								string omg = "";
								switch (kill % 14)
								{
								case 0:
									wcscat_s(wcs, L"0 - First Blood.wav");
									omg = "First Blood";
									break;
								case 1:
									wcscat_s(wcs, L"1 - Double Kill.wav");
									omg = "Double Kill";
									break;
								case 2:
									if (round_num % 2 == 0) {
										wcscat_s(wcs, L"2 - Triple Kill.wav");
										omg = "Triple Kill";
									}
									else {
										wcscat_s(wcs, L"2 - Hattrick.wav");
										omg = "Hattrick";
									}
									break;
								case 3:
									wcscat_s(wcs, L"3 - Team Killer.wav");
									omg = "Team Killer";
									break;
								case 4:
									wcscat_s(wcs, L"4 - Headshot.wav");
									omg = "Headshot";
									break;
								case 5:
									wcscat_s(wcs, L"5 - Rampage.wav");
									omg = "Rampage";
									break;
								case 6:
									wcscat_s(wcs, L"6 - Killing Spree.wav");
									omg = "Killing Spree";
									break;
								case 7:
									wcscat_s(wcs, L"7 - Unstoppable.wav");
									omg = "Unstoppable";
									break;
								case 8:
									wcscat_s(wcs, L"8 - Monster Kill.wav");
									omg = "Monster Kill";
									break;
								case 9:
									wcscat_s(wcs, L"9 - Multi Kill.wav");
									omg = "Multi Kill";
									break;
								case 10:
									wcscat_s(wcs, L"10 - Ludicrouskill.wav");
									omg = "Ludicrouskill";
									break;
								case 11:
									wcscat_s(wcs, L"11 - Ultra Kill.wav");
									omg = "Ultra Kill";
									break;
								case 12:
									wcscat_s(wcs, L"12 - Dominating.wav");
									omg = "Dominating";
									break;
								case 13:
									wcscat_s(wcs, L"13 - Godlike.wav");
									omg = "Godlike";
									break;
								}
								kill++;
								print_screen();
								sleep_sec(1);
								int credit_gained = level + 1;
								credit += credit_gained;
								cout << omg << endl
									<< credit_gained << " credit gained!" << endl;

								//-//-//PlaySound(wcs, NULL, SND_ASYNC | SND_FILENAME);

								sleep_sec(2);
								//-//-//PlaySound(L"Assets/sound/zombie-choking.wav", NULL, SND_ASYNC | SND_FILENAME);
							}
							else if (not_in_range) {
								cout << "Zombie is not in range! come closer." << endl;
								sleep_sec(1.5);
							}
						}
						else {
							cout << "No charged ammo!" << endl;
							/// <summary>
							///moshkel
							/// </summary>
							/// <returns></returns>
							//-//-//PlaySound(L"Assets/sound/out-of-ammo-no-ammo.wav", NULL, SND_ASYNC | SND_FILENAME);
							sleep_sec(1.5);
						}
						break;
					}
					case RELOAD_KEY: {
						//reload
						if (ammo > 0) {
							if (charged < magazine_capacity) {
								cout << "Reloaded!" << endl;
								//-//-//PlaySound(L"Assets/sound/reload.wav", NULL, SND_ASYNC | SND_FILENAME);
								sleep_sec(1.5);
								int need = magazine_capacity - charged;
								if (need > ammo) {
									charged += ammo;
									ammo = 0;
								}
								else {
									ammo -= need;
									charged += need;
								}
							}
							else if (charged == 3) {
								cout << "The gun is already Charged" << endl;
								sleep_sec(1.5);
							}
						}
						else {
							cout << "No Ammo!" << endl;
							//-//-//PlaySound(L"Assets/sound/out-of-ammo-no-ammo.wav", NULL, SND_ASYNC | SND_FILENAME);
							sleep_sec(1.5);
						}
						break;
					}
					case EXIT_KEY: {
						//cout << "Are you sure that you want to exit the game?" << endl;
						game_is_on = false;
						yn = 'n';
						if (!just_play && ask_yn("Would you like to save your data?\n"))
							user.Save();
						break;
					}
					case UPGRADE_KEY:
						base_menu();
						break;
					case MENU_KEY: {
						enum game_menu_items { Return_to_game = 48, New_Game, Save, Load, Options, Exit };
						char game_menu;
						bool broken;
						cout << "0 - Return to game\n"
							<< "1 - New Game\n"
							<< "2 - Save\n"
							<< "3 - Load\n"
							<< "4 - Options\n"
							<< "5 - Exit" << endl;
						do {
							broken = true;
							cin >> game_menu;
							switch (game_menu)
							{
							case Return_to_game:
								break;
							case Load:
								if (!just_play)
									user.Load();
								else {
									cout << "You did't Log in!" << endl;
									break;
								}
							case New_Game:
								if (game_menu != Load)
									Reset_game();
								break;
							case Save:
								if (!just_play)
									user.Save();
								else {
									cout << "You did't Log in!" << endl;
									break;
								}
								break;
							case Exit:
								game_is_on = false;
								yn = 'n';
								if (!just_play && ask_yn("Would you like to save your data?\n"))
									user.Save();
								break;
							default:
								cout << "Please just enter the numbers in the menu:" << endl;
								broken = false;
								break;
							}
						} while (!broken);
					}
					}
					/*
							if (!PlaySound(L"dornandaz.wav", NULL, SND_ASYNC | SND_FILENAME))
								printf("error\n");*/
								/*const char* a1 = "test.wav";
								string a2 = "test.wav";
								wstring filename(L"C:\\test.wav");*/

								//play congratulations.wav
								//mciSendString(a1.c_str(), NULL, 0, NULL);
								//PlaySound(TEXT("test.wav"), NULL, SND_FILENAME | SND_ASYNC);
								//PlaySound(L"test.wav", NULL, SND_ASYNC | SND_FILENAME);
								/*WIN32_FIND_DATA fd = { 0 };
								HANDLE hFile = FindFirstFileW(filename.c_str(), &fd);
								if(hFile != INVALID_HANDLE_VALUE)
									PlaySound(filename.c_str(), NULL, SND_ASYNC | SND_FILENAME);
								*/

								//PlaySound((a1.c_str()), NULL, SND_SYNC);
								//PlaySound("kenny g.WAV", NULL, SND_ASYNC);
								//magically_do_something_platform_and_implementation_specific(PLAY_MUSIC, "test.wav");




					for (int i = 0; i < Item_Interface::Zombies.size(); i++)//enemy moves
					{
						int Ex = Item_Interface::Zombies[i].get_coordinate().get_Xcor(), Ey = Item_Interface::Zombies[i].get_coordinate().get_Ycor(),
							Px = Player.get_coordinate().get_Xcor(), Py = Player.get_coordinate().get_Ycor();
						if (round_num % 2 == 0) {//zombie move
							if (Px > Ex)
								Item_Interface::Zombies[i].get_coordinate().move('d', HEIGHT, WIDTH);
							else if (Px < Ex)
								Item_Interface::Zombies[i].get_coordinate().move('a', HEIGHT, WIDTH);
							else if (Py > Ey)
								Item_Interface::Zombies[i].get_coordinate().move('s', HEIGHT, WIDTH);
							else if (Py < Ey)
								Item_Interface::Zombies[i].get_coordinate().move('w', HEIGHT, WIDTH);
						}
						//print(Zombies, Coins, Door);

						//Zombie ate us
						if (abs(Px - Ex) <= 1 && abs(Py - Ey) <= 1) {
							/*game_is_on = false;
							won = false;*/
							health--;
							print_screen();
							//-//-//PlaySound(L"Assets/sound/zombies-eating.wav", NULL, SND_ASYNC | SND_FILENAME);
							cout << "The zombie is eating you! You lost one of your healths!" << endl;
							sleep_sec(2);
							if (health <= 0)
								break;
						}

					}
					if (health <= 0) {//die
						game_is_on = false;
						won = false;
						print_screen();
						cout << "You Died!" << endl;
						//-//-//PlaySound(L"Assets/sound/evillaugh.wav", NULL, SND_ASYNC | SND_FILENAME);
						//break;
					}
					//Door
					if (Player == Door) {
						if (Item_Interface::Vaccines.size() == 0) {
							game_is_on = false;
							won = true;
							print_screen();
							//-//-//PlaySound(L"Assets/sound/mission-complete.wav", NULL, SND_ASYNC | SND_FILENAME);
							//break;
						}
						else {
							print_screen();
							cout << "First get all the Vaccines." << endl;
							//-//-//PlaySound(L"Assets/sound/First Get all the Vaccines.wav", NULL, SND_ASYNC | SND_FILENAME);
							sleep_sec(1.5);
						}
					}
					//Ammo
					else {
						for (int i = 0; i < Item_Interface::Ammunition.size(); i++)
						{
							if (Player == Item_Interface::Ammunition[i])
							{
								Item_Interface::Ammunition.erase(Item_Interface::Ammunition.begin() + i);
								ammo++;
								print_screen();
								cout << "Ammo collected!" << endl;
								//-//-//PlaySound(L"Assets/sound/Ammo collected.wav", NULL, SND_ASYNC | SND_FILENAME);
								sleep_sec(1.5);
							}
						}
						for (int i = 0; i < Item_Interface::Vaccines.size(); i++)
						{
							if (Item_Interface::Vaccines[i] == Player) {
								Item_Interface::Vaccines.erase(Item_Interface::Vaccines.begin() + i);
								vaccine++;
								print_screen();
								int credit_gained = level + 1;
								credit += credit_gained;
								cout << "Vaccine collected!" << endl
									<< credit_gained << " credit gained!" << endl;
								//-//-//PlaySound(L"Assets/sound/Vaccine collected.wav", NULL, SND_ASYNC | SND_FILENAME);
								sleep_sec(1.5);
							}

						}
					}
				}
				if (won) {
					level++;
					if (level != END_LEVEL + 1) {
						int credit_gained = level;
						credit += credit_gained;
						cout << "Well Done! You have reached level " << level << endl
							<< credit_gained << " credit gained!" << endl;
						sleep_sec(1.5);
					}
					else if (level == END_LEVEL + 1) {
						cout << "Congratulations! You have successfully collected all the Vaccines! Now it is time to return to the Earth" << endl;
						cout << "Good Bye!" << endl;
						break;
					}
				}
				else {
					if (yn != 'n')
						cout << "You Lose! Would you like to try again?(y/n)" << endl;
					//char yn;
					while (yn != 'n') {
						cin >> yn;
						if (yn == 'y' || yn == 'n')
							break;
						cout << "Please just enter y for yes or n for no:" << endl;
					}
					if (yn == 'y') {
						cout << "The game will restart in 5 seconds" << endl;
						reset_values();
						sleep_sec(5);
					}
					else if (yn == 'n') {
						//Exit_game();
						break;
					}
				}
				/*Zombies.clear();
				Vaccines.clear();
				Ammo.clear();*/
			}
			break;
		case Settings:

			break;
		case Credits:
			Credits_print();
			break;
		case Exit:
			if (ask_yn("Are you sure you want to exit the game?\nWarning: All unsaved data will be lost!\n")) {
				is_exit = true;
				Exit_game();
			}
			break;
		default:
			break;
		}
	}
	return 0;

}
void Exit_game() {
	//-//-//PlaySound(L"Assets/sound/dornandaz.wav", NULL, SND_ASYNC | SND_FILENAME);
	cout << "Good Bye!" << endl;
	sleep_sec(15);
}
void reset_values() {
	level = 1;
	vaccine = 0;
	health = 3;
	ammo = 0;
	charged = 3;
	kill = 0;
	range_gun = 5;
	credit = 0;
	round_num = 0;
	magazine_capacity = 3;
	mute = false;
}
//void reset_keys() {
//	keys_chars[0] = 'w';
//	keys_chars[1] = 'a';
//	keys_chars[2] = 's';
//	keys_chars[3] = 'd';
//	keys_chars[4] = 't';
//	keys_chars[5] = 'f';
//	keys_chars[6] = 'g';
//	keys_chars[7] = 'h';
//	keys_chars[8] = 'r';
//	keys_chars[9] = 'e';
//	keys_chars[10] = 'u';
//	keys_chars[11] = 'm';
//}
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
				cout << Player.get_pic();
				continue;
			}
			else if (Door.get_coordinate().Xcor == j && Door.get_coordinate().Ycor == i) {
				cout << Door.get_pic();
				continue;
			}
			bool broken = false;
			for (int a = 0; a < Item_Interface::Zombies.size(); a++)
			{
				if (Item_Interface::Zombies[a].get_coordinate().Xcor == j && Item_Interface::Zombies[a].get_coordinate().Ycor == i) {
					cout << Item_Interface::Zombies[a].get_pic();
					broken = true;
					break;
				}
			}
			if (broken)
				continue;
			for (int c = 0; c < Item_Interface::Vaccines.size(); c++)
			{

				if (Item_Interface::Vaccines[c].get_coordinate().Xcor == j && Item_Interface::Vaccines[c].get_coordinate().Ycor == i) {
					cout << Item_Interface::Vaccines[c].get_pic();
					broken = true;
					break;
				}

			}
			if (broken)
				continue;
			for (int c = 0; c < Item_Interface::Ammunition.size(); c++)
			{

				if (Item_Interface::Ammunition[c].get_coordinate().Xcor == j && Item_Interface::Ammunition[c].get_coordinate().Ycor == i) {
					cout << Item_Interface::Ammunition[c].get_pic();
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
		sleep_sec(.1);
	}
	sleep_sec(2);
}
void Reset_game() {
	reset_values();
	read_max_level();
	get_level_info_from_file(level);
}
