#include "Headers.h"

extern const int ilosc_wierszy;
extern const int ilosc_kolumn;
extern const int size;

void pokaz_obraz(char tab[ilosc_wierszy][ilosc_kolumn])
{
	system("cls");
	for (int i = 0; i < ilosc_wierszy; i++)
	{
		for (int j = 0; j < ilosc_kolumn; j++)
		{
			std::cout << tab[i][j];
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < 80; i++)
	{
		std::cout << '-';
	}
}

void wyczysc_obraz(char tab[ilosc_wierszy][ilosc_kolumn])
{
	for (int i = 0; i < ilosc_wierszy; i++)
	{
		for (int j = 0; j < ilosc_kolumn; j++)
		{
			tab[i][j] = ' ';
		}
	}
}

void wyczysc_polegry(int polegry[size][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			polegry[i][j] = 0;
		}
	}
}

void rysuj_polegry_do_obraz(int polegry[size][size], char obraz[ilosc_wierszy][ilosc_kolumn])
{

	int przesuniecie_w_dol = 2;
	int licznik = 0;

	for (int j = 0; j < size*4; j++)
	{
		if (licznik == 0) //kreski na gorze
		{
			for (int i = 0; i < size * 8+1; i++) //size*4 - ilosc kresek na 1 komorke
			{
				obraz[j+przesuniecie_w_dol-1][i] = '-';
			} //kreski na gorze
		}


		if (!(j % 4 == 3))
		{
			for (int i = 0; i < size; i++)
			{
				obraz[j+przesuniecie_w_dol][i * 8] = '|';                    //Narysowanie pionowej linii
				for (int k = 1; k < 4; k++)            // I spacji po niej
				{
					obraz[j+przesuniecie_w_dol][i + k] = ' ';
				}
				obraz[j+przesuniecie_w_dol][32] = '|'; //kreska konczaca wiersz
			}
		}
		else
		{
			for (int i = 0; i < size * 8+1; i++) //size*4 - ilosc kresek na 1 komorke
			{
				obraz[j+przesuniecie_w_dol][i] = '-';
			} //kreski oddzielajace wiersze
		}
		licznik++;
	}



	for (int i = 0; i < 4; i++)
	{
		_itoa_s(polegry[i][0], &obraz[i * 4 + 3][3], 5, 10);
		_itoa_s(polegry[i][1], &obraz[i * 4 + 3][11], 5, 10);
		_itoa_s(polegry[i][2], &obraz[i * 4 + 3][19], 5, 10);
		_itoa_s(polegry[i][3], &obraz[i * 4 + 3][27], 5, 10);

		if (obraz[i * 4 + 3][3] == '0') obraz[i * 4 + 3][3] = ' ';
		if (obraz[i * 4 + 3][11] == '0') obraz[i * 4 + 3][11] = ' ';  //jezeli 0 nie rysuj nic
		if (obraz[i * 4 + 3][19] == '0') obraz[i * 4 + 3][19] = ' ';
		if (obraz[i * 4 + 3][27] == '0') obraz[i * 4 + 3][27] = ' ';
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if ((obraz[i][j] == -2)) obraz[i][j] = ' ';
		}
	}
}

void wyczyszczeniepolegry(int polegry[size][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			polegry[i][j] = 0;
		}
	}
}

int dodajliczbe(int polegry[size][size])
{
	int ile_pustych = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (polegry[i][j] == 0) ile_pustych = 1;
		}
	}
	if (ile_pustych == 0) return 1;

	if (ile_pustych > 0)
	{
		srand(clock());
		for (;;) //dopoki nie znajdzie wolnego miejsca
		{
			int x = rand() % 4; //wspolrzedne liczby
			int y = rand() % 4;
			int a = rand() % 2; //do losowania
			int b;   //liczba ktora sie pojawi
			if (a == 0) b = 2;
			if (a == 1) b = 4;

			if (polegry[x][y] == 0)
			{
				polegry[x][y] = b;
				break;
			}
		}

	}

	return 0;
}

void gameover(char tab[ilosc_wierszy][ilosc_kolumn])
{
	wyczysc_obraz(tab);
	tab[10][30] = 'G';
	tab[10][31] = 'A';
	tab[10][32] = 'M';
	tab[10][33] = 'E';
	tab[10][34] = 'O';
	tab[10][35] = 'V';
	tab[10][36] = 'E';
	tab[10][37] = 'R';
	pokaz_obraz(tab);
}

