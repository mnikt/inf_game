#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>
#include <SFML\Graphics.hpp>

/*
Do zrobienia:
-okno zarz¹dzania dru¿yn¹ w trakcie meczu
-spadek poziomu kondycji w trakcie meczu
-dodanie mo¿liwoœci otrzymania kartki i kontuzji
-dodanie paska pokazuj¹cego szanse obu dru¿yn
-dodanie wp³ywu poziomu linii pomocy na szanse dru¿yn

-dodanie formacji
-dodanie wp³ywu umieszczenia zawodnika na nie swojej pozycji

*/
using namespace std;

class Player {
	enum Position {
		///st, lw, rw, rm, lm, cm, cdm, cam, rb, lb, cb, gk
		striker, midfielder, defender, goalkeeper
	};
	string name = "Kowalski";
	double offensive = 70;
	double pace = 70;
	double passing = 70;
	double shooting = 70;
	double condition = 99;
	double defence = 70;
	double physicality = 70;
	int overall = 70;
	Position position = goalkeeper;

public:

	//Funkcja zwraca imiê pi³karza
	string get_name() {
		return name;
	}

	///Funkcja zwraca statystyki
	double get_stats(string stat) {
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
		if (stat == "offensive")
			return offensive;
		return 70;
	}

	///Funkcja obliczaj¹ca ocenê ogóln¹
	void set_overall() {
		switch (position) {
		case goalkeeper:
			overall = (defence * 10 + pace + passing + physicality + shooting) / 14;
			break;
		case defender:
			overall = (defence * 8 + pace * 2 + passing + physicality * 2 + shooting) / 14;
			break;
		case midfielder:
			overall = (defence + pace + passing * 8 + physicality + shooting) / 12;
			break;
		case striker:
			overall = (defence + pace * 2 + passing + physicality * 3 + shooting * 8) / 15;
			break;
		default:
			break;
		}
	}

};


