#include "User.h"
void User::reset_values() {
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
}
bool User::string_check_numeric(string text) {
	for (int i = 0; i < text.length(); i++)
		if (!(text[i] >= '0' && text[i] <= '9'))
			return false;
	return true;
}
bool User::check_user_name(string user_name) {
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
bool User::check_password(string password) {
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
void User::Save_file() {
	/*ofstream user_file(file_path, ios::binary);
	user_file.write(reinterpret_cast<const char*>(&(*this)), sizeof((*this)));
	user_file.close();*/
	//string address = "Assets/users/" + user_name + ".txt";
	ofstream user_file(file_path, ios::out);
	user_file << password << endl;
	user_file << _Width << " " << _Height << " " << _num_save << endl;
	user_file << _level << " " << _vaccine << " " << _credit << " " << _round_num << endl;
	user_file << _health << " " << _ammo << " " << _charged << " " << _kill << endl;
	user_file << _range_gun << " " << _magazine_capacity << " " << _mute << endl;
	user_file << _Player.get_coordinate().get_Xcor() << " " << _Player.get_coordinate().get_Ycor() << endl;
	user_file << _Zombies.size() << " " << _Vaccines.size() << " " << _Ammunition.size() << endl;
	for (int i = 0; i < _Zombies.size(); i++)
		user_file << _Zombies[i].get_coordinate().get_Xcor() << " " << _Zombies[i].get_coordinate().get_Ycor() << endl;
	for (int i = 0; i < _Vaccines.size(); i++)
		user_file << _Vaccines[i].get_coordinate().get_Xcor() << " " << _Vaccines[i].get_coordinate().get_Ycor() << endl;
	for (int i = 0; i < _Ammunition.size(); i++)
		user_file << _Ammunition[i].get_coordinate().get_Xcor() << " " << _Ammunition[i].get_coordinate().get_Ycor() << endl;
	user_file.close();
}
void User::Load_file() {
	ifstream user_file(file_path, ios::in);
	user_file >> password;
	user_file >> _Width >> _Height >> _num_save;
	user_file >> _level >> _vaccine >> _credit >> _round_num;
	user_file >> _health >> _ammo >> _charged >> _kill;
	user_file >> _range_gun >> _magazine_capacity >> _mute;
	mute = _mute;
	int x, y;
	user_file >> x >> y;
	Player = Item_Interface(PLAYER_CHAR, x, y);
	Door = Item_Interface(DOOR_CHAR, _Width - 1, _Height - 1);
	int zombie_size, vaccine_size, ammunition_size;
	user_file >> zombie_size >> vaccine_size >> ammunition_size;
	Item_Interface::Zombies.clear(); Item_Interface::Vaccines.clear(); Item_Interface::Ammunition.clear();
	for (int i = 0; i < zombie_size; i++) {
		user_file >> x >> y;
		Item_Interface::Zombies.push_back(Item_Interface(ZOMBIE_CHAR, x, y));
	}
	for (int i = 0; i < vaccine_size; i++) {
		user_file >> x >> y;
		Item_Interface::Vaccines.push_back(Item_Interface(VACCINE_CHAR, x, y));
	}
	for (int i = 0; i < ammunition_size; i++) {
		user_file >> x >> y;
		Item_Interface::Ammunition.push_back(Item_Interface(AMMO_CHAR, x, y));
	}
	user_file.close();
}
bool User::file_exist(string path) {
	bool exist;
	ifstream inFile(path, ios::in);
	if (!inFile)
		exist = false;
	else
		exist = true;
	inFile.close();
	return exist;
}
User::User() { _num_save = 0; }
User::~User() {}
bool User::Sign_up() {
	cout << "(notes: username or password should contain at least " << min_user_pass_length
		<< " and at most " << max_user_pass_length
		<< " characters, legal chars for username {a-z,A-Z,0-9} space is illegal, " << endl
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
	sleep_sec(2);
	return true;
}
bool User::Login() {
	string password_input;
	cout << "(notes: username or password should contain at least " << User::min_user_pass_length
		<< " and at most " << User::max_user_pass_length
		<< " characters, legal chars for username {a-z,A-Z,0-9} space is illegal, " << endl
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

	/*ifstream user_file(file_path, ios::in);
	user_file.read(reinterpret_cast<char*>(&(*this)), sizeof((*this)));
	user_file.close();*/
	//Load_file();
	Load();
	cout << "Enter your password:" << endl;
	do {
		cin >> password_input;
	} while (!check_password(password_input));
	if (password_input == password) {
		cout << "password is correct" << endl
			<< "All your data is loaded!" << endl;
		//Load();
		sleep_sec(2);
		return true;
	}
	else
		cout << "password is incorrect" << endl;
	sleep_sec(2);
	return false;
}
void User::Load() {

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
	WIDTH = _Width;
	HEIGHT = _Height;
	mute = _mute;
	//Player = _Player;
	//Door = _Door;
	//Item_Interface::Zombies = _Zombies;
	//Item_Interface::Vaccines = _Vaccines;
	//Item_Interface::Ammunition = _Ammunition;
}
void User::Save() {
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
	_Width = WIDTH;
	_Height = HEIGHT;
	_num_save++;

	_Player = Player;
	_Door = Door;
	_Zombies = Item_Interface::Zombies;
	_Vaccines = Item_Interface::Vaccines;
	_Ammunition = Item_Interface::Ammunition;
	Save_file();
}
int User::get_num_save() { return _num_save; }

const int User::max_user_pass_length = 20;
const int User::min_user_pass_length = 4;