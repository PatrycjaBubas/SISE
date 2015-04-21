// Generator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define IL 6		//ilosc plikow do wygenerowania
#define MAX_N 10	//najwieksza liczba wierszy
#define MAX_M 10	//najwieksza liczba kolumn

using namespace std;

bool otworz_do_zapisu(ofstream &plik, string nazwa_pliku)
{
	plik.open(nazwa_pliku, ios_base::out);
	if (plik.is_open() == false)
	{
		cout << "\nBlad otwarcia do zapisu";
		return false;
	}
	else return true;
}

void zapisz(ofstream &plik_wy, vector<int> plansza, int n, int m)
{
	plik_wy << n << " " << m << endl;

	for (int i = 0; i < n*m; i++)
	{
		if ((i%m) != (m - 1))
		{
			plik_wy << plansza[i] << " ";
		}
		else
		{
			plik_wy << plansza[i] << " " << endl;
		}
	}
}


void wyswietlPlansze(vector<int> wierzcholek, int n, int m)
{
	vector<int>::iterator iter = wierzcholek.begin();
	int tempN = n;
	int tempM = m;


	int** plansza = new int*[n];
	for (int i = 0; i < n; i++)
	{
		plansza[i] = new int[m];
	}

	//utworzenie planszy
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			plansza[i][j] = *iter;
			iter++;
		}
	}

	//wyswietlenie planszy
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(6) << plansza[i][j];
		}
		cout << endl;
	}
	cout << endl << endl;

	delete[] plansza;

}

int znajdzZero(vector<int> wierzcholek)
{
	int counterZero = 0;
	vector<int> temp(wierzcholek);
	for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++)
	{
		if ((*it) == 0)
		{
			return counterZero;
		}
		else
		{
			counterZero++;
		}
	}
	return 0;
}

void tasujPlansze(vector<int> wierzcholek, int n, int m)
{
	int s;		//wartosc strategii
	char strategia;
	string nazwa;

	ofstream plik_wy;


	char s_tab[] = { 'L', 'P', 'G', 'D' }; //tablica strategii

	vector<int> nowyStan(wierzcholek);

	//generujemy IL plikow
	for (int licznik = 0, s = 0; licznik < IL;s++)
	{
		//s = rand() % 4;
		strategia = s_tab[s];

		cout << "\nstrategia: " << strategia << endl;

		int zero = znajdzZero(nowyStan);

		if (strategia == 'L' && zero % m != 0)
		{
			vector<int>::iterator it1 = nowyStan.begin();
			advance(it1, zero);
			vector<int>::iterator it2 = it1;
			advance(it2, -1);
			swap(*it1, *it2);

			wyswietlPlansze(nowyStan, n, m);
			
			licznik++;

			//konwersja int na string
			ostringstream ss;
			ss << licznik;
			string str = ss.str();

			nazwa = "../../Zad1_pietnastka/Zad1_pietnastka/" + str + ".txt"; //polaczenie stringow
			
			if (otworz_do_zapisu(plik_wy, nazwa) == false) cout << endl;//sprawdzenie czy plik otworzyl sie poprawnie
			zapisz(plik_wy, nowyStan, n, m);//zapis do pliku
			plik_wy.close();

			
		}
		else if (strategia == 'P' && zero%m != (m - 1))
		{
			vector<int>::iterator it1 = nowyStan.begin();
			advance(it1, zero);
			vector<int>::iterator it2 = it1;
			advance(it2, +1);
			swap(*it1, *it2);

			wyswietlPlansze(nowyStan, n, m);
			licznik++;

			ostringstream ss;
			ss << licznik;
			string str = ss.str();

			nazwa = "../../Zad1_pietnastka/Zad1_pietnastka/" + str + ".txt";

			if (otworz_do_zapisu(plik_wy, nazwa) == false) cout << endl;
			zapisz(plik_wy, nowyStan, n, m);
			plik_wy.close();
		}
		else if (strategia == 'G' && zero >= m)
		{
			vector<int>::iterator it1 = nowyStan.begin();
			advance(it1, zero);
			vector<int>::iterator it2 = it1;
			advance(it2, -m);
			swap(*it1, *it2);
			
			wyswietlPlansze(nowyStan, n, m);
			licznik++;

			ostringstream ss;
			ss << licznik;
			string str = ss.str();

			nazwa = "../../Zad1_pietnastka/Zad1_pietnastka/" + str + ".txt";

			if (otworz_do_zapisu(plik_wy, nazwa) == false) cout << endl;
			zapisz(plik_wy, nowyStan, n, m);
			plik_wy.close();
		}
		else if (strategia == 'D' && zero < (n*m) - m)
		{
			vector<int>::iterator it1 = nowyStan.begin();
			advance(it1, zero);
			vector<int>::iterator it2 = it1;
			advance(it2, +m);
			swap(*it1, *it2);

			wyswietlPlansze(nowyStan, n, m);
			licznik++;

			ostringstream ss;
			ss << licznik;
			string str = ss.str();

			nazwa = "../../Zad1_pietnastka/Zad1_pietnastka/" + str + ".txt";

			if (otworz_do_zapisu(plik_wy, nazwa) == false) cout << endl;
			zapisz(plik_wy, nowyStan, n, m);
			plik_wy.close();
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	int n, m;	//wymiary planszy

	int tmp = 0;
	int temp;

	vector<int> lista;


	n = (rand() % (MAX_N - 1)) + 2;
	m = (rand() % (MAX_M - 1)) + 2;

	cout << "Plansza o wymiarach NxM. N= " << n << " M= " << m << endl << endl;
	

	//deklaracja tablicy dwuwymiarowej
	int** plansza_wej = new int*[n];
	for (int i = 0; i < n; i++)
	{
		plansza_wej[i] = new int[m];
	}

	//utworzenie poczatkowej planszy
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			plansza_wej[i][j] = tmp;
			lista.push_back(plansza_wej[i][j]);
			tmp++;
		}
	}

	//przesuniecie 0 na koniec listy
	for (int i = 0; i < lista.size()-1; i++)
	{
		temp = lista[i];
		lista[i] = lista[i + 1];
		lista[i + 1] = temp;
	}

	
	//Wyswietlenie vectora lista
	//for (int i = 0; i < lista.size(); i++)
	//{
	//	cout << setw(5) << lista[i]<<endl;
	//}


	tasujPlansze(lista, n, m);


	return 0;
}

