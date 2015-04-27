// Z1_pietnastka.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "BFS.h"
#include "DFS.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <conio.h>

using namespace std;


bool otworz_do_odczytu(ifstream &plik, char nazwa_pliku[])
{
	plik.open(nazwa_pliku, ios_base::in);
	if (plik.is_open() == false)
	{
		cout << "\nBlad otwarcia do odczytu";
		return false;
	}
	else return true;
}

vector<int> odczytaj(ifstream &plik_we)
{
	vector<int> lista;
	int temp = 0;

	while (!plik_we.eof())
	{
		plik_we >> temp;
		lista.push_back(temp);
	}
	return lista;
}

int *uloz_plansze(vector<int> lista_we, int wymiary[])
{
	//rozmiar planszy NxM
	int n, m;

	//ustalenie rozmiaru planszy
	vector<int>::iterator iter = lista_we.begin();
	n = *iter;
	advance(iter, 1);
	m = *iter;
	advance(iter, 1);

	wymiary[0] = n;
	wymiary[1] = m;


	int** plansza = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		plansza[i] = new int[m];
	}

	//int wiersze = n;
	//int kolumny = m;

	//utworzenie planszy w odpowiednim kszta³cie
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			plansza[i][j] = *iter;
			iter++;
		}
	}

	cout << "Wczytano plansze:" << endl;
	//wyswietlenie planszy
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			cout.width(2);
			cout << plansza[i][j] << " | ";
		}

		cout << endl;
		for (int h = 0; h<m; h++)
		{
			cout << "_____";
		}
		cout << endl << endl << endl;
	}
	//return listawyjsciowa;
	return wymiary;
	
	delete[] wymiary;
	delete[] plansza;
}

int _tmain(int argc, _TCHAR argv[])
{
	//strumien wejsciowy
	ifstream plik_we;

	//lista wszystkich liczb w pliku
	vector<int> lista_pol;

	//pierwszy wierzcholek
	vector<int> pierwszyWierzcholek;

	//strategia przeszukiwania
	char* strategia = new char[5];
//	char* przeszukiwanie = new char[2];

	vector<int> lista;
	vector<int> rozmiar;
	vector<int> wierszy;
	int temp = 0;
	string rozm;
	string wiersz;


	int wymiary[2];
	int wybor;
	
	cout << "Wcisnij:\n1 - jesli chcesz wczytac plansze z pliku\n"
		"2 - jesli chcesz podac dane w kosoli" << endl << endl;
	cin >> wybor;

	switch (wybor)
	{
	case 1:
		//odczyt pliku
		if (otworz_do_odczytu(plik_we, "dane.txt") == false) return 0;
		lista_pol = odczytaj(plik_we);
		plik_we.close();
		cout << "Wczytano plansze: " << endl << endl;
		uloz_plansze(lista_pol, wymiary);
		break;

	case 2:
		cout << "Podaj rozmiar planszy:" << endl;

		for (int i = 0; i<2; i++)
		{
			getline(cin, rozm);
			getch();
		}

		

		int rozm2 = atoi(rozm.c_str());

		cout << rozm2;

		rozmiar.push_back(rozm2);


		
		wymiary[0] = rozmiar[0];
		wymiary[1] = rozmiar[1];

		

		cout << "\nPodaj poczatkowy uklad plaszy:" << endl;
		for (int i = 0; i < wymiary[0]; i++)
		{
			getline(cin, wiersz);
			int wiersz2 = atoi(wiersz.c_str());
			wierszy.push_back(wiersz2);
		}

		cout << "\n\nOdczyt tablicy - wektor" << endl;
		for (int i = 0; i < wierszy.size(); i++)
		{
			cout << wierszy[i];
		}
		
	 /*default:
	    break;*/
	}


	
	
	//*************************************************************
	
	

	char przeszukiwanie;
	przeszukiwanie = argv[0];
	/*
	//wybranie przeszukiwania
	/*cout << "\n Wybierz przeszukiwanie: \n Aby wykonac przeszukiwanie BFS wpisz: -b ";
	cout << "\n Aby wykonac przeszukiwanie DFS wpisz: -d \n Aby wykonac przeszukiwanie A* wpisz: -a \n" << endl;*/
	/*for (int i = 0; i<2; i++)
	{
		char x;
		x = getchar();
		przeszukiwanie[i] = x;
	}
	getchar();*/

	//logika
	/*cout << "Podaj strategie przeszukiwania: " << endl;
	for (int i = 0; i<4; i++)
	{
		char c;
		c = getchar();
		strategia[i] = c;
	}*/



	



	cout << "Podales: " << endl;
	for (int i = 0; i<4; i++)
	{
		cout << strategia[i];
	}
	cout << endl;

	lista_pol.erase(lista_pol.begin(), lista_pol.begin() + 2);
	uloz_plansze(lista_pol, wymiary);

	int wiersze = wymiary[0];
	int kolumny = wymiary[1];

	if (przeszukiwanie == 'b' || przeszukiwanie == 'B')
	{
		//obiektBFS
		BFS obiektBFS = BFS(wiersze, kolumny);
		obiektBFS.stworzPoprawnyStan();
		obiektBFS.listaStanow.push_back(lista_pol);
		obiektBFS.szukajBFS(strategia, lista_pol);
	}
	else if (przeszukiwanie == 'd' || przeszukiwanie == 'D')
	{
		//obiekt DFS
		vector<char> strategiaDFS;
		for (int x = 0; x<4; x++)
		{
			strategiaDFS.push_back(strategia[x]);
		}
		DFS obiektDFS = DFS(wiersze, kolumny);
		obiektDFS.stworzPoprawnyStan();
		obiektDFS.szukajDFS(strategiaDFS, lista_pol);
	}
	else
	{
		cout << "Nie ma takiego przeszukiwania!" << endl;
	}


	//************************************************

	return 0;
}

