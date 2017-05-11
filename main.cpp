#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>
#include <SFML\Graphics.hpp>
#include "match.h"

int main() {
	Player team1[17], team2[17];

	for (int i = 0; i < 17; i++) {
		team1[i].load_stats(i, "Pogoñ_Szczecin");
	}

	sf::RenderWindow window(sf::VideoMode(1000, 600), "My window");
	window.setFramerateLimit(8);

	for (int i = 0; i < 10; i++) {
		match(team1, team2, window);
		Sleep(1000); 
	}

	system("PAUSE");
	return 0;
}