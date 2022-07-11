#pragma once
#include <iostream>
#include <ctime>
#include <conio.h>
#include <fstream>

const int ilosc_wierszy = 20;
const int ilosc_kolumn = 80;

const int size = 4;

void pokaz_obraz(char tab[ilosc_wierszy][ilosc_kolumn]);

void wyczysc_obraz(char tab[ilosc_wierszy][ilosc_kolumn]);

void rysuj_polegry_do_obraz(int polegry[size][size], char obraz[ilosc_wierszy][ilosc_kolumn]);

void wyczyszczeniepolegry(int polegry[size][size]);

int dodajliczbe(int polegry[size][size]);

void gameover(char tab[ilosc_wierszy][ilosc_kolumn]);

void edytujpolegry(int polegry[size][size], char input);