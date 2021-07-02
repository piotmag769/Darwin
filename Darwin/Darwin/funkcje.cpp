/** @file */

#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<chrono>

#include "funkcje.h"
#include "struktury.h"

using namespace std;

void pobierzDane(int argc, char* argv[], string& plik_wejsciowy, string& plik_wyjsciowy, double& wspolczynnik_wymierania, double& wspolczynnik_rozmnazania, int& liczba_pokolen, int& liczba_par)
{
	string argument;
	for (int i = 0; i < argc; i++)
	{
		argument = argv[i];
		if (argument == "-i")
			plik_wejsciowy = argv[i + 1];
		if (argument == "-o")
			plik_wyjsciowy = argv[i + 1];
		if (argument == "-w")
			wspolczynnik_wymierania = atof(argv[i + 1]);
		if (argument == "-r")
			wspolczynnik_rozmnazania = atof(argv[i + 1]);
		if (argument == "-p")
			liczba_pokolen = atoi(argv[i + 1]);
		if (argument == "-k")
			liczba_par = atoi(argv[i + 1]);
	}
}

bool sprawdzArgumenty(int argc, ifstream& wejscie, double wspolczynnik_wymierania, double wspolczynnik_rozmnazania, int liczba_pokolen, int liczba_par)
{
	if (argc != 13)
	{
		cout << "Nieprawidlowa liczba argumentow";
		return false;
	}

	if (!(wspolczynnik_wymierania >= 0 && wspolczynnik_wymierania <= 1 && wspolczynnik_rozmnazania >= 0 && wspolczynnik_rozmnazania <= 1) || (wspolczynnik_wymierania >= wspolczynnik_rozmnazania))
	{
		cout << "Bledny wspolczynnik wymierania/rozmnazania";
		return false;
	}

	if (liczba_pokolen <= 0)
	{
		cout << "Bledna liczba pokolen";
		return false;
	}

	if (liczba_par <= 0)
	{
		cout << "Bledna liczba par";
		return false;
	}

	if (!wejscie.good())
	{
		cout << "Brak dostepu do pliku wejsciowego/plik wejsciowy nie istnieje";
		return false;
	}

	return true;
}


void dodajNaKoniecListyOsobnikow(osobnik*& pierwszy, osobnik* jakis)
{
	if (!pierwszy)
	{
		pierwszy = new osobnik{ jakis->glowa_chromosomu, jakis->nastepny_osobnik };
	}

	else
	{
		auto wsk = pierwszy;
		while (wsk->nastepny_osobnik)
			wsk = wsk->nastepny_osobnik;

		wsk->nastepny_osobnik = new osobnik{ jakis->glowa_chromosomu, jakis->nastepny_osobnik };
	}
}

void dodajNaKoniecChromosomu(osobnik*& wskaznik_na_osobnika, int kawalek)
{
	if (!(wskaznik_na_osobnika->glowa_chromosomu))
		wskaznik_na_osobnika->glowa_chromosomu = new lista_ch{ kawalek, nullptr };
	else
	{
		auto p = wskaznik_na_osobnika->glowa_chromosomu;
		while (p->nastepny_kawalek)
			p = p->nastepny_kawalek;

		p->nastepny_kawalek = new lista_ch{ kawalek, nullptr };
	}
}

bool pobierzZPliku(osobnik*& pierwszy, ifstream& wejscie)
{
	string linijka;

	while (!wejscie.eof())
	{
		getline(wejscie, linijka);

		osobnik* wskaznik_na_osobnika = new osobnik{ nullptr, nullptr };

		for (int i = 0; i < linijka.size(); i++)
		{
			if (linijka.size() == 1)
			{
				cout << "Nieprawidlowy format pliku (pojedyncze chromosomy)";
				usunListe(pierwszy);
				delete wskaznik_na_osobnika;
				wejscie.close();
				return false;
			}

			if (linijka[i] != ' ' && linijka[i] != '	')
			{
				int kawalek = linijka[i] - 48;
				if (!(kawalek >= 0 && kawalek <= 9))
				{
					cout << "Nieprawidlowy format pliku (chromosomy nie skladaja sie z cyfr)";
					usunListe(pierwszy);
					delete wskaznik_na_osobnika;
					wejscie.close();
					return false;
				}
				dodajNaKoniecChromosomu(wskaznik_na_osobnika, kawalek);
			}
		}

		if (wskaznik_na_osobnika->glowa_chromosomu == nullptr)
		{
			cout << "Nieprawidlowy format pliku (enter lub pusty plik)";
			usunListe(pierwszy);
			delete wskaznik_na_osobnika;
			wejscie.close();
			return false;
		}

		dodajNaKoniecListyOsobnikow(pierwszy, wskaznik_na_osobnika);

		delete wskaznik_na_osobnika;
	}
	return true;
}

