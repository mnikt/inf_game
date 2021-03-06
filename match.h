#include <time.h>
#include <string>
#include <windows.h>
#include <SFML\Graphics.hpp>
#include "player.h"

using namespace std;

string num_to_str(int number);

///Zmiana zawodników
void change(int a, int b, Player *player[17], int &c);

///Funkcja wyświetlająca statystyki piłkarzy w ekranie zarządzania drużyną i pozwalająca na dokonanie zmian
void team_management(sf::RenderWindow &window, Player *player[17], int &clicked, int &change_left);

void match(Player player1[17], Player player2[17], sf::RenderWindow &window);

void no_view_match(Player player1[17], Player player2[17]);

///Funkcja wyświetlająca statystyki piłkarzy w ekranie zarządzania drużyną i pozwalająca na dokonanie zmian
void menu_team_management(sf::RenderWindow &window, Player team[17]);