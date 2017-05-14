#include <string>
#include <windows.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include "player.h"

using namespace std;

int str_to_num(string text) {
	int a = 0;
	if(text[0]!=NULL)
	a += (text[0] - 48) * 10;
	else return a;
	if(text[1]!=NULL)
	a += (text[1] - 48);
	return a;
}

	//Konstruktor
Player::Player() :
name ("Kowalski"),
pace (80),
passing  (80),
shooting  (80),
condition  (99),
defence  (95),
physicality (80),
overall (70),
injury (0),
position (goalkeeper),
no_y_card (true),
no_r_card (true)
{}
	
//Funkcja zwraca imiê pi³karza
	string Player::get_name() {
		return name;
	}

	//Funkcja zwraca pozycjê pi³karza
	int Player::get_position() {
		return position;
	}

	///Funkcja zwraca statystyki
	double Player::get_stats(string stat) {
		if (stat == "pace")
			return pace;
		if (stat == "defence")
			return defence;
		if (stat == "condition")
			return condition;
		if (stat == "passing")
			return passing;
		if (stat == "physicality")
			return physicality;
		if (stat == "shooting")
			return shooting;
		if (stat == "overall")
			return overall;
		if (stat == "injury")
			return injury;
		return 70;
	}

	///Funkcja obliczaj¹ca ocenê ogóln¹
	void Player::set_overall() {
		switch (position) {
		case goalkeeper:
			overall = (defence * 10 + pace + passing + physicality + shooting) / 14;
			break;
		case defender:
			overall = (defence * 8 + pace * 2 + passing + physicality * 2 + shooting) / 14;
			break;
		case midfielder:
			overall = (defence + pace + passing * 6 + physicality + shooting) / 10;
			break;
		case striker:
			overall = (defence + pace * 2 + passing + physicality * 3 + shooting * 8) / 15;
			break;
		default:
			break;
		}
	}

	///Funkcja zwraca posiadanie kartki
	bool Player::get_card(string card) {
		if (card == "yellow")
			return no_y_card;
		if (card == "red")
			return no_r_card;
		return false;
	}

	///Funkcja ustawia kartki
	void Player::set_card(string card) {
		if (card == "red")
		{
			no_r_card = false;
			return;
		}
		else {
			if (no_y_card == true)
				no_y_card = false;
			else no_r_card = false;
		}
	}

	///Funkcja obni¿aj¹ca poziom kondycji w trakcie meczu
	void Player::condition_match_update() {
		if(condition > 0)
		condition -= 0.333333f - ((physicality - 70) / 100);
	}

	///Funkcja otrzymania kontuzji
	void Player::get_injury(int days) {
		injury = days;
	}

	///Funkcja otwiera plik z danymi dru¿yny
	fstream Player::open_file_team(string name) {
		fstream plik;
		if (name == "Wzór")
			plik.open("teams/Wzór.txt", ios::in | ios::out | ios::app);
		if (name == "Dru¿yna_testowa")
			plik.open("teams/Dru¿yna_testowa.txt", ios::in | ios::out | ios::app);
		if (name == "Pogoñ_Szczecin")
			plik.open("teams/Szczecin.txt", ios::in | ios::out | ios::app);
		if (name == "Main_team")
			plik.open("teams/main_team.txt", ios::in | ios::out | ios::app);
		if (name == "test")
			plik.open("teams/test.txt", ios::in | ios::out | ios::app);
		cout << plik.good();
		if(plik.good()==true)
			return plik;
		else exit(0);
	}
	
	///Funkcja czyœci plik z danymi dru¿yny
	void Player::clean_file_team(string name) {
		fstream plik;
		if (name == "Wzór")
			plik.open("teams/Wzór.txt", ios::out | ios::trunc);
		if (name == "Dru¿yna_testowa")
			plik.open("teams/Dru¿yna_testowa.txt", ios::out | ios::trunc);
		if (name == "Pogoñ_Szczecin")
			plik.open("teams/Szczecin.txt",ios::out | ios::trunc);
		if (name == "Main_team")
			plik.open("teams/main_team.txt", ios::out | ios::trunc);
		if (name == "test") 
			plik.open("teams/test.txt", ios::out | ios::trunc);
		plik.close();
	}

	///Funkcja ³aduj¹ca statystyki z pliku
	void Player::load_stats(int number, string team_name) {
		fstream file = open_file_team(team_name);
		string line;
		for (int i = 0; i < number * 11 + 6; i++)
			getline(file, line);
		getline(file,name);
		getline(file, line);
		pace = str_to_num(line);
		getline(file, line);
		passing = str_to_num(line);
		getline(file, line);
		shooting = str_to_num(line);
		getline(file, line);
		condition = str_to_num(line);
		getline(file, line);
		defence = str_to_num(line);
		getline(file, line);
		physicality = str_to_num(line);
		getline(file, line);
		overall = str_to_num(line);
		getline(file, line);
		injury = str_to_num(line);
		getline(file, line);
		position = (Player::Position) str_to_num(line);
		getline(file, line);
		no_r_card = str_to_num(line);
		file.close();
	}

	///Funkcja ³aduj¹ca statystyki do pliku
	void Player::send_stats(int number, string team_name) {
		string line;
		fstream file;
		if(number == 0)
		{
			clean_file_team(team_name);
			file = open_file_team(team_name);
			file << endl << endl << endl << endl << endl;
		} else file = open_file_team(team_name);

		file << name << endl;
		file << pace << endl;
		file << passing << endl;
		file << shooting << endl;
		file << condition << endl;
		file << defence << endl;
		file << physicality << endl;
		file << overall << endl;
		file << injury << endl;
		file << no_r_card << endl;
		//file >> (int)position<< endl;
		file << no_r_card << endl;
		file.close();
	}