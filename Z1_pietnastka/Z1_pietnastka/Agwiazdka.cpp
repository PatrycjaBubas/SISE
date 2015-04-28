#include "stdafx.h"
#include "Agwiazdka.h"

using namespace std;

Agwiazdka::Agwiazdka(int nn, int mm) : pietnastka(nn, mm)
{
}

double Agwiazdka::znajdzKoszt(vector<int> wierzcholek)
{
	double koszt = 0;
	double vx, vy;
	double costX, costY;
	int polozenie;

	for (int i = 1; i < (this->n * this->m); i++)
	{
		polozenie = znajdzLiczbe(i, wierzcholek);
		vx = polozenie % (this->m);
		vy = floor(polozenie / this->m);
		costX = abs(vx - ((i - 1) % this->m));
		costY = abs(vy - floor((i - 1) / this->m));
		koszt += (costX + costY);
	}
	return koszt;
}

int Agwiazdka::znajdzLiczbe(int liczba, vector<int> wierzcholek)
{
	int counter = 0;
	vector<int> temp(wierzcholek);
	for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++)
	{
		if ((*it) == liczba)
			return counter;
		else
			counter++;
	}
	return 0;
}



bool Agwiazdka::czyWOpen(vector<int> wierzcholek)
{
	int comp;
	vector<int>::iterator iterWierzcholek = wierzcholek.begin();
	vector< vector<int> >::iterator iter = this->listaOpen.begin();
	for (iter = listaOpen.begin(); iter != listaOpen.end(); iter++)
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
				else
				{
					this->gdzieWOpen = comp;
					return false;
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

void Agwiazdka::szukajA(vector<int> wierzcholek)
{
	double h = znajdzKoszt(wierzcholek);
	double g = 0;
	double f = 0 + h;
	int zero = 0;

	vector<int> pustyPoprzednik;
	zero = znajdzZero(wierzcholek);
	this->listaOpen.push_back(pustyPoprzednik);
	this->listaOpen.push_back(wierzcholek);
	while (!listaOpen.empty())
	{
		vector<int> temp(listaOpen.back());
		wyswietlPlansze(temp);
		listaOpen.pop_back();
		if (porownaj(temp, this->ostatniStan) == true)
		{
			this->czyRozwiazano = true;
			break;
		}
		this->iloscKrokow += 1;
		//pojscie w lewo
		if (zero%this->m != 0)
		{
			vector<int> potomnyLewo(temp);
			vector<int>::iterator it1 = potomnyLewo.begin();
			advance(it1, zero);
			vector<int>::iterator it2 = it1;
			advance(it2, -1);
			swap(*it1, *it2);

			if (czyOdwiedzony(potomnyLewo) == false)
			{

				g = this->iloscKrokow;
				f = g + znajdzKoszt(potomnyLewo);
				if (czyWOpen(potomnyLewo) == false)
				{
					listaOpen.push_back(potomnyLewo);
					this->ruchy.push_back('L');
				}
				else
				{
					listaOpen.erase(listaOpen.begin() + this->gdzieWOpen);
					listaOpen.push_back(potomnyLewo);
				}
			}
		}
		//pojscie w prawo
		if (zero%this->m != (this->m - 1))
		{
			vector<int> potomnyPrawo(temp);
			vector<int>::iterator it1 = potomnyPrawo.begin();
			advance(it1, zero);
			vector<int>::iterator it2 = it1;
			advance(it2, +1);
			swap(*it1, *it2);

			if (czyOdwiedzony(potomnyPrawo) == false)
			{

				g = this->iloscKrokow;
				f = g + znajdzKoszt(potomnyPrawo);
				if (czyWOpen(potomnyPrawo) == false)
				{
					listaOpen.push_back(potomnyPrawo);
					this->ruchy.push_back('P');
				}
				else
				{
					listaOpen.erase(listaOpen.begin() + this->gdzieWOpen);
					listaOpen.push_back(potomnyPrawo);
				}
			}
		}
		//pojscie w gore
		if (zero >= this->m)
		{
			vector<int> potomnyGora(temp);
			vector<int>::iterator it1 = potomnyGora.begin();
			advance(it1, zero);
			vector<int>::iterator it2 = it1;
			advance(it2, -this->m);
			swap(*it1, *it2);

			if (czyOdwiedzony(potomnyGora) == false)
			{

				g = this->iloscKrokow;
				f = g + znajdzKoszt(potomnyGora);
				if (czyWOpen(potomnyGora) == false)
				{
					this->ruchy.push_back('G');
					listaOpen.push_back(potomnyGora);
				}
				else
				{
					listaOpen.erase(listaOpen.begin() + this->gdzieWOpen);
					listaOpen.push_back(potomnyGora);
				}
			}
		}
		//pojscie w dol
		if (zero < (this->n * this->m) - this->m)
		{
			vector<int> potomnyDol(temp);
			vector<int>::iterator it1 = potomnyDol.begin();
			advance(it1, zero);
			vector<int>::iterator it2 = it1;
			advance(it2, +this->m);
			swap(*it1, *it2);

			if (czyOdwiedzony(potomnyDol) == false)
			{

				g = this->iloscKrokow;
				f = g + znajdzKoszt(potomnyDol);
				if (czyWOpen(potomnyDol) == false)
				{
					listaOpen.push_back(potomnyDol);
					this->ruchy.push_back('D');
				}
				else
				{
					listaOpen.erase(listaOpen.begin() + this->gdzieWOpen);
					listaOpen.push_back(potomnyDol);
				}
			}
		}
		listaStanow.push_back(temp);
	}
	if (this->czyRozwiazano == true)
	{
		{
			cout << "Udalo sie rozwiazac ukladanke!" << endl;
			cout << "Liczba iteracji: " << this->iloscKrokow << endl;
			cout << "Sciezka przeszukiwania: ";
			wyswietlRuchy(ruchy);
			cout << endl << endl;
			return;
		}
	}
	else
	{
		cout << "-1";
		return;
	}
}

Agwiazdka::~Agwiazdka()
{
}
