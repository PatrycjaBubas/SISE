// Z1pietnastka.cpp : Defines the entry point for the console application.
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

void uloz_plansze(vector<int> lista_we)
{
	if (lista_we.size() > 2){
		//rozmiar plnaszy NxM
		int wiersze, kolumny;
		//iterator listy wejsciowej
		vector<int>::iterator iter_we = lista_we.begin();
		//pierwsze dwa elementy listy sa jej rozmiarem. n=ilosc wierszy, m= ilosc kolumn
		wiersze = *iter_we;
		iter_we++;
		kolumny = *iter_we;
		iter_we++;

		//utworzenie tablicy dwuwymiarowej odpowiadajacej za wyglad planszy
		int** plansza = new int*[wiersze];
		for (int i = 0; i < wiersze; ++i)
		{
			plansza[i] = new int[kolumny];
		}

		//przypisanie pol planszy
		//utworzenie planszy w odpowiednim ksztalcie
		for (int i = 0; i<wiersze; i++)
		{
			for (int j = 0; j<kolumny, iter_we != lista_we.end(); j++)
			{
				plansza[i][j] = *iter_we;
				iter_we++;
			}
		}

		cout << "\n Wczytano plansze \n";

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
		for (int x = 0; x<wiersze; x++)
		{
			delete[] plansza;
		}
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

	przeszukiwanie = *argv[1];

	cout << "\nPrzeszukiwanie: " << przeszukiwanie << endl;

	strategia[0] = *argv[2];
	strategia[1] = *argv[3];
	strategia[2] = *argv[4];
	strategia[3] = *argv[5];

	cout << "\nStrategia:" << endl;

	for (int i = 0; i < 4; i++)
	{
		cout<<strategia[i]<<endl;
	}


	cout << endl;


	system("pause");
	return 0;
}