void wypiszChromosom(lista_ch* poczatek_chromosomu, ostream& strumien)
{
	if (!poczatek_chromosomu)
		strumien << "Osobnik nie istnieje" << endl;
	else
	{
		auto p = poczatek_chromosomu;
		while (p)
		{
			strumien << p->kawalek;
			p = p->nastepny_kawalek;
		}
		strumien << endl;
	}
}

void wypiszOsobnikow(osobnik* pierwszy, ostream& strumien)
{
	if (!pierwszy)
		strumien << "Lista jest pusta" << endl;
	else
		while (pierwszy)
		{
			wypiszChromosom(pierwszy->glowa_chromosomu, strumien);
			pierwszy = pierwszy->nastepny_osobnik;
		}
}

int liczbaOsobnikow(osobnik* pierwszy)
{
	int i = 0;
	while (pierwszy)
	{
		pierwszy = pierwszy->nastepny_osobnik;
		i++;
	}
	return i;
}

int dlugoscChromosomu(lista_ch* poczatek_chromosomu)
{
	int d = 0;
	while (poczatek_chromosomu)
	{
		poczatek_chromosomu = poczatek_chromosomu->nastepny_kawalek;
		d++;
	}
	return d;
}

int dlugoscListy(osobnik* pierwszy)
{
	int l = 0;
	while (pierwszy)
	{
		pierwszy = pierwszy->nastepny_osobnik;
		l++;
	}
	return l;
}

osobnik* losujOsobnika(osobnik* pierwszy)
{
	int numer = rand() % liczbaOsobnikow(pierwszy);

	osobnik* osobnik = pierwszy;

	for (numer; numer > 0; numer--)
	{
		osobnik = osobnik->nastepny_osobnik;
	}

	return osobnik;
}

lista_ch* losujPrzerwanie(osobnik* jakis)
{
	int przerwanie = rand() % (dlugoscChromosomu(jakis->glowa_chromosomu) - 1);

	lista_ch* lista = jakis->glowa_chromosomu;

	for (przerwanie; przerwanie > 0; przerwanie--)
	{
		lista = lista->nastepny_kawalek;
	}

	return lista;
}

void krzyzujOsobnikow(osobnik*& osobnik1, osobnik*& osobnik2)
{
	lista_ch* lista1 = losujPrzerwanie(osobnik1);
	lista_ch* lista2 = losujPrzerwanie(osobnik2);

	auto tmp = lista1->nastepny_kawalek;
	lista1->nastepny_kawalek = lista2->nastepny_kawalek;
	lista2->nastepny_kawalek = tmp;
}

