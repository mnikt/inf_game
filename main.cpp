#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

class Player {
	enum Position {
		///st, lw, rw, rm, lm, cm, cdm, cam, rb, lb, cb, gk
		striker, midfielder, defender, goalkeeper
	};

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
			overall = (defence * 10 + pace + passing + physicality + shooting) /14 ;
			break;
		case defender:
			overall = (defence * 8 + pace * 2 + passing + physicality * 2 + shooting) / 14;
			break;
		case midfielder:
			overall = (defence + pace  + passing * 8 + physicality + shooting) / 12;
			break;
		case striker:
			overall = (defence + pace*2 + passing + physicality*3 + shooting*8) / 15;
			break;
		default:
			break;
		}
	}
	
};


void match(Player player1[11], Player player2[11]) {
	///Rozpoczêcie meczu
	///Wykonywane tylko raz

	srand(time(NULL));

	double team1_defence = 0, team2_defence = 0, team1_offensive = 0, team2_offensive = 0, team1_midle = 0, team2_midle = 0;
	for (int i = 0; i < 11; i++) {
		player1[i].set_overall();
		player2[i].set_overall();
		team1_defence += (player1[i].get_stats("defence") + player1[i].get_stats("pace") + player1[i].get_stats("physicality"))
			* (player1[i].get_stats("overall") - 30) /3 * (player1[i].get_stats("condition") +30) / 90;//(((int)((int)(player1[i].get_stats("condition") / 90) * 10 + player1[i].get_stats("condition")) % 100 - 60));
		team2_defence += (player2[i].get_stats("defence") + player2[i].get_stats("pace") + player2[i].get_stats("physicality"))
			* ((player2[i].get_stats("overall") - 30) /3 ) * (player2[i].get_stats("condition") + 30) / 90;// (((int)((int)(player2[i].get_stats("condition") / 90) * 10 + player2[i].get_stats("condition")) % 100 - 60));
		team1_offensive += (player1[i].get_stats("shooting") + player1[i].get_stats("pace") + player1[i].get_stats("physicality"))
			* (player1[i].get_stats("overall") - 30) /3 * (player1[i].get_stats("condition") + 30) / 90;//(((int)((int)(player1[i].get_stats("condition") / 90) * 10 + player1[i].get_stats("condition")) % 100 - 60));
		team2_defence += (player2[i].get_stats("shooting") + player2[i].get_stats("pace") + player2[i].get_stats("physicality"))
			* (player2[i].get_stats("overall") - 30) /3 * (player2[i].get_stats("condition") + 30) / 90;//(((int)((int)(player2[i].get_stats("condition") / 90) * 10 + player2[i].get_stats("condition")) % 100 - 60));
	}
	team1_offensive = (8100 - team1_offensive/11 + team2_defence/11);
	team2_offensive = (8100 - team2_offensive/11 + team1_defence/11) +1;
	//cout << team1_offensive << endl << team2_offensive << endl;
	long int random = 0;

	int goals1 = 0, goals2 = 0;

	///Przebieg meczu
	///Wykonywane w ka¿dej minucie
	
	for (int i = 1; i < 9100; i++) {

		random = rand() % 300000000000;

		if (random % (int)team1_offensive == 0) {
			//cout << "Bramka team1, minuta:" << i / 100 + 1 << endl;
			goals1++;
		}

		if (random % (int)team2_offensive == 0) {
			//cout << "Bramka team2, minuta:" << i / 100 + 1 << endl;
			goals2++;
		}
	}

	cout << goals1 << " : " << goals2<<endl;

}

int main() {

	Player team1[11], team2[11];

	for (int i = 0; i < 10; i++) {
		match(team1, team2);
		Sleep(1000);
	}

	system("PAUSE");
	return 0;
}