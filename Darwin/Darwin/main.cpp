/** @file */

#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<chrono>

#include "funkcje.h"
#include "struktury.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	string plik_wejsciowy, plik_wyjsciowy;
	double wspolczynnik_wymierania = -1, wspolczynnik_rozmnazania = -1;
	int liczba_pokolen = 0, liczba_par = 0;

	pobierzDane(argc, argv, plik_wejsciowy, plik_wyjsciowy, wspolczynnik_wymierania, wspolczynnik_rozmnazania, liczba_pokolen, liczba_par);

	ifstream wejscie;
	ofstream wyjscie;

	wejscie.open(plik_wejsciowy);

	bool argumenty = sprawdzArgumenty(argc, wejscie, wspolczynnik_wymierania, wspolczynnik_rozmnazania, liczba_pokolen, liczba_par);

	if (!argumenty)
		return 0;

	osobnik* pierwszy = nullptr;

	bool poprawnosc = pobierzZPliku(pierwszy, wejscie);

	if (!poprawnosc)
		return 0;

	wejscie.close();

	zrealizujRozwojPopulacji(pierwszy, wspolczynnik_rozmnazania, wspolczynnik_wymierania, liczba_pokolen, liczba_par);

	wyjscie.open(plik_wyjsciowy);

	wypiszOsobnikow(pierwszy, wyjscie);

	wyjscie.close();

	usunListe(pierwszy);

	return 0;
}