void edytujpolegry(int polegry[size][size], char input)
{
	/*Algorytm:
	Przesun liczby w odpowiednim kierunku
	Polacz jezeli sa takie same
	Przesun jeszcze raz
	*/
	if (input == 'f')
	{
		for (int k = 0; k < size*2; k++) //By przesunelo sie do konca
		{
			for (int j = 0; j < size - 1; j++)
			{
				for (int i = 0; i < size; i++) //dla kazdego wiersza
				{
					if (polegry[i][j] == 0)
					{
						polegry[i][j] = polegry[i][j + 1];
						polegry[i][j + 1] = 0;
					}
				}
			}
		}  //przesuniecie
		for (int j = 0; j < size - 1; j++)
		{
			for (int i = 0; i < size; i++) //dla kazdego wiersza
			{
				if (polegry[i][j] == polegry[i][j + 1])
				{
					polegry[i][j] = polegry[i][j] * 2;
					polegry[i][j + 1] = 0;
				}
			}
		}  // polaczenie
		for (int k = 0; k < size * 2; k++) //By przesunelo sie do konca
		{
			for (int j = 0; j < size - 1; j++)
			{
				for (int i = 0; i < size; i++) //dla kazdego wiersza
				{
					if (polegry[i][j] == 0)
					{
						polegry[i][j] = polegry[i][j + 1];
						polegry[i][j + 1] = 0;
					}
				}
			}
		}  //przesuniecie
	}


	if (input == 't')
	{
		for (int k = 0; k < size * 2; k++) //By przesunelo sie do konca
		{
			for (int j = 0; j < size; j++)
			{
				for (int i = 0; i < size - 1; i++) //dla kazdego wiersza
				{
					if (polegry[i][j] == 0)
					{
						polegry[i][j] = polegry[i + 1][j];
						polegry[i + 1][j] = 0;
					}
				}
			}
		}
		for (int j = 0; j < size; j++)
		{
			for (int i = 0; i < size - 1; i++) //dla kazdego wiersza
			{
				if (polegry[i][j] == polegry[i + 1][j])
				{
					polegry[i][j] = polegry[i][j] * 2;
					polegry[i + 1][j] = 0;
				}
			}
		}
		for (int k = 0; k < size * 2; k++) //By przesunelo sie do konca
		{
			for (int j = 0; j < size; j++)
			{
				for (int i = 0; i < size - 1; i++) //dla kazdego wiersza
				{
					if (polegry[i][j] == 0)
					{
						polegry[i][j] = polegry[i + 1][j];
						polegry[i + 1][j] = 0;
					}
				}
			}
		}
	}

	if (input == 'h') //musi sprawdzac od prawej
	{
		for (int k = 0; k < size * 2; k++) //By przesunelo sie do konca
		{
			for (int j = 1; j < size; j++)
			{
				for (int i = 0; i < size; i++) //dla kazdego wiersza
				{
					if (polegry[i][j] == 0)
					{
						polegry[i][j] = polegry[i][j - 1];
						polegry[i][j - 1] = 0;
					}
				}
			}
		}
		for (int j = size; j >= 1; j--)
		{
			for (int i = size; i >= 0; i--) //dla kazdego wiersza
			{
				if (polegry[i][j] == polegry[i][j - 1])
				{
					polegry[i][j] = polegry[i][j] * 2;
					polegry[i][j - 1] = 0;
				}
			}
		}
		for (int k = 0; k < size * 2; k++) //By przesunelo sie do konca
		{
			for (int j = 1; j < size; j++)
			{
				for (int i = 0; i < size; i++) //dla kazdego wiersza
				{
					if (polegry[i][j] == 0)
					{
						polegry[i][j] = polegry[i][j - 1];
						polegry[i][j - 1] = 0;
					}
				}
			}
		}
	}

	if (input == 'g')//musi sprawdzac od dolu - wtedy zadziala
	{
		for (int k = 0; k < size * 2; k++) //By przesunelo sie do konca
		{
			for (int j = 0; j < size; j++)
			{
				for (int i = 1; i < size; i++) //dla kazdego wiersza
				{
					if (polegry[i][j] == 0)
					{
						polegry[i][j] = polegry[i - 1][j];
						polegry[i - 1][j] = 0;
					}
				}
			}
		}
		for (int j = size; j >= 0; j--)
		{
			for (int i = size; i >= 1; i--) //dla kazdego wiersza
			{
				if (polegry[i][j] == polegry[i - 1][j])
				{
					polegry[i][j] = polegry[i][j] * 2;
					polegry[i - 1][j] = 0;
				}
			}
		}
		for (int k = 0; k < size * 2; k++) //By przesunelo sie do konca
		{
			for (int j = 0; j < size; j++)
			{
				for (int i = 1; i < size; i++) //dla kazdego wiersza
				{
					if (polegry[i][j] == 0)
					{
						polegry[i][j] = polegry[i - 1][j];
						polegry[i - 1][j] = 0;
					}
				}
			}
		}
	}
}