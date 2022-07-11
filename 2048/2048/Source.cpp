#include "Headers.h"

float framerate = 15;

extern const int ilosc_wierszy;
extern const int ilosc_kolumn;
extern const int size;

int main()
{
	//////////////////////INIZJALIZACJA
	char up = 't';
	char right = 'h';
	char bottom = 'g';
	char left = 'f';
	//////////////////////INIZJALIZACJA

	for (;;)
	{

		char input = 0; //z klawiatury
		char ekran[ilosc_wierszy][ilosc_kolumn];
		int polegry[4][4];
		wyczyszczeniepolegry(polegry);
		wyczysc_obraz(ekran);

		//INICJALIZACJA
		std::cout << "\n\n       2048\n\nSterowanie: t,h,g,f";
		_getch();
		dodajliczbe(polegry);
		for (;;)  //PETLA PROGRAMU
		{
			//Instrukcje------------------------------
			
			wyczysc_obraz(ekran);
			rysuj_polegry_do_obraz(polegry, ekran);
			pokaz_obraz(ekran);
			
			do
			{
				input = _getch(); //Odbieranie informacji z klawiatury
			}
			while (!(input == 't' || input == 'f' || input == 'g' || input == 'h'));
			edytujpolegry(polegry, input);



			if (dodajliczbe(polegry) == 1) { //1 gdy nie ma miejsca
				gameover(ekran); break;
			}
			if (input == 'q') break;
		}  //////////////////////PETLA PROGRAMU

		std::cout << "Nacisnij ENTER"; _getch(); break;
		std::cout << std::endl << std::endl << std::endl << std::endl;

	}
	system("pause");
}