/** @file */
#ifndef FUNKCJE
#define FUNKCJE

#include<iostream>
#include<fstream>
#include<string>

#include "struktury.h"

using namespace std;

/** Funkcja pobiera dane z konsoli i wczytuje je do zmiennych.
@param argc liczba argumentow podanych w konsoli
@param argv tablica wskaznikow na argumenty w  konsoli
@param[in,out] plik_wejsciowy nazwa sciezki do pliku wejsciowego
@param[in,out] plik_wyjœciowy nazwa sciezki do pliku wyjsciowego
@param[in,out] wspolczynnik_wymierania wspolczynnik wymierania dla populacji osobnikow
@param[in,out] wspolczynnik_rozmnazania wspolczynnik rozmnazania dla populacji osobnikow
@param[in,out] liczba_pokolen numer pokolenia, ktorego postac nalezy podac w pliku koncowym
@param[in,out] liczba_par liczba par osobnikow, ktorych nalezy ze soba skrzyzowac
*/
void pobierzDane(int argc, char* argv[], string& plik_wejsciowy, string& plik_wyjsciowy, double& wspolczynnik_wymierania, double& wspolczynnik_rozmnazania, int& liczba_pokolen, int& liczba_par);

/** Funkcja sprawdza poprawnosc podanych przez uzytkownika argumentow, zwracajac informacje o ich poprawnosci.
@param argc liczba argumentow podanych w konsol
@param[in,out] wejscie strumien umozliwiajacy odczytanie danych z pliku wejsciowego
@param wspolczynnik_wymierania wspolczynnik wymierania dla populacji osobnikow
@param wspolczynnik_rozmnazania wspolczynnik rozmnazania dla populacji osobnikow
@param liczba_pokolen numer pokolenia, ktorego postac nalezy podac w pliku koncowym
@param liczba_par liczba par osobnikow, ktorych nalezy ze soba skrzyzowac
@return wartosc logiczna zdania "Argumenty sa poprawne."
@warning gdy argumenty sa niepoprawne, funkcja wypisuje do konsoli odpowiedni komunikat
*/
bool sprawdzArgumenty(int argc, ifstream& wejscie, double wspolczynnik_wymierania, double wspolczynnik_rozmnazania, int liczba_pokolen, int liczba_par);

/**  Funkcja dodaje osobnika na koniec listy.
@param[in,out] pierwszy wskaznik na pierwszego osobnika w liscie
@param jakis wskaznik na osobnika, ktorego chcemy dodac na koniec listy
*/
void dodajNaKoniecListyOsobnikow(osobnik*& pierwszy, osobnik* jakis);

/** Funkcja dodaje liczbe na koniec chromosomu.
@param[in,out] wskaznik_na_osobnika wskaznik na osobnika, na ktorego koniec chromosomu chcemy dodac dana liczbe
@param kawalek liczba, ktora chcemy dodac na koniec chromosomu
*/
void dodajNaKoniecChromosomu(osobnik*& wskaznik_na_osobnika, int kawalek);

/** Funkcja pobiera dane z pliku i umieszcza je w liscie, zwracajac informacje o poprawnosci danych w pliku.
@param[in,out] pierwszy wskaznik na pierwszego osobnika w liscie
@param[in,out] wejscie strumien, przez ktory funkcja ma pobrac dane
@return wartosc logiczna zdania "Dane w pliku maja poprawny format."
@warning gdy dane w pliku sa niepoprawne, funcja wypisuje do konsoli odpowiedni komunikat
*/
bool pobierzZPliku(osobnik*& pierwszy, ifstream& wejscie);

/** Funkcja wypisuje chromosom.
@param poczatek_chromosomu wskaznik na poczatek wypisywanego chromosomu
@param[in,out] strumien strumien, do ktorego funkcja ma wypisac chromosom
@warning gdy chromosom nie istnieje, funkcja wypisuje do strumienia komunikat "Osobnik nie istnieje"
*/
void wypiszChromosom(lista_ch* poczatek_chromosomu, ostream& strumien);

/** Funkcja wypisuje chromosomy osobnikow z listy.
@param pierwszy wskaznik na pierwszego osobnika z listy
@param[in,out] strumien strumien, do ktorego funkcja ma wypisac osobnikow
@warning gdy pierwszy osobnik nie istnieje, funkcja wypisuje do strumienia komunikat "Lista jest pusta"
*/
void wypiszOsobnikow(osobnik* pierwszy, ostream& strumien);

/** Funkcja oblicza liczbe osobnikow w liscie.
@param pierwszy wskaznik na pierwszego osobnika w liscie
@return liczba osobnikow w liscie
*/
int liczbaOsobnikow(osobnik* pierwszy);

/** Funkcja oblicza dlugosc chromosomu.
@param poczatek_chromosomu wskaznik na pierwszy kawalek chromosomu
@return dlugosc chromosomu
*/
int dlugoscChromosomu(lista_ch* poczatek_chromosomu);

