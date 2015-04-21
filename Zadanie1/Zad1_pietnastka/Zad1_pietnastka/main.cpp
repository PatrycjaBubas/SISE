#include "BFS.h"
#include "DFS.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <conio.h>

using namespace std;

int wiersze, kolumny = 0;
bool otworz_do_odczytu(ifstream &plik, char nazwa_pliku[]);     //funkcja otwiera plik do odczytu
vector<int> odczytaj(ifstream &plik_we);                               //funkcja, ktora odczytuje z pliku
void uloz_plansze(vector<int> lista_pol);                         //funkcja ktora wyswietla wczytane liczby w postaci planszy
void stworzPierwszyWierzcholek(vector<int> wczytaneLiczby, vector<int> wyjsciowy);  //funkcja ktora przekazuje wczytane liczby w odpowiednia liste



int main()
{
	//strumien wejsciowy
	ifstream plik_we;
	//lista wszystkich liczb w pliku
	vector<int> lista_pol;
	//pierwszy wierzcholek
	vector<int> pierwszyWierzcholek;
	//strategia przeszukiwania
	char* strategia = new char[5];
	char* przeszukiwanie = new char[2];
	//odczyt pliku
	if (otworz_do_odczytu(plik_we, "dane.txt") == false) return 0;
	lista_pol = odczytaj(plik_we);
	plik_we.close();

	cout << "Wczytano plansze: " << endl << endl;
	uloz_plansze(lista_pol);


	//wybranie przeszukiwania
	cout << "\n Wybierz przeszukiwanie: \n Aby wykonac przeszukiwanie BFS wpisz: -b ";
	cout << "\n Aby wykonac przeszukiwanie DFS wpisz: -d \n Aby wykonac przeszukiwanie A* wpisz: -a \n" << endl;
	for (int i = 0; i<2; i++)
	{
		char x;
		x = getchar();
		przeszukiwanie[i] = x;
	}
	getchar();
	//logika
	cout << "Podaj strategie przeszukiwania: " << endl;
	for (int i = 0; i<4; i++)
	{
		char c;
		c = getchar();
		strategia[i] = c;
	}
	cout << "Podales: " << endl;
	for (int i = 0; i<4; i++)
	{
		cout << strategia[i];
	}
	cout << endl;

	lista_pol.erase(lista_pol.begin(), lista_pol.begin() + 2);


	if (przeszukiwanie[1] == 'b' || przeszukiwanie[1] == 'B')
	{
		//obiektBFS
		BFS obiektBFS = BFS(wiersze, kolumny);
		obiektBFS.stworzPoprawnyStan();
		obiektBFS.listaStanow.push_back(lista_pol);
		obiektBFS.szukajBFS(strategia, lista_pol);
	}
	else if (przeszukiwanie[1] == 'd' || przeszukiwanie[1] == 'D')
	{
		//obiekt DFS
		vector<char> strategiaDFS;
		for(int x=0; x<4; x++)
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


	system("pause");
	return 0;
}

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
	//rozmiar planszy NxM
	int n, m;
	//ustalenie rozmiaru planszy
	vector<int>::iterator iter = lista_we.begin();
	n = *iter;
	advance(iter, 1);
	m = *iter;
	advance(iter, 1);

	int** plansza = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		plansza[i] = new int[m];
	}

	wiersze = n;
	kolumny = m;
	//utworzenie planszy w odpowiednim kszta³cie
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			plansza[i][j] = *iter;
			iter++;
		}
	}

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

	delete[] plansza;
}