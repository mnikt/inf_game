#include <time.h>
#include <string>
#include <windows.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "match.h"

using namespace std;

string num_to_str(int number) {
	string a = "00";
	a[1] = number % 10 + 48;
	a[0] = number / 10 + 48;
	return a;
}

///Zmiana zawodników
void change(int a, int b, Player *player[17], int &c) {
	if (player[a]->get_card("red") == false || player[b]->get_card("red") == false)
	{
		if ((a > 10 || b > 10) && (a<11 || b<11))
			return;
	}
	if (c == 0)
		return;
	Player *help;
	help = player[a];
	player[a] = player[b];
	player[b] = help;
	if ((a > 10 || b > 10) && (a<11 || b<11))
		c--;
}

///Funkcja wyœwietlaj¹ca statystyki pi³karzy w ekranie zarz¹dzania dru¿yn¹ i pozwalaj¹ca na dokonanie zmian
void team_management(sf::RenderWindow &window, Player *player[17], int &clicked, int &change_left) {
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		cout << "Couldn't load font";

	sf::Text text[17][9];
	sf::Sprite card[17];
	sf::Texture texture;
	texture.loadFromFile("grafika/trawa.jpg");

	//Ustawienie informacji o podawanych statystykach 
	sf::Text inf[9];
	for (int i = 0; i < 9; i++) {
		inf[i].setFont(font);
		inf[i].setColor(sf::Color::White);
		inf[i].setCharacterSize(10);
		inf[i].setPosition(i * 30 + 40, 85);
	}
	inf[0].setPosition(10, 85);
	inf[0].setString("Name");
	inf[1].setString("Pos");
	inf[2].setString("Con");
	inf[3].setString("Ovr");
	inf[4].setString("Pac");
	inf[5].setString("Sho");
	inf[6].setString("Pas");
	inf[7].setString("Def");
	inf[8].setString("Phs");

	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 9; j++) {
			text[i][j].setFont(font);
			text[i][j].setColor(sf::Color::White);
			text[i][j].setCharacterSize(15);
		}
		card[i].setPosition(305, i * 30 + 100);
		if (player[i]->get_card("yellow") == false) {
			texture.loadFromFile("grafika/¿ó³ta_kartka.jpg");
			card[i].setTexture(texture);
		}
		if (player[i]->get_card("red") == false) {
			texture.loadFromFile("grafika/czerwona_kartka.jpg");
			card[i].setTexture(texture);
		}

		text[i][0].setString(player[i]->get_name());
		text[i][0].setPosition(5, i * 30 + 100);
		//	text[i][1].setString(num_to_str(player[i]->get_position()));
		//	text[i][1].setPosition(70, i * 30 + 100);
		text[i][2].setString(num_to_str(player[i]->get_stats("condition")));
		text[i][2].setPosition(100, i * 30 + 100);
		text[i][3].setString(num_to_str(player[i]->get_stats("overall")));
		text[i][3].setPosition(130, i * 30 + 100);
		text[i][4].setString(num_to_str(player[i]->get_stats("pace")));
		text[i][4].setPosition(160, i * 30 + 100);
		text[i][5].setString(num_to_str(player[i]->get_stats("shooting")));
		text[i][5].setPosition(190, i * 30 + 100);
		text[i][6].setString(num_to_str(player[i]->get_stats("passing")));
		text[i][6].setPosition(220, i * 30 + 100);
		text[i][7].setString(num_to_str(player[i]->get_stats("defence")));
		text[i][7].setPosition(250, i * 30 + 100);
		text[i][8].setString(num_to_str(player[i]->get_stats("physicality")));
		text[i][8].setPosition(280, i * 30 + 100);
	}

	for (int i = 11; i < 17; i++) {
		text[i][0].setColor(sf::Color(250, 250, 250, 170));
	}

	if (sf::Mouse::getPosition(window).x < 80 && sf::Mouse::getPosition(window).x>5 && sf::Mouse::getPosition(window).y < 595 && sf::Mouse::getPosition(window).y > 100)
		text[(sf::Mouse::getPosition(window).y - 100) / 30][0].setColor(sf::Color(100, 80, 200));
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		int x, y;
		x = sf::Mouse::getPosition(window).x;
		y = sf::Mouse::getPosition(window).y;

		if (x < 80 && x>5 && y < 595 && y > 100) {
			if (clicked == (y - 100) / 30)
				clicked = -1;
			else if (clicked == -1)
				clicked = (y - 100) / 30;
			else {
				change(clicked, (y - 100) / 30, player, change_left);
				clicked = -1;
			}
		}
	}

	if (clicked != -1)
		text[clicked][0].setColor(sf::Color::Yellow);

	for (int y = 0; y < 9; y++)
		window.draw(inf[y]);

	for (int x = 0; x < 17; x++) {
		window.draw(card[x]);
		for (int y = 0; y < 9; y++)
			window.draw(text[x][y]);
	}
}


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

	//Ekran zarz¹dzania dru¿yn¹
	bool team_manager = false;
	sf::Sprite team_manager_button;
	sf::Texture team_manager_texture;
	team_manager_button.setPosition(800, 500);
	team_manager_texture.loadFromFile("grafika/zarzadzanie_druzyna.jpg");
	team_manager_button.setTexture(team_manager_texture);

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

	class Event {
		sf::Text team;
		sf::Text player;
		sf::Text time;
		sf::Sprite icon;
		sf::Texture texture;
		sf::Font font;

	public:

		Event(int number = 0, string teamx = "team1", string playerx = "Kow", string timex = "00", string type = "goal") {
			font.loadFromFile("arial.ttf");
			team.setCharacterSize(20);
			team.setPosition(810, 50 + number * 30);
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

	//Event *event[15];

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
	int team1_power = 0, team2_power = 0;

	//cout << team1_offensive << endl << team2_offensive << endl;
	long int random = 0;

	int goals1 = 0, goals2 = 0;

	string clock = { "00'" };

	Event event[15];

	int clicked = -1;

	int change_left = 3;

	///Ustawienie tekstu z iloœci¹ zmian
	sf::Text changes[2];
	changes[0].setString("Changes left:");
	changes[0].setColor(sf::Color::White);
	changes[0].setPosition(400, 560);
	changes[0].setCharacterSize(20);
	changes[0].setFont(font);
	changes[1].setColor(sf::Color::White);
	changes[1].setPosition(525, 560);
	changes[1].setCharacterSize(20);
	changes[1].setFont(font);

	///Przebieg meczu
	///Wykonywane w ka¿dej minucie

	for (int i = 1; i < 92; i++) {
		clock[0] = i / 10 + 48;
		clock[1] = i % 10 + 48;
		timer.setString(clock);

		string pomocniczy = "3";
		pomocniczy[0] = change_left + 48;
		changes[1].setString(pomocniczy);

		team1_offensive = 0;
		team1_defence = 0;
		team1_midle = 0;
		team2_offensive = 0;
		team2_defence = 0;
		team2_midle = 0;
		team1_power = 0;
		team2_power = 0;

		for (int i = 0; i < 17; i++) {
			team1[i]->set_overall();
			team2[i]->set_overall();
		}

		for (int i = 0; i < 11; i++) {
			team1_defence += (team1[i]->get_stats("defence") + team1[i]->get_stats("pace") + team1[i]->get_stats("physicality"))
				* (team1[i]->get_stats("overall") - 30) / 3 * (team1[i]->get_stats("condition") + 30) / 90 * team1[i]->get_card("red");//(((int)((int)(team1[i]->get_stats("condition") / 90) * 10 + team1[i]->get_stats("condition")) % 100 - 60));
			team2_defence += (team2[i]->get_stats("defence") + team2[i]->get_stats("pace") + team2[i]->get_stats("physicality"))
				* (team2[i]->get_stats("overall") - 30) / 3 * (team2[i]->get_stats("condition") + 30) / 90 * team2[i]->get_card("red");// (((int)((int)(team2[i]->get_stats("condition") / 90) * 10 + team2[i]->get_stats("condition")) % 100 - 60));
			team1_offensive += (team1[i]->get_stats("shooting") + team1[i]->get_stats("pace") + team1[i]->get_stats("physicality"))
				* (team1[i]->get_stats("overall") - 30) / 3 * (team1[i]->get_stats("condition") + 30) / 90 * team1[i]->get_card("red");//(((int)((int)(team1[i]->get_stats("condition") / 90) * 10 + team1[i]->get_stats("condition")) % 100 - 60));
			team2_offensive += (team2[i]->get_stats("shooting") + team2[i]->get_stats("pace") + team2[i]->get_stats("physicality"))
				* (team2[i]->get_stats("overall") - 30) / 3 * (team2[i]->get_stats("condition") + 30) / 90 * team2[i]->get_card("red");//(((int)((int)(team2[i]->get_stats("condition") / 90) * 10 + team2[i]->get_stats("condition")) % 100 - 60));
			team1_midle += (team1[i]->get_stats("passing") + team1[i]->get_stats("pace") + team1[i]->get_stats("physicality"))
				* (team1[i]->get_stats("overall") - 30) / 3 * (team1[i]->get_stats("condition") + 30) / 90 * team1[i]->get_card("red");//(((int)((int)(team1[i]->get_stats("condition") / 90) * 10 + team1[i]->get_stats("condition")) % 100 - 60));
			team2_midle += (team2[i]->get_stats("passing") + team2[i]->get_stats("pace") + team2[i]->get_stats("physicality"))
				* (team2[i]->get_stats("overall") - 30) / 3 * (team2[i]->get_stats("condition") + 30) / 90 * team2[i]->get_card("red");//(((int)((int)(team2[i]->get_stats("condition") / 90) * 10 + team2[i]->get_stats("condition")) % 100 - 60));
		}
		cout << team1[5]->get_card("y_card") << endl;
		int a = team1_midle; //zmienna pomocnicza 
		team1_power = (8100 - team1_offensive / 11 + team2_defence / 11);
		team2_power = (8100 - team2_offensive / 11 + team1_defence / 11) + 1;
		team1_midle = (int)(team1_midle / team2_midle * 10);
		team2_midle = (int)(team2_midle / a * 10);


		//Pasek pokazuj¹cy szanse dru¿yn
		sf::RectangleShape chance1(sf::Vector2f(team2_power * 300 / team1_power, 5));
		chance1.setPosition(58, 10);
		chance1.setFillColor(sf::Color::Red);
		sf::RectangleShape chance2(sf::Vector2f(600, 5));
		chance2.setPosition(58, 10);
		chance2.setFillColor(sf::Color::Blue);

		window.display();
		window.clear();
		window.draw(background);
		window.draw(events);
		window.draw(team1_name);
		window.draw(team2_name);
		window.draw(goals1_text);
		window.draw(goals2_text);
		window.draw(timer);
		window.draw(team_manager_button);
		window.draw(chance2);
		window.draw(chance1);
		if (team_manager) {
			window.draw(changes[0]);
			window.draw(changes[1]);
		}

		for (int a = 0; a < event_counter; a++) {
			event[a].draw(window);
		}

		if (!team_manager) {
			for (int b = 0; b < 17; b++) {
				window.draw(players_names_1[b]);
				window.draw(players_names_2[b]);
			}
		}//OKNO ZARZ¥DZANIA DRU¯YN¥
		else {
			team_management(window, team1, clicked, change_left);
		}

		int player_power;
		for (int i = 0; i < 11; i++) {
			player_power = ((team1[i]->get_stats("shooting") + team1[i]->get_stats("pace") + team1[i]->get_stats("physicality")) * (team1[i]->get_stats("overall") - 30) / 3 * (team1[i]->get_stats("condition") + 30) / 90);
			//player_power = 1/(player_power * 11 / team1_offensive);
			for (int j = 0; j < team1_midle; j++) {
				if (team1[i]->get_card("red") == false) break;
				random = rand() % (team1_power * team2_power);
				if (random % player_power == 0)
				{
					goals1++;
					goal1++;
					goals1_text.setString(goal1);
					event[event_counter].set(event_counter, "team1", team1[i]->get_name(), clock, "goal");
					event_counter++;
					break;
				}
			}
			player_power = (team2[i]->get_stats("shooting") + team2[i]->get_stats("pace") + team2[i]->get_stats("physicality"))* (team2[i]->get_stats("overall") - 30) / 3 * (team2[i]->get_stats("condition") + 30) / 90;
			//	 player_power = 1/(player_power / team2_offensive * 11);
			for (int j = 0; j < team2_midle; j++) {
				if (team2[i]->get_card("red") == false) break;
				random = rand() % (team1_power * team2_power);
				if (random % player_power == 0)
				{
					goals2++;
					goal2++;
					goals2_text.setString(goal2);
					event[event_counter].set(event_counter, "team2", team2[i]->get_name(), clock, "goal");
					event_counter++;
					break;
				}
			}
			//Spadek kondycji
			if (team1[i]->get_card("red"))
				team1[i]->condition_match_update();
			if (team2[i]->get_card("red"))
				team2[i]->condition_match_update();
		}

		//Otrzymanie ¿ó³tej kartki
		random = rand() % 550;
		if (random < 11) {
			if (team1[random]->get_card("yellow") == true) {
				event[event_counter].set(event_counter, "team1", team1[random]->get_name(), clock, "y_card");
				event_counter++;
				team1[random]->set_card("yellow");
			}
			else {
				event[event_counter].set(event_counter, "team1", team1[random]->get_name(), clock, "r_card");
				event_counter++;
				team1[random]->set_card("red");
			}
		}
		else if (random < 22) {
			if (team2[random - 11]->get_card("yellow") == true) {
				event[event_counter].set(event_counter, "team2", team2[random - 11]->get_name(), clock, "y_card");
				event_counter++;
				team2[random - 11]->set_card("yellow");
			}
			else {
				event[event_counter].set(event_counter, "team2", team2[random - 11]->get_name(), clock, "r_card");
				event_counter++;
				team2[random - 11]->set_card("red");
			}
		}

		//Otrzymanie czerwonej kartki
		random = rand() % 5000;
		if (random < 11) {
			event[event_counter].set(event_counter, "team1", team1[random]->get_name(), clock, "r_card");
			event_counter++;
			team1[random]->set_card("red");
		}
		else if (random < 22) {
			event[event_counter].set(event_counter, "team2", team2[random - 11]->get_name(), clock, "r_card");
			event_counter++;
			team2[random - 11]->set_card("red");
		}

		//Otrzymanie kontuzji
		random = rand() % 3500;
		if (random < 11) {
			event[event_counter].set(event_counter, "team1", team1[random]->get_name(), clock, "injury");
			event_counter++;
			team1[random]->get_injury(rand() % 20);
		}
		else if (random < 22) {
			event[event_counter].set(event_counter, "team2", team2[random - 11]->get_name(), clock, "injury");
			event_counter++;
			team2[random - 11]->get_injury(rand() % 20);
		}

		sf::Clock clock;
		sf::Time time;
		while (time.asSeconds() <= 1.0f) {
			time += clock.getElapsedTime();
			clock.restart();
			window.display();
			window.clear();
			window.draw(background);
			window.draw(events);
			window.draw(team1_name);
			window.draw(team2_name);
			window.draw(goals1_text);
			window.draw(goals2_text);
			window.draw(timer);
			window.draw(team_manager_button);
			window.draw(chance2);
			window.draw(chance1);
			if (team_manager) {
				window.draw(changes[0]);
				window.draw(changes[1]);
			}

			for (int a = 0; a < event_counter; a++) {
				event[a].draw(window);
			}

			if (!team_manager) {
				for (int b = 0; b < 17; b++) {
					window.draw(players_names_1[b]);
					window.draw(players_names_2[b]);
				}
			}//OKNO ZARZ¥DZANIA DRU¯YN¥
			else {
				team_management(window, team1, clicked, change_left);
			}
			if (sf::Mouse::getPosition(window).x > 800 && sf::Mouse::getPosition(window).x < 923 && sf::Mouse::getPosition(window).y > 500 && sf::Mouse::getPosition(window).y < 563 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				team_manager = !team_manager;
		}
		clock.restart();

	}
	///Wys³anie danych pomeczowych, statystyk itp.

}