void zrealizujRozwojPopulacji(osobnik*& pierwszy, double wspolczynnik_rozmnazania, double wspolczynnik_wymierania, int liczba_pokolen, int liczba_par)
{
	for (liczba_pokolen; liczba_pokolen > 0; liczba_pokolen--)
	{
		if (dlugoscListy(pierwszy) == 0)
			break;

		int schowek = liczba_par;

		if (dlugoscListy(pierwszy) == 1)
		{
			if (wyznaczPrzystosowanie(pierwszy) > wspolczynnik_rozmnazania)
			{
				osobnik* nowy = new osobnik{ nullptr, nullptr };
				auto p = pierwszy->glowa_chromosomu;

				while (p)
				{
					dodajNaKoniecChromosomu(nowy, p->kawalek);
					p = p->nastepny_kawalek;
				}

				dodajNaKoniecListyOsobnikow(pierwszy, nowy);

				delete nowy;
			}

			if (wyznaczPrzystosowanie(pierwszy) < wspolczynnik_wymierania)
			{
				auto p = pierwszy;
				auto tmp = znajdzPoprzedniOsobnik(pierwszy, p);
				usunOsobnika(pierwszy, p, tmp);
			}
		}
		else
		{
			for (schowek; schowek > 0; schowek--)
			{
				osobnik* osobnik1 = losujOsobnika(pierwszy);
				osobnik* osobnik2 = losujOsobnika(pierwszy);

				while (osobnik1 == osobnik2)
					osobnik2 = losujOsobnika(pierwszy);

				krzyzujOsobnikow(osobnik1, osobnik2);
			}

			auto ktorys = pierwszy;

			for (int i = dlugoscListy(pierwszy); i > 0; i--)
			{
				if (wyznaczPrzystosowanie(ktorys) < wspolczynnik_wymierania)
				{
					auto poprzedni = znajdzPoprzedniOsobnik(pierwszy, ktorys);
					auto p = ktorys->nastepny_osobnik;
					usunOsobnika(pierwszy, ktorys, poprzedni);
					ktorys = p;
				}
				else if (wyznaczPrzystosowanie(ktorys) > wspolczynnik_rozmnazania)
				{
					osobnik* nowy = new osobnik{ nullptr, nullptr };
					auto p = ktorys->glowa_chromosomu;

					while (p)
					{
						dodajNaKoniecChromosomu(nowy, p->kawalek);
						p = p->nastepny_kawalek;
					}

					dodajNaKoniecListyOsobnikow(pierwszy, nowy);

					ktorys = ktorys->nastepny_osobnik;

					delete nowy;
				}
				else
					ktorys = ktorys->nastepny_osobnik;
			}
		}
	}
}

double wyznaczPrzystosowanie(osobnik* jakis)
{
	double przystosowanie = 0.0;
	auto p = jakis->glowa_chromosomu;

	while (p)
	{
		przystosowanie += ((p->kawalek % 9) / 8.0);
		p = p->nastepny_kawalek;
	}

	przystosowanie = przystosowanie / dlugoscChromosomu(jakis->glowa_chromosomu);

	return przystosowanie;
}

osobnik* znajdzPoprzedniOsobnik(osobnik* pierwszy, osobnik* jakis)
{
	if (!pierwszy || jakis == pierwszy)
		return nullptr;

	auto p = pierwszy;

	while (p && p->nastepny_osobnik != jakis)
		p = p->nastepny_osobnik;

	return p;
}

lista_ch* znajdzPoprzedniKawalekChromosomu(lista_ch* poczatek, lista_ch* jakis)
{
	if (!poczatek || jakis == poczatek)
		return nullptr;

	auto p = poczatek;

	while (p && p->nastepny_kawalek != jakis)
		p = p->nastepny_kawalek;

	return p;
}

void usunKawalekChromosomu(lista_ch*& poczatek, lista_ch*& jakis, lista_ch*& poprzedni)
{
	if (poprzedni == nullptr)
	{
		poczatek = jakis->nastepny_kawalek;
		delete jakis;
	}
	else
	{
		poprzedni->nastepny_kawalek = jakis->nastepny_kawalek;
		delete jakis;
	}
}

void usunCalyChromosom(lista_ch*& poczatek_chromosomu)
{
	while (poczatek_chromosomu)
	{
		auto p = poczatek_chromosomu->nastepny_kawalek;
		delete poczatek_chromosomu;
		poczatek_chromosomu = p;
	}
}

void usunOsobnika(osobnik*& pierwszy, osobnik*& jakis, osobnik*& poprzedni)
{
	if (!poprzedni)
	{
		pierwszy = jakis->nastepny_osobnik;
		usunCalyChromosom(jakis->glowa_chromosomu);
		delete jakis;
	}
	else
	{
		poprzedni->nastepny_osobnik = jakis->nastepny_osobnik;
		usunCalyChromosom(jakis->glowa_chromosomu);
		delete jakis;
	}
}

void usunListe(osobnik*& pierwszy)
{
	while (pierwszy)
	{
		auto p = pierwszy->nastepny_osobnik;
		usunCalyChromosom(pierwszy->glowa_chromosomu);
		delete pierwszy;
		pierwszy = p;
	}
}
