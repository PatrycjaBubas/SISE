// Z1pietnastka.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BFS.h"
#include "DFS.h"
#include "Agwiazdka.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <conio.h>

using namespace std;

int wiersze;
int kolumny;

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

void uloz_plansze(vector<int> lista_we)
{
	if (lista_we.size() > 2){
		//iterator listy wejsciowej
		vector<int>::iterator iter_we = lista_we.begin();
		//pierwsze dwa elementy listy sa jej rozmiarem. n=ilosc wierszy, m= ilosc kolumn
		wiersze = lista_we.at(0);
		kolumny = lista_we.at(1);


		//utworzenie tablicy dwuwymiarowej odpowiadajacej za wyglad planszy
		int** plansza = new int*[wiersze];
		for (int i = 0; i < wiersze; ++i)
		{
			plansza[i] = new int[kolumny];
		}

		//przypisanie pol planszy
		//utworzenie planszy w odpowiednim ksztalcie
		lista_we.erase(lista_we.begin(), lista_we.begin() + 2);
		iter_we = lista_we.begin();
		for (int i = 0; i<wiersze; i++)
		{
			for (int j = 0; j<kolumny; j++)
			{
				plansza[i][j] = *iter_we;
				iter_we++;
			}
		}

		cout << "\n Wczytano plansze: \n \n";

		//wyswietlenie planszy
		for (int i = 0; i<wiersze; i++)
		{
			for (int j = 0; j<kolumny; j++)
			{
				cout.width(2);
				cout << plansza[i][j] << " | ";
			}

			cout << endl;
			for (int h = 0; h<kolumny; h++)
			{
				cout << "_____";
			}
			cout << endl << endl << endl;
		}
		//zwolnienie pamieci
		for (int w = 0; w < wiersze; w++)
		{
			delete[] plansza[w];
		}
		delete[] plansza;
	}
	return;
}

int _tmain(int argc, char* argv[])
{
	//strumien wejsciowy
	ifstream plik_we;

	//lista wszystkich liczb w pliku/strumieniu
	vector<int> lista_pol;

	//pierwszy wierzcholek grafu
	vector<int> pierwszy_wierzcholek;

	//strategia przeszukiwania
	char* strategia = new char[5];

	//algorytm przeszukiwania
	char przeszukiwanie;
	int wybor;

	przeszukiwanie = *argv[1];

	cout << "\nPrzeszukiwanie: " << przeszukiwanie << endl;
	if (argc == 3){
		for (int i = 0; i < 4; i++)
		{
			strategia[i] = argv[2][i * 2];
		}

		cout << "\nStrategia: ";
		for (int i = 0; i < 4; i++)
		{
			cout << strategia[i];
		}
	}

	cout << "\n\nPodaj w jaki sposob chcesz wczytac poczatkowy uklad planszy. Wcisnij:"
		"\n1 - jesli chcesz wczytac z pliku"
		"\n2 - jesli chcesz podac ja w konsoli" << endl;
	cout << "\nTwoj wybor: ";
	cin >> wybor;


	switch (wybor)
	{
	case 1:
		//odczyt pliku
		if (otworz_do_odczytu(plik_we, "dane.txt") == false) return 0;
		lista_pol = odczytaj(plik_we);
		plik_we.close();

		cout << "Wczytano plansze: " << endl << endl;
		uloz_plansze(lista_pol);

		break;
	case 2:
		//odczyt z konsoli
		cout << "\nPodaj wymiary tablicy:" << endl;
		cin >> wiersze >> kolumny;
		cout << "\n Wiersze: " << wiersze << "\n Kolumny: " << kolumny << endl;
		//utworzenie tablicy dwuwymiarowej odpowiadajacej za wyglad planszy
		int** plansza = new int*[wiersze];
		for (int i = 0; i < wiersze; ++i)
		{
			plansza[i] = new int[kolumny];
		}
		cout << "\nPodaj stan poczatkowy ukladanki:" << endl;
		//wczytywanie pierwszego wierzcholka grafu z konsoli
		for (int i = 0; i < wiersze; i++)
		{
			for (int j = 0; j < kolumny; j++)
			{
				cin >> plansza[i][j];
			}
		}

		//przekazanie wierzcholka do vectora
		lista_pol.push_back(wiersze);
		lista_pol.push_back(kolumny);
		for (int i = 0; i < wiersze; i++)
		{
			for (int j = 0; j < kolumny; j++)
			{
				int poleint = (int)plansza[i][j];
				lista_pol.push_back(poleint);
			}
		}


		cout << "Wczytany wektor:" << endl;
		for (int i = 0; i < (wiersze*kolumny) + 2; i++)
		{
			cout << lista_pol.at(i);
		}

		uloz_plansze(lista_pol);
		break;
	}
	lista_pol.erase(lista_pol.begin(), lista_pol.begin() + 2);


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
	else if (przeszukiwanie == 'a' || przeszukiwanie == 'A')
	{
		Agwiazdka obiektAgwiazdka = Agwiazdka(wiersze, kolumny);
		obiektAgwiazdka.stworzPoprawnyStan();
		obiektAgwiazdka.szukajA(lista_pol);
	}
	else
	{
		cout << "Nie ma takiego przeszukiwania!" << endl;
	}


	cout << endl;

	system("pause");
	return 0;
}
