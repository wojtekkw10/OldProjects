#include <fstream>
#include <string>
#include <cctype> //toupper
#include <ctime>
#include "snake.h"

extern const int ilosc_wierszy;
extern const int ilosc_kolumn;

void czekaj_do_konca_klatki(clock_t czas_poczatku_klatki, clock_t czas_konca_klatki, float framerate)
{
	float czas_jednej_klatki = 1 / framerate;
	while (((double)czas_konca_klatki - (double)czas_poczatku_klatki) / 1000 < czas_jednej_klatki) { czas_konca_klatki = clock(); }
	system("cls");
}

int edytuj_weza(snake & snake, char input, sf::Vector2u jedzenie)
{
	//Sprawdzenie czy user nie ksrecil w siebie samego
	if ((input == 2) && (snake.direction == 4)) snake.direction = 4;
	else if ((input == 4) && (snake.direction == 2)) snake.direction = 2;
	else if ((input == 1) && (snake.direction == 3)) snake.direction = 3;
	else if ((input == 3) && (snake.direction == 1)) snake.direction = 1;
	else
	{
		//wpisanie kierunku do weza
		if (input == 2) snake.direction = 2;
		if (input == 3) snake.direction = 3;
		if (input == 4) snake.direction = 4;
		if (input == 1) snake.direction = 1;
	}

	//Sprawdzenie czy nie wysedl poza mape
	if (snake.direction == 1 && snake.shape[0].y == 0) return 1;
	if (snake.direction == 2 && snake.shape[0].x == 79) return 1;
	if (snake.direction == 3 && snake.shape[0].y == 19) return 1;
	if (snake.direction == 4 && snake.shape[0].x == 0) return 1;

	//Sprawdzenie czy sie nie ugryzl
	for (int i = 1; i < snake.length; i++)
	{
		if ((snake.shape[0].x == snake.shape[i].x) && (snake.shape[0].y == snake.shape[i].y)) return 1;
	}

	bool czy_cos_zjadl = false;
	//Sprawdzenie czy czegos nie zjazd
	for (int i = 1; i < snake.length; i++)
	{
		if ((snake.shape[0].x == jedzenie.x) && (snake.shape[0].y == jedzenie.y)) czy_cos_zjadl = true;
	}

	sf::Vector2u pomoc[1600]; //wpisanie pierwszej przesunieej ju¿ komórki do tab pomocniczej
	if (snake.direction == 2) { pomoc[0].x = snake.shape[0].x + 1; pomoc[0].y = snake.shape[0].y; }
	if (snake.direction == 3) { pomoc[0].y = snake.shape[0].y + 1; pomoc[0].x = snake.shape[0].x; }
	if (snake.direction == 4) { pomoc[0].x = snake.shape[0].x - 1; pomoc[0].y = snake.shape[0].y; }
	if (snake.direction == 1) { pomoc[0].y = snake.shape[0].y - 1; pomoc[0].x = snake.shape[0].x; }

	for (int i = 0; i < snake.length+10; i++)
	{
		pomoc[i + 1].x = snake.shape[i].x;
		pomoc[i + 1].y = snake.shape[i].y;
	} //Wpisanie do tab pomoc reszty we¿a

	for (int i = 0; i < snake.length+10; i++)
	{
		snake.shape[i].x = pomoc[i].x;
		snake.shape[i].y = pomoc[i].y;
	} //przekopiowanie danych z z tablicy pomocniczej

	if (czy_cos_zjadl) return 2;
	return 0;
}


int czy_liczba(char znak)
{
	if (int(znak) >= 48 && int(znak) <= 57) return atoi(&znak);
	else return 0;
}

void dodajjedzenie(sf::Vector2u & jedzenie, snake snake)
{
	for (;;)
	{
		bool czy_znalazlo_miejsce = false;
		srand(clock());
		int x = rand() % 40; //tylko na chwile 20 powinno byc 80
		int y = rand() % 20;
		for (int i = 0; i < snake.length + 1; i++)
		{
			if ((x != snake.shape[i].x) && (y != snake.shape[i].y))
			{
				jedzenie.x = x;
				jedzenie.y = y;
				czy_znalazlo_miejsce = true;
			}
		}

		if (czy_znalazlo_miejsce) break;
	}

}