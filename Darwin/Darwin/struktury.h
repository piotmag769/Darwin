/** @file */
#ifndef STRUKTURY
#define STRUKTURY

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

/** Element listy jednokierunkowej reprezentujacej chromosom osobnika. */
struct lista_ch
{
	int kawalek;                ///<liczba reprezentujaca kawalek chromosomu
	lista_ch* nastepny_kawalek; ///<wskaznik na nastepny kawalek chromosomu
};

/** Element listy jednokierunkowej osobnikow. */
struct osobnik
{
	lista_ch* glowa_chromosomu; ///<wskaznik na poczatek chromosomu osobnika
	osobnik* nastepny_osobnik;  ///<wskaznik na nastepnego osobnika
};








#endif
