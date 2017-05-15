#include <SFML/Graphics.hpp>
#include <iostream>
#include "match.h"
class Button
{
private:
	//sf::RenderWindow window;

	sf::Text caption;
	sf::RectangleShape shape;

	sf::RenderWindow window;
	std::string cap_text;
	int cap_size;
	sf::Color cap_color;
	//float cap_pos_x;
	//float cap_pos_y;
	sf::Font font;

	float sh_size;
	float shape_pos_x;
	float shape_pos_y;
	int sh_red;
	int sh_green;
	int sh_blue;
	bool isHover = false;
	//void hover(sf::RenderWindow &window);

public:
	Button(sf::RenderWindow &window, std::string cap_text, float sh_pos_x, float sh_pos_y, float cap_pos_x, float cap_pos_y);
	void draw();

	bool check_Hover(sf::RenderWindow &window);

	~Button();

};

Button::Button(sf::RenderWindow &window, std::string cap_text, float sh_pos_x, float sh_pos_y, float cap_pos_x, float cap_pos_y)
	:
	//window(sf::VideoMode(900, 700), "Futbal Menad?er v.1"),
	cap_text("button"),
	shape_pos_x(sh_pos_x),
	shape_pos_y(sh_pos_y),
	sh_size(100),
	sh_red(100),
	sh_green(250),
	sh_blue(50),
	cap_color(255, 255, 255),
	cap_size(30)
{
	shape.setSize(sf::Vector2f(sh_size, sh_size));
	shape.setPosition(sf::Vector2f(sh_pos_x, sh_pos_y));
	shape.setFillColor(sf::Color(sh_red, sh_green, sh_blue));

	if (font.loadFromFile("arial.ttf"));

	caption.setString(cap_text);
	caption.setFont(font);
	caption.setCharacterSize(cap_size);
	caption.setFillColor(cap_color);
	caption.setPosition(cap_pos_x, cap_pos_y);
	caption.setStyle(sf::Text::Regular);

	window.draw(shape);
	window.draw(caption);
}

void Button::draw()
{

}

bool Button::check_Hover(sf::RenderWindow &window)
{
	if (sf::Mouse::getPosition(window).x >= shape_pos_x && sf::Mouse::getPosition(window).x <= sh_size + shape_pos_x && sf::Mouse::getPosition(window).y <= sh_size + shape_pos_y && sf::Mouse::getPosition(window).y >= shape_pos_y)
	{
		//if(sh_red+sh_green+sh_blue<380)
		//  shape.setFillColor(sf::Color::Yellow);
		//else
		shape.setFillColor(sf::Color::Blue);
		window.draw(shape);
		isHover = true;
	}

	return isHover;
}

Button::~Button()
{
	//dtor
}

class Menu
{
private:

	enum Whitch_button
	{
		is_nothing = 0,
		is_sklad = 1,
		is_matches = 2,
		is_shop = 3,
		is_trening = 4,
		is_options = 5,
		is_exit = 6,
	};
	//sf::RenderWindow window;


public:

	void main_menu(sf::RenderWindow &window);

	Menu();
	~Menu();

};

Menu::Menu()
{
	//ctor
}

Menu::~Menu()
{
	//dtor
}

void Menu::main_menu(sf::RenderWindow &window)
{
	Button sklad(window, "Sklad", 330, 160, 330, 230);
	Button matches(window, "Mecze", 450, 160, 450, 230);
	Button shop(window, "Handel", 570, 160, 570, 230);
	Button trening(window, "trening", 330, 300, 330, 370);
	Button options(window, "opcje", 450, 300, 450, 370);
	Button exit(window, "wyjdz", 570, 300, 570, 370);
	Whitch_button check = is_nothing;

	if (sklad.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_sklad;
	}

	else if (matches.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_matches;
	}

	else if (shop.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_shop;
	}

	else if (trening.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_trening;
	}

	else if (options.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_options;
	}

	else if (exit.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_exit;
	}

	switch (check)
	{
	case is_sklad:
	{
		Player players[17];
		for (int i = 0; i < 17; i++)
			players[i].load_stats(i, "Pogoń_Szczecin");
		menu_team_management(window, players);
		break;
	}

	case is_matches:
	{	
	Player players1[17], players2[17];
	for (int i = 0; i < 17; i++)
		players1[i].load_stats(i, "Pogoń_Szczecin");
	match(players1, players2, window);
	break;

	}

	case is_shop:
	{
		/*sf::Font font;
		sf::Text caption;
		if(font.loadFromFile("arial.ttf"));
		window.clear();
		caption.setString("Zarzadzaj skladem swojego klubu");
		caption.setFont(font);
		caption.setCharacterSize(50);
		caption.setFillColor(sf::Color::Yellow);
		caption.setPosition(20,20);
		caption.setStyle(sf::Text::Regular);
		window.draw(caption);*/
	}

	case is_trening:
	{
		/*sf::Font font;
		sf::Text caption;
		if(font.loadFromFile("arial.ttf"));
		window.clear();
		caption.setString("Zarzadzaj skladem swojego klubu");
		caption.setFont(font);
		caption.setCharacterSize(50);
		caption.setFillColor(sf::Color::Yellow);
		caption.setPosition(20,20);
		caption.setStyle(sf::Text::Regular);
		window.draw(caption);*/
	}

	case is_options:
	{
		sf::Font font;
		sf::Text caption;

		if (font.loadFromFile("arial.ttf"));
		caption.setString("Zarzadzaj skladem swojego klubu");
		caption.setFont(font);
		caption.setCharacterSize(50);
		caption.setFillColor(sf::Color::Yellow);
		caption.setPosition(20, 20);
		caption.setStyle(sf::Text::Regular);
		window.draw(caption);
	}

	case is_exit:
	{
		//Wyjście
	}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
	window.setFramerateLimit(8);

	sf::Texture background_texture;
	if (!background_texture.loadFromFile("grafika/bckg.jpg"));
	sf::Sprite background(background_texture);

	sf::Texture logo_texture;
	if (!logo_texture.loadFromFile("grafika/maly.png"));
	sf::Sprite logo(logo_texture);
	logo.setPosition(500, 20);

	Menu men;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(background);
		men.main_menu(window);
		window.display();
	}

	return 0;
}