void match(Player player1[17], Player player2[17], sf::RenderWindow &window) {
	///Rozpoczêcie meczu
	///Wykonywane tylko raz

	//£adowanie czcionki oraz t³a
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		cout << "Couldn't load font";
	sf::Sprite background;
	sf::Texture texture;
	texture.loadFromFile("grafika/trawa.jpg");
	background.setTexture(texture);

	//Tablice wska¿ników pokazuj¹cych na pi³karzy
	Player *team1[17];
	Player *team2[17];
	//Przypisanie pi³karzy do wska¿ników
	for (int i = 0; i < 17; i++) {
		team1[i] = &player1[i];
		team2[i] = &player2[i];
	}

	//Wyœwietlenie nazwisk pi³karzy
	sf::Text players_names_1[17];
	for (int i = 0; i < 11; i++) {
		players_names_1[i].setFont(font);
		players_names_1[i].setString(team1[i]->get_name());
		players_names_1[i].setColor(sf::Color::White);
		players_names_1[i].setCharacterSize(20);
		players_names_1[i].setPosition(50, 100 + i * 28);
	}
	for (int i = 11; i < 17; i++) {
		players_names_1[i].setFont(font);
		players_names_1[i].setString(team1[i]->get_name());
		players_names_1[i].setColor(sf::Color::Yellow);
		players_names_1[i].setCharacterSize(18);
		players_names_1[i].setPosition(50, 120 + i * 28);
	}

	sf::Text players_names_2[17];
	for (int i = 0; i < 11; i++) {
		players_names_2[i].setFont(font);
		players_names_2[i].setString(team2[i]->get_name());
		players_names_2[i].setColor(sf::Color::White);
		players_names_2[i].setCharacterSize(20);
		players_names_2[i].setPosition(600, 100 + i * 28);
	}
	for (int i = 11; i < 17; i++) {
		players_names_2[i].setFont(font);
		players_names_2[i].setString(team2[i]->get_name());
		players_names_2[i].setColor(sf::Color::Yellow);
		players_names_2[i].setCharacterSize(18);
		players_names_2[i].setPosition(600, 120 + i * 28);
	}
	//Wyœwietlenie nazw dru¿yn, wyniku, zegara
	char goal1 = '0', goal2 = '0';
	sf::Text team1_name("team1", font, 35);
	team1_name.setPosition(50, 30);
	team1_name.setColor(sf::Color::White);
	sf::Text team2_name("team2", font, 35);
	team2_name.setPosition(550, 30);
	team2_name.setColor(sf::Color::White);
	sf::Text goals1_text(goal1, font, 35);
	goals1_text.setPosition(300, 30);
	sf::Text goals2_text(goal1, font, 35);
	goals2_text.setPosition(390, 30);
	sf::Text timer("0", font, 25);
	timer.setPosition(343, 55);
	sf::Text events("Wydarzenia meczu", font, 20);
	events.setPosition(770, 15);

	int event_counter = 0;

	class Event{
		sf::Text team;
		sf::Text player;
		sf::Text time;
		sf::Sprite icon;
		sf::Texture texture;
		sf::Font font;

	public:

		Event(int number = 0, string teamx = "team1", string playerx = "Kow", string timex="00", string type = "goal") {
			font.loadFromFile("arial.ttf");
			team.setCharacterSize(20);
			team.setPosition(810, 50+number * 30);
			team.setString(teamx);
			team.setFont(font);
			team.setColor(sf::Color::White);	

			player.setCharacterSize(15);
			player.setPosition(815, number * 30 + 70);
			player.setString(playerx);
			player.setFont(font);
			player.setColor(sf::Color::White);

			time.setCharacterSize(15);
			time.setPosition(810, number * 30 + 70);
			time.setString(timex);
			time.setFont(font);
			time.setColor(sf::Color::White);

			texture.loadFromFile("grafika/ball.jpeg");

			icon.setTexture(texture);
			icon.setPosition(780, number * 30 + 50);

		}

		//Funkcja tymczasowa(Nieoficjalny konstruktor)
		void set(int number, string teamx, string playerx, string timex, string type) {
			team.setPosition(810, 50 + number * 40);
			team.setString(teamx);

			player.setPosition(835, number * 40 + 70);
			player.setString(playerx);

			time.setPosition(810, number * 40 + 70);
			time.setString(timex);

			//Pokazanie obrazka odpowiedniego do wydarzenia 
			//Wydarzenie 'goal' zapisane jest w konstruktorze domyœlnym - brak zmiany spowoduje wyœwietlenie tego wydarzenia
			if (type == "y_card")
				texture.loadFromFile("grafika/¿ó³ta_kartka.jpg");
			else if (type == "r_card")
				texture.loadFromFile("grafika/czerwona_kartka.jpg");
			else if (type == "injury")
				texture.loadFromFile("grafika/kontuzja.png");

			icon.setTexture(texture);

			icon.setPosition(780, number * 40 + 50);
		}

		void draw(sf::RenderWindow &window) {
			window.draw(team);
			window.draw(icon);
			window.draw(time);
			window.draw(player);
		}
	};

	//Event *event;

	window.display();
	window.draw(team1_name);
	window.draw(team2_name);
	window.draw(goals1_text);
	window.draw(goals2_text);
	window.draw(events);

	for (int i = 0; i < 17; i++) {
		window.draw(players_names_1[i]);
		window.draw(players_names_2[i]);
	}

	srand(time(NULL));

	double team1_defence = 0, team2_defence = 0, team1_offensive = 0, team2_offensive = 0, team1_midle = 0, team2_midle = 0;
	for (int i = 0; i < 11; i++) {
		team1[i]->set_overall();
		team2[i]->set_overall();
		team1_defence += (team1[i]->get_stats("defence") + team1[i]->get_stats("pace") + team1[i]->get_stats("physicality"))
			* (team1[i]->get_stats("overall") - 30) / 3 * (team1[i]->get_stats("condition") + 30) / 90;//(((int)((int)(team1[i]->get_stats("condition") / 90) * 10 + team1[i]->get_stats("condition")) % 100 - 60));
		team2_defence += (team2[i]->get_stats("defence") + team2[i]->get_stats("pace") + team2[i]->get_stats("physicality"))
			* ((team2[i]->get_stats("overall") - 30) / 3) * (team2[i]->get_stats("condition") + 30) / 90;// (((int)((int)(team2[i]->get_stats("condition") / 90) * 10 + team2[i]->get_stats("condition")) % 100 - 60));
		team1_offensive += (team1[i]->get_stats("shooting") + team1[i]->get_stats("pace") + team1[i]->get_stats("physicality"))
			* (team1[i]->get_stats("overall") - 30) / 3 * (team1[i]->get_stats("condition") + 30) / 90;//(((int)((int)(team1[i]->get_stats("condition") / 90) * 10 + team1[i]->get_stats("condition")) % 100 - 60));
		team2_defence += (team2[i]->get_stats("shooting") + team2[i]->get_stats("pace") + team2[i]->get_stats("physicality"))
			* (team2[i]->get_stats("overall") - 30) / 3 * (team2[i]->get_stats("condition") + 30) / 90;//(((int)((int)(team2[i]->get_stats("condition") / 90) * 10 + team2[i]->get_stats("condition")) % 100 - 60));
	}

	team1_offensive = (8100 - team1_offensive / 11 + team2_defence / 11);
	team2_offensive = (8100 - team2_offensive / 11 + team1_defence / 11) + 1;
	//cout << team1_offensive << endl << team2_offensive << endl;
	long int random = 0;

	int goals1 = 0, goals2 = 0;

	string clock = { "00'"};

	Event event[15];

	///Przebieg meczu
	///Wykonywane w ka¿dej minucie

	for (int i = 1; i < 9100; i++) {
		clock[0] = i / 1000 + 48;
		clock[1] = i / 100 % 10 + 48;
		timer.setString(clock);

		window.display();
		window.clear();
		window.draw(background);
		window.draw(events);
		window.draw(team1_name);
		window.draw(team2_name);
		window.draw(goals1_text);
		window.draw(goals2_text);
		window.draw(timer);

		for (int i = 0; i < event_counter; i++) {
			event[i].draw(window);
		}

		for (int i = 0; i < 17; i++) {
			window.draw(players_names_1[i]);
			window.draw(players_names_2[i]);
		}

		random = rand() % 300000000000;

		if (random % (int)team1_offensive == 0) {
			goals1++;
			goal1++;
			goals1_text.setString(goal1);
			event[event_counter].set(event_counter, "team1", team1[0]->get_name(), clock, "goal");
			event_counter++;
		}

		if (random % (int)team2_offensive == 0) {
			goals2++;
			goal2++;
			goals2_text.setString(goal2);
			event[event_counter].set(event_counter, "team2",team2[0]->get_name(), clock, "goal");
			event_counter++;
		}


	}
/*	if (event_counter == 1)
		delete event;
	else if (event_counter > 1)
	delete[] event;*/

	cout << goals1 << " : " << goals2 << endl;

}
/*
void match(sf::RenderWindow &window){
	sf::RectangleShape TeamManager(sf::Vector2f(100, 50));
	//TeamManager.setTexture();
	TeamManager.setPosition(10, 10);
	sf::RectangleShape TimeTable(sf::Vector2f(100, 50));
	//TimeTable.setTexture();
	TimeTable.setPosition(10, 70);
	sf::RectangleShape NextMatch(sf::Vector2f(100, 50));
	//NextMatch.setTexture();
	NextMatch.setPosition(10, 130);
	sf::RectangleShape Exit(sf::Vector2f(100, 50));
	//Exit.setTexture();
	Exit.setPosition(10, 190);
	
	sf::Mouse::getPosition(window);
	window.draw(TeamManager);
	window.draw(TimeTable);
	window.draw(NextMatch);
	window.draw(Exit);

}*/




int main() {

	Player team1[17], team2[17];
	sf::RenderWindow window(sf::VideoMode(1000, 600), "My window");
	window.setFramerateLimit(1000);
	
	for (int i = 0; i < 10; i++) {
		match(team1, team2, window);
		Sleep(1000); 
	}

	system("PAUSE");
	return 0;
}