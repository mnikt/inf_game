#include <SFML/Graphics.hpp>
#include <iostream>
//#include "match.h"
class Button
{
private:
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
		if(sh_red+sh_green+sh_blue<380)
		  shape.setFillColor(sf::Color(sh_red + 25, sh_green +25, sh_blue+25));
		else
			shape.setFillColor(sf::Color(sh_red - 25, sh_green - 25, sh_blue - 25));
		window.draw(shape);
		window.draw(caption);
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

    std::string intToStr(int n)
    {
        std::string tmp, ret;

         do {
          tmp += n % 10 + 48;
          n -= n % 10;
        }
     while(n /= 10);
     for(int i = tmp.size()-1; i >= 0; i--)
      ret += tmp[i];
     return ret;
    }

	enum Whitch_button
	{
		is_nothing = 0,
		is_sklad = 1,
		is_matches = 2,
		is_shop = 3,
		is_trening = 4,
		is_tabel = 5,
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
	Button next(window, "Dalej", 450, 160, 450, 230);
	Button shop(window, "Rynek", 570, 160, 570, 230);
	Button trening(window, "Trening", 330, 300, 330, 370);
	Button tabel(window, "Tabela", 450, 300, 450, 370);
	Button exit(window, "Wyjdz", 570, 300, 570, 370);
	Whitch_button check = is_nothing;

	sf::Texture call_texture;
	int month=5;
	call_texture.loadFromFile("Kalendarzyk/Grafika/"+intToStr(month)+".png");
    sf::Sprite callendar(call_texture);
    callendar.setPosition(100,100);
    sf::Font font;
    sf::Text str_day;
    int is=4;
    if(font.loadFromFile("arial.ttf"));
    str_day.setString("Czwartek");
    str_day.setFont(font);
    str_day.setCharacterSize(23);
    str_day.setFillColor(sf::Color::Red);
    str_day.setPosition(120,123);
    str_day.setStyle(sf::Text::Regular);

    sf::Text num_day;
    int in=18;
    num_day.setString("18");
    num_day.setFont(font);
    num_day.setCharacterSize(75);
    num_day.setFillColor(sf::Color::Red);
    num_day.setPosition(160,150);
    num_day.setStyle(sf::Text::Regular);

	if (sklad.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_sklad;
	}

	else if (next.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
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

	else if (tabel.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_tabel;
	}

	else if (exit.check_Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		check = is_exit;
	}

	switch (check)
	{
        case is_matches:
        {
            is++;
            if(is>7) is=1;

            switch(is)
            {
            case 1:
                str_day.setString("Poniedzialek");
                break;

            case 2:
                str_day.setString("Wtorek");
                break;

            case 3:
                str_day.setString("Sroda");
                break;

            case 4:
                str_day.setString("Czwartek");
                break;

            case 5:
                str_day.setString("Piatek");
                break;

             case 6:
                str_day.setString("Sobota");
                break;

             case 7:
                str_day.setString("Niedziela");
                break;
            }

            in++;

            if(month==1 && month==3 && month==5 && month==7 && month==8 && month==10 && month==12 && in>31)
            {
                in=1;
                month++;
            }

            else if(month==4 && month==6 && month==9 && month==11 && in>30)
            {
                in=1;
                month++;
            }

            else if(month==2 && in>28)
            {
                in=1;
                month++;
            }

            num_day.setString(intToStr(in));

            if(month>12) month=1;
        }

	case is_sklad:
	{
//		Player players[17];
		//for (int i = 0; i < 17; i++)
//			players[i].load_stats(i, "Pogoń_Szczecin");
//		menu_team_management(window, players);
		//break;
	}
/*
	case is_matches:
	{
	Player players1[17], players2[17];
	for (int i = 0; i < 17; i++)
		players1[i].load_stats(i, "Pogoń_Szczecin");
	match(players1, players2, window);
	break;
	}*/

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

	case is_tabel:
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
		window.close();
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
