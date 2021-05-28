#pragma once
#ifndef _USER_
#define _USER_
#include "Item_Interface.h"
class User {
private:
	string user_name;
	string password;
	string file_path;
	int _level, _health, _ammo, _charged, _vaccine,
		_kill, _range_gun, _credit, _round_num, _magazine_capacity,
		_Width, _Height;
	bool _mute;
	int _num_save;
	static const int max_user_pass_length;
	static const int min_user_pass_length;
	Item_Interface _Player;
	Item_Interface _Door;
	Array<Item_Interface> _Zombies;
	Array<Item_Interface> _Vaccines;
	Array<Item_Interface> _Ammunition;
	void reset_values();
	static bool string_check_numeric(string);
	static bool check_user_name(string);
	static bool check_password(string);
	void Save_file();
	void Load_file();
	static bool file_exist(string);
public:
	User();
	~User();
	bool Sign_up();
	bool Login();
	void Load();
	void Save();
	int get_num_save();
};


User user;
#endif