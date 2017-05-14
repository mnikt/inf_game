#include <string>
#include <windows.h>
#include <SFML\Graphics.hpp>

using namespace std;

class Player {
	enum Position {
		///st, lw, rw, rm, lm, cm, cdm, cam, rb, lb, cb, gk
		striker, midfielder, defender, goalkeeper
	};
	string name;
	double pace;
	double passing;
	double shooting;
	double condition;
	double defence;
	double physicality;
	int overall;
	int injury;
	Position position;
	bool no_y_card;
	bool no_r_card;

public:

	//Konstruktor
	Player();

	//Funkcja zwraca imi� pi�karza
	string get_name();

	//Funkcja zwraca pozycj� pi�karza
	int get_position();

	///Funkcja zwraca statystyki
	double get_stats(string stat);

	///Funkcja obliczaj�ca ocen� og�ln�
	void set_overall();

	///Funkcja zwraca posiadanie kartki
	bool get_card(string card);

	///Funkcja ustawia kartki
	void set_card(string card);

	///Funkcja obni�aj�ca poziom kondycji w trakcie meczu
	void condition_match_update();

	///Funkcja otrzymania kontuzji
	void get_injury(int days);

	///Funkcja otwiera plik z danymi dru�yny
	fstream open_file_team(string);

	///Funkcja czy�ci plik z danymi dru�yny
	void Player::clean_file_team(string);

	///Funkcja �aduj�ca statystyki z pliku
	void load_stats(int,string);//nr_zawodnika, nazwa_dru�yny 

	///Funkcja �aduj�ca statystyki do pliku
	void send_stats(int number, string team_name);
};