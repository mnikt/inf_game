#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>
#include <SFML\Graphics.hpp>
#include "match.h"

///Funkcja wyświetlająca statystyki piłkarzy w ekranie zarządzania drużyną i pozwalająca na dokonanie zmian
void menu_team_management(sf::RenderWindow &window, Player team[17]) {
	int clicked = -1;
	Player *player[17];
	for (int i = 0; i < 17; i++)
		player[i] = &team[i];

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
			texture.loadFromFile("grafika/żółta_kartka.jpg");
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

	sf::Sprite save_button;
	sf::Sprite return_button;
	sf::Texture save_but;
	sf::Texture return_but;
	save_button.setPosition(650, 560);
	return_button.setPosition(830, 560);
	save_but.loadFromFile("grafika/Zapisz.png");
	save_button.setTexture(save_but);
	return_but.loadFromFile("grafika/Wyjdź.png");
	return_button.setTexture(return_but);
	save_button.setScale(sf::Vector2f(1.25, 1.25));
	return_button.setScale(sf::Vector2f(1.25, 1.25));
	
	///Wykonywane w każdej klatce
	while (!(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).y < 598 && sf::Mouse::getPosition(window).y >= 560 && sf::Mouse::getPosition(window).x >= 830 && sf::Mouse::getPosition(window).x < 930)) {
		for (int i = 0; i < 17; i++) {

			if (player[i]->get_card("red") == false) {
				texture.loadFromFile("grafika/czerwona_kartka.jpg");
				card[i].setTexture(texture);
			}

			text[i][0].setString(player[i]->get_name());
			//	text[i][1].setString(num_to_str(player[i]->get_position()));
			//	text[i][1].setPosition(70, i * 30 + 100);
			text[i][2].setString(num_to_str(player[i]->get_stats("condition")));
			text[i][3].setString(num_to_str(player[i]->get_stats("overall")));
			text[i][4].setString(num_to_str(player[i]->get_stats("pace")));
			text[i][5].setString(num_to_str(player[i]->get_stats("shooting")));
			text[i][6].setString(num_to_str(player[i]->get_stats("passing")));
			text[i][7].setString(num_to_str(player[i]->get_stats("defence")));
			text[i][8].setString(num_to_str(player[i]->get_stats("physicality")));
		}

		for (int i = 11; i < 17; i++) {
			text[i][0].setColor(sf::Color(250, 250, 250, 170));
		}
		
		
		for (int j = 0; j < 11; j++) {
			text[j][0].setColor(sf::Color::White);
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
					if (player[clicked]->get_card("red") == false || player[(y - 100) / 30]->get_card("red") == false)
					{
						if ((clicked > 10 || (y - 100) / 30 > 10) && (clicked < 11 || (y - 100) / 30 < 11))
							return;
					}
					Player *help;
					help = player[clicked];
					player[clicked] = player[(y - 100) / 30];
					player[(y - 100) / 30] = help;
					clicked = -1;
				}
			}
		}

		if (clicked != -1)
			text[clicked][0].setColor(sf::Color::Yellow);
		window.display();
		window.clear();

		for (int y = 0; y < 9; y++)
			window.draw(inf[y]);

		for (int x = 0; x < 17; x++) {
			window.draw(card[x]);
			for (int y = 0; y < 9; y++)
				window.draw(text[x][y]);
		}
		window.draw(return_button);
		window.draw(save_button);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).y < 598 && sf::Mouse::getPosition(window).y >= 560 && sf::Mouse::getPosition(window).x < 750 && sf::Mouse::getPosition(window).x >= 650) {
			for(int i=0; i<17; i++)
			player[i]->send_stats(i, "test");
			
		}
	}
}

int main() {
	Player team1[17], team2[17];
	
	for (int i = 0; i < 17; i++) {
		team1[i].load_stats(i, "Pogoń_Szczecin");
	}
	
	sf::RenderWindow window(sf::VideoMode(1000, 600), "My window");
	window.setFramerateLimit(8);
	while (true) {
		menu_team_management(window, team1);
	}
/*	for (int i = 0; i < 10; i++) {
		for (int i = 0; i < 17; i++) {
			team1[i].load_stats(i, "Pogoń_Szczecin");
		}
		no_view_match(team1, team2);
		Sleep(1000); 
	}*/

	system("PAUSE");
	return 0;
}