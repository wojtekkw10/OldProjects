#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "snake.h"

int edytuj_weza(snake & snake, char input, sf::Vector2u jedzenie);
void dodajjedzenie(sf::Vector2u & jedzenie, snake snake);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 400), "SFML works!");
	window.setFramerateLimit(5);

	sf::CircleShape square(10);// sf::Vector2f(20, 20)
	square.setFillColor(sf::Color::Green);

	sf::CircleShape circle(10.f);
	circle.setFillColor(sf::Color::Red);

	snake waz;
	waz.direction = 2;

	waz.shape[0].x = 5;
	waz.shape[0].y = 5;

	waz.length = 10;
	sf::Vector2u food;
	food.x = 50;
	food.y = 50;
	dodajjedzenie(food, waz);
	
	tgui::Gui gui{ window };
	sf::Clock clockFPS;
	int input=2;
	for (int i = 0; i < 10; i++)
	{
		edytuj_weza(waz, input, food);
	}

	sf::Texture texture;
	texture.loadFromFile("grass.png");
	sf::Sprite background;
	background.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					input = 1;
				}
				if (event.key.code == sf::Keyboard::D)
				{
					input = 2;
				}
				if (event.key.code == sf::Keyboard::S)
				{
					input = 3;
				}
				if (event.key.code == sf::Keyboard::A)
				{
					input = 4;
				}
			}
			gui.handleEvent(event);
		}

			int czyzjadl = edytuj_weza(waz, input, food); //do obslugi return z edutuj weza
			//if ((czyzjadl = edytuj_weza(waz, input, food)) == 1) break; //1 gdzy ugryzl siebie
			if (czyzjadl == 2) { waz.length += 1; dodajjedzenie(food, waz); } //2 gdy cos zjadl

			window.clear();
			window.draw(background);

			circle.setPosition(food.x * 20, food.y * 20);
			window.draw(circle);

			//Draw the snake
			for (int i = 0; i < waz.length; i++)
			{
				square.setPosition(waz.shape[i].x*20, waz.shape[i].y*20);
				window.draw(square);
			}


		gui.draw();
		window.display();
	}

	return 0;
}




//#include <iostream>
//#include <conio.h> //getch()
//#include <ctime>
//#include "headers.h"
//#include "waz.h"
//#include <string>
//
//float framerate = 15;
//
//extern const int ilosc_wierszy;
//extern const int ilosc_kolumn;
//
//int main()
//{
//	//////////////////////INIZJALIZACJA
//	float czas_jednej_klatki = 1 / framerate;
//	clock_t czas;
//	clock_t czas_poczatkowy; //do wyliczenia czasu klatki
//
//	char up = 't';
//	char right = 'h';
//	char bottom = 'g';
//	char left = 'f';
//	//////////////////////INIZJALIZACJA
//
//	for (;;)
//	{
//
//		char input = 0; //z klawiatury
//		waz waz;
//		komorkaweza jedzenie;
//		jedzenie.x = 70;
//		jedzenie.y = 15;//inicjalizacja jedzenia
//		char ekran[ilosc_wierszy][ilosc_kolumn];
//		wyczysc_obraz(ekran);
//		ekran[0][79] = 'd';
//		ekran[19][79] = 'k';
//		static int ilezjadl = 0;
//		ilezjadl = 0;
//		//INICJALIZACJA
//
//
//
//		char znak = menu(ekran); ///////////MENU
//
//		if (znak == '2') { //pokaz wyniki 
//			pokazwyniki();
//		}
//		if (znak == '3') { //ustawienia
//			ustawienia(ekran, up, right, bottom, left);
//		}
//		if (znak == '4') { //wyjscie 
//			break;
//		}
//		if (znak == '1')
//		{
//			for (;;)  //PETLA PROGRAMU
//			{
//				czas_poczatkowy = clock();
//
//				//Instrukcje------------------------------
//				pokaz_obraz(ekran);
//				if (_kbhit()) { input = _getch(); } //Odbieranie informacji z klawiatury
//
//				int czyzjadl = 0; //do obslugi return z edutuj weza
//				if ((czyzjadl = edytuj_weza(waz, input, jedzenie, up, right, bottom, left)) == 1) break; //1 gdzy ugryzl siebie
//				if (czyzjadl == 2) { waz.dlugosc += 1; dodajjedzenie(jedzenie, waz); ilezjadl += 1; } //2 gdy cos zjadl
//				if (rysuj_weza(ekran, waz)) break;
//
//				rysujjedzenie(ekran, jedzenie);
//
//				//Kolejna klatka
//				czas = clock();
//				czekaj_do_konca_klatki(czas_poczatkowy, czas, framerate);
//				if (input == 'q') break;
//			}  //////////////////////PETLA PROGRAMU
//			gameover(ekran);
//			std::cout << "Zjadles: " << ilezjadl << " cukierkow" << std::endl << std::endl;
//			std::string nick;
//			std::cout << "Podaj nick: ";
//			std::cin >> nick;
//			zapiszdopliku(nick, ilezjadl);
//			std::cout << "Nacisnij ENTER"; _getch();
//			std::cout << std::endl << std::endl << std::endl << std::endl;
//
//		}
//
//	}
//
//
//
//
//	//system("pause");
//}