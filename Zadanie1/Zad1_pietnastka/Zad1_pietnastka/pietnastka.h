#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

using namespace std;


class pietnastka
{

protected:

	//stan pozadany
	vector<int> ostatniStan;
	//startegia przeszukiwania
	char* strategia;
	//glebokosc
	int depth;
	//liczba wierszy
	int n;
	//liczba kolumn
	int m;
	//ilosc wykonanych iteracji
	int iloscKrokow;
	//
	string rozwiazanie;
	//przebyta droga
	vector<char> ruchy;

public:
	pietnastka(int nn, int mm);
	~pietnastka();

	bool czyRozwiazano;
	//lista odwiedzonych stanow
	vector<vector<int> > listaStanow;

	void stworzPoprawnyStan();
	int znajdzZero(vector<int> wierzcholek);
	bool czyOdwiedzony(vector<int> lista);
	bool porownaj(vector<int> list1, vector<int> list2);
	void wyswietlRuchy(vector<char> listaRuchow);
	void wyswietlPlansze(vector<int> wierzcholek);


};