/** Funkcja oblicza dlugosc listy osobnikow.
@param pierwszy wskaznik na pierwszego osobnika w liscie
@return dlugosc listy osobnikow
*/
int dlugoscListy(osobnik* pierwszy);

/** Funkcja losuje osobnika z listy.
@param pierwszy wskaznik na pierwszego osobnika w liscie
@return wskaznik na wylosowanego z listy osobnika
*/
osobnik* losujOsobnika(osobnik* pierwszy);

/** Funkcja losuje miejsce przerwania chromosomu.
@param jakis wskaznik na osobnika, dla ktorego chcemy wylosowac miejsce przerwania chromosomu
@return wskaznik na wylosowany kawalek chromosomu (miejsce przerwania)
*/
lista_ch* losujPrzerwanie(osobnik* jakis);

/** Funkcja krzyzuje osobnikow z populacji.
@param osobnik1 wskaznik na pierwszego z osobnikow, ktorego chcemy skrzyzowac
@param osobnik2 wskaznik na drugiego z osobnikow, ktorego chcemy skrzyzowac
*/
void krzyzujOsobnikow(osobnik*& osobnik1, osobnik*& osobnik2);

/**	Funkcja modyfikuje liste osobnikow zgodnie z trescia zadania (wykonuje krzyzowania i modyfikacje w zaleznosci od przystosowania do warunkow srodowiska, wyznaczajac pokolenie szukane przez uzytkownika).
@param[in,out] pierwszy wskaznik na pierwszego osobnika w liscie
@param wspolczynnik_rozmnazania wspolczynnik rozmnazania dla populacji osobnikow
@param wspolczynnik_wymierania wspolczynnik wymierania dla populacji osobnikow
@param liczba_pokolen numer pokolenia, ktorego postac nalezy podac w pliku koncowym
@param liczba_par liczba par osobnikow, ktorych nalezy ze soba skrzyzowac
*/
void zrealizujRozwojPopulacji(osobnik*& pierwszy, double wspolczynnik_rozmnazania, double wspolczynnik_wymierania, int liczba_pokolen, int liczba_par);

/** Funkcja wyznacza przystosowanie osobnika do warunkow srodowiska.
@param jakis wskaznik na osobnika, ktorego przystosowanie do warunkow srodowiska chcemy wyznaczyc
@return wspolczynnik przystosowania osobnika do warunkow srodowiska
*/
double wyznaczPrzystosowanie(osobnik* jakis);

/** Funkcja znajduje poprzedniego osobnika w liscie.
@param pierwszy wskaznik na pierwszego osobnika w liscie
@param jakis wskaznik na osobnika, ktorego poprzednika chcemy wyznaczyc
@return wskaznik na poprzedniego osobnika w liscie
@warning funkcja zwraca nullptr, gdy osobnik, ktorego poprzednika szukamy, jest pierwszy w liscie lub gdy pierwszy osobnik nie istnieje
*/
osobnik* znajdzPoprzedniOsobnik(osobnik* pierwszy, osobnik* jakis);

/** Funkcja znajduje poprzedni kawalek chromosomu.
@param poczatek wskaznik na pierwszy kawalek chromosomu
@param jakis wskaznik na kawalek chromosomu, ktorego poprzednika chcemy znalezc
@return wskaznik na poprzedni kawalek chromosomu
@warning funkcja zwraca nullptr, gdy kawalek, ktorego poprzednika szukamy jest jednoczesnie pierwszym kawalkiem chromosomu lub gdy pierwszy kawalek nie istnieje
*/
lista_ch* znajdzPoprzedniKawalekChromosomu(lista_ch* poczatek, lista_ch* jakis);

/** Funkcja usuwa dany kawalek z chromosomu.
@param[in,out] poczatek wskaznik na pierwszy kawalek chromosomu
@param[in,out] wskaznik na kawalek chromosomu, ktorego chcemy usunac
@param[in,out] poprzedni wskaznik na poprzedni, wzgledem tego, ktorego chcemy usunac, kawalek chromosomu
*/
void usunKawalekChromosomu(lista_ch*& poczatek, lista_ch*& jakis, lista_ch*& poprzedni);

/** Funkcja usuwa caly chromosom.
@param[in,out] poczatek_chromosomu wskaznik na pierwszy kawalek chromosomu, ktorego chcemy usunac
*/
void usunCalyChromosom(lista_ch*& poczatek_chromosomu);

/** Funkcja usuwa danego osobnika razem z jego chromosomem.
@param[in,out] pierwszy wskaznik na pierwszego osobnika w liscie
@param[in,out] jakis wskaznik na osobnika, ktorego chcemy usunac
@param[in,out] poprzedni wskaznik na poprzedniego, wzgledem tego, ktorego chcemy usunac, osobnika
*/
void usunOsobnika(osobnik*& pierwszy, osobnik*& jakis, osobnik*& poprzedni);

/** Funkcja usuwa cala liste osobnikow razem z ich chromosomami.
@param[in,out] pierwszy wskaznik na pierwszego osobnika w liscie
*/
void usunListe(osobnik*& pierwszy);


#endif

