#include "stdafx.h"
#include "pietnastka.h"


pietnastka::pietnastka(int nn, int mm)
{
	this->depth = 0;
	this->n = nn;
	this->m = mm;
	this->czyRozwiazano = false;
	this->iloscKrokow = 0;
	this->rozwiazanie = "";
}

void pietnastka::wyswietlPlansze(vector<int> wierzcholek)
{
	vector<int>::iterator iter = wierzcholek.begin();
	int tempN = this->n;
	int tempM = this->m;
	int** plansza = new int*[tempN];
	for (int i = 0; i < tempN; ++i)
	{
		plansza[i] = new int[tempM];
	}

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

void pietnastka::stworzPoprawnyStan()
{
	vector<int> temp;
	int max = (this->n * this->m);
	for (int i = 1; i<max; i++)
	{
		this->ostatniStan.push_back(i);
	}
	this->ostatniStan.push_back(0);
}

bool pietnastka::czyOdwiedzony(vector<int> wierzcholek)
{
	int comp;
	vector<int>::iterator iterWierzcholek = wierzcholek.begin();
	vector< vector<int> >::iterator iter = this->listaStanow.begin();
	for (iter = listaStanow.begin(); iter != listaStanow.end(); iter++)
	{
		iterWierzcholek = wierzcholek.begin();
		comp = 0;
		if ((*iter).size() == wierzcholek.size())
		{
			for (vector<int>::iterator itTemp = (*iter).begin(); itTemp != (*iter).end(); itTemp++)
			{
				if ((*itTemp) == *iterWierzcholek)
				{
					comp++;
				}
				iterWierzcholek++;
			}
			if (comp == wierzcholek.size())
			{
				return true;
			}
		}
	}
	return false;
}

int pietnastka::znajdzZero(vector<int> wierzcholek)
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

//funkcja porownujaca dwie listy. zwraca true, jesli listy s¹ takie same
bool pietnastka::porownaj(vector<int> list1, vector<int> list2)
{
	vector<int>::iterator iter1 = list1.begin();
	vector<int>::iterator iter2 = list2.begin();
	if (list1.size() == list2.size())
	{
		for (iter1 = list1.begin(); iter1 != list1.end(); iter1++)
		{
			if (*iter1 != *iter2)
			{
				return false;
			}
			iter2++;
		}
		return true;
	}
}

void pietnastka::wyswietlRuchy(vector<char> listaRuchow)
{
	for (vector<char>::iterator iterTemp = listaRuchow.begin(); iterTemp != listaRuchow.end(); iterTemp++)
	{
		cout << *iterTemp;
	}
	return;
}

pietnastka::~pietnastka()
{
}
