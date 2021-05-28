#include "User.h"

int main() {
	read_max_level();
	cout <<RED<< LOGO <<RESET<< endl;
	cout << "Welcome to Covid 2030 game!\n";
	Register();

	while (!is_exit) {
		char yn = ' ', main_menu;			//'0'
		enum main_menu_items { Register_stage = 48, New_Game, Load, Settings, Credits, Exit };
		//srand(time(0));//srand(10);//quera
		Clear_scr();
		cout <<YELLOW<< "0 - Register\n"
			<< "1 - New Game\n"
			<< "2 - Load\n"
			<< "3 - Settings\n"
			<< "4 - Credits\n"
			<< "5 - Exit" <<RESET<< endl;
		cin >> main_menu;
		switch (main_menu)
		{
		case Register_stage:
			if (ask_yn("Warning: if you have already loged in you'll be loged out and your unsaved data will be lost.Would you like to continue?\n"))
				Register();
			break;
		case Load:
			if (!just_play) {
				if (user.get_num_save() != 1) {
					user.Load();
					cout << "All your data is loaded!" << endl;
					sleep_sec(2);
				}
				else {
					cout << "You have't saved yet" << endl;
					sleep_sec(2);
					break;
				}
			}
			else {
				cout << "You did't Log in!" << endl;
				sleep_sec(2);
				break;
			}
		case New_Game:
			if (main_menu != Load)
				reset_values();
			//while bazi
			while (true) {
				if (main_menu != Load)
					get_level_info_from_file(level);

				bool game_is_on = true, won = false, load_triggered = false;
				if (main_menu != Load)
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
							play_sound(L"Assets/sound/gun shot.wav");
							//PlaySound(TEXT("Assets/sound/gun shot.wav"), NULL, SND_ASYNC | SND_FILENAME);
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
								play_sound(wcs);
								//PlaySound(wcs, NULL, SND_ASYNC | SND_FILENAME);

								sleep_sec(2);
								play_sound(L"Assets/sound/zombie-choking.wav");
								//PlaySound(L"Assets/sound/zombie-choking.wav", NULL, SND_ASYNC | SND_FILENAME);
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
							play_sound(L"Assets/sound/out-of-ammo-no-ammo.wav");
							//PlaySound(L"Assets/sound/out-of-ammo-no-ammo.wav", NULL, SND_ASYNC | SND_FILENAME);
							sleep_sec(1.5);
						}
						break;
					}
					case RELOAD_KEY: {
						//reload
						if (ammo > 0) {
							if (charged < magazine_capacity) {
								cout << "Reloaded!" << endl;
								play_sound(L"Assets/sound/reload.wav");
								//PlaySound(L"Assets/sound/reload.wav", NULL, SND_ASYNC | SND_FILENAME);
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
							play_sound(L"Assets/sound/out-of-ammo-no-ammo.wav");
							//PlaySound(L"Assets/sound/out-of-ammo-no-ammo.wav", NULL, SND_ASYNC | SND_FILENAME);
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
						enum game_menu_items { Return_to_game = 48, New_Game_inner_menu, Save, Load_inner_menu, Settings, Exit };
						char game_menu;
						bool broken;
						cout<< YELLOW << "0 - Return to game\n"
							<< "1 - New Game\n"
							<< "2 - Save\n"
							<< "3 - Load\n"
							<< "4 - Settings\n"
							<< "5 - Exit"<<RESET << endl;
						do {
							broken = true;
							cin >> game_menu;
							switch (game_menu)
							{
							case Return_to_game:
								break;
							case Load_inner_menu:
								if (!just_play) {
									if (user.get_num_save() != 1) {
										user.Load();
										main_menu = Load;
										game_is_on = false;
										load_triggered = true;
										cout << "All your data is loaded!" << endl;
									}
									else {
										cout << "You haven't saved yet!" << endl;
									}
								}
								else {
									cout << "You did't Log in!" << endl;
								}
								sleep_sec(2);
								break;
							case New_Game_inner_menu:
								Reset_game();
								main_menu = New_Game;
								game_is_on = false;
								break;
							case Save:
								if (!just_play)
									user.Save();
								else {
									cout << "You did't Log in!" << endl;
									sleep_sec(1.5);
								}
								break;
							case Settings:
								Settings_menu();
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
							play_sound(L"Assets/sound/zombies-eating.wav");
							//PlaySound(L"Assets/sound/zombies-eating.wav", NULL, SND_ASYNC | SND_FILENAME);
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
						play_sound(L"Assets/sound/evillaugh.wav");
						//PlaySound(L"Assets/sound/evillaugh.wav", NULL, SND_ASYNC | SND_FILENAME);
						//break;
					}
					//Door
					if (Player == Door) {
						if (Item_Interface::Vaccines.size() == 0) {
							game_is_on = false;
							won = true;
							print_screen();
							play_sound(L"Assets/sound/mission-complete.wav");
							//PlaySound(L"Assets/sound/mission-complete.wav", NULL, SND_ASYNC | SND_FILENAME);
							//break;
						}
						else {
							print_screen();
							cout << "First get all the Vaccines." << endl;
							play_sound(L"Assets/sound/First Get all the Vaccines.wav");
							//PlaySound(L"Assets/sound/First Get all the Vaccines.wav", NULL, SND_ASYNC | SND_FILENAME);
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
								play_sound(L"Assets/sound/Ammo collected.wav");
								//PlaySound(L"Assets/sound/Ammo collected.wav", NULL, SND_ASYNC | SND_FILENAME);
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
								play_sound(L"Assets/sound/Vaccine collected.wav");
								//PlaySound(L"Assets/sound/Vaccine collected.wav", NULL, SND_ASYNC | SND_FILENAME);
								sleep_sec(1.5);
							}

						}
					}
				}
				if (!load_triggered) {
					if (won) {
						main_menu = New_Game;
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
							Reset_game();
							sleep_sec(5);
						}
						else if (yn == 'n') {
							//Exit_game();
							break;
						}
					}
				}
				/*Zombies.clear();
				Vaccines.clear();
				Ammo.clear();*/
			}
			break;
		case Settings:
			Settings_menu();
			break;
		case Credits:
			Credits_print();
			break;
		case Exit:
			if (ask_yn("Are you sure you want to exit the game?\n")) {
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
