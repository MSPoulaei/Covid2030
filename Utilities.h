#ifndef _UTILITIES_
#define _UTILITIES_
#include <iostream>
#include <fstream>//for save/load
#include <ctime>//for sleep_sec(time)
#include <vector>
#include <Windows.h>//for play_sound
#include <MMSystem.h>//for play_sound
#include <algorithm>//for finding the nearest zombie to kill
//CONSTANTS
#define PLAYER_CHAR 'P'
#define ZOMBIE_CHAR 'Z'
#define VACCINE_CHAR 'V'
#define AMMO_CHAR 'A'
#define DOOR_CHAR 'D'
#define EMPTY_CHAR ' '
#define MAX_MAG_CAP 7
#define MAX_GUN_RANGE 10
#define MAX_HEALTH 5
//ANSI CODES
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define LOGO "\
######   #######  ##     ## #### ########      #######    #####    #######    #####   \n\
##    ## ##     ## ##     ##  ##  ##     ##    ##     ##  ##   ##  ##     ##  ##   ##  \n\
##       ##     ## ##     ##  ##  ##     ##           ## ##     ##        ## ##     ## \n\
##       ##     ## ##     ##  ##  ##     ##     #######  ##     ##  #######  ##     ## \n\
##       ##     ##  ##   ##   ##  ##     ##    ##        ##     ##        ## ##     ## \n\
##    ## ##     ##   ## ##    ##  ##     ##    ##         ##   ##  ##     ##  ##   ##  \n\
######   #######     ###    #### ########     #########   #####    #######    #####   "
using namespace std;
bool just_play = false, is_exit = false, mute = false;
int WIDTH = 15, HEIGHT = 15, END_LEVEL = 20;
int level = 1, health = 3, ammo = 0, charged = 3,
vaccine = 0, kill = 0, range_gun = 5, credit = 0,
round_num = 0, magazine_capacity = 3;

void sleep_sec(float);
void Settings_menu();
void Reset_game();
void Exit_game();
void print_screen();
void print_score_board();
void Upgrade_item(const int&, int&, const int, string);
void base_menu();
void reset_values();
void get_level_info_from_file(int);
void Clear_scr();
void char_to_lower(char&);
void read_max_level();
void write_max_level(int& max_level);
void Credits_print();
bool ask_yn(string = "");
void Register();
bool play_sound(LPCWSTR);
template<typename T1>
void reset_value(T1&, T1);
#endif