#include "stdafx.h"
#include "Agwiazdka.h"

using namespace std;

Agwiazdka::Agwiazdka(int nn, int mm) : pietnastka(nn, mm)
{
	this->h = 0;			//koszt
}

int Agwiazdka::znajdzKoszt(vector<int> wierzcholek)
{
	int zero;
	int koszt = 0;
	zero = znajdzZero(wierzcholek);
	int szerokosc = this->m;
	int wysokosc = this->n;

	koszt = (szerokosc - (zero%szerokosc)); //koszt przejscia do prawej krawedzi
	koszt += (wysokosc - floor(zero / szerokosc)); //koszt przejscia do dolnej krawedzi

	return 0;
}

void Agwiazdka::szukajA(char* sstrategia, vector<int> wierzcholek)
{
	int zero;
	zero = znajdzZero(wierzcholek);
	vector<vector<int> >::iterator iterOpen = this->open.begin();
	vector<int> pusty;
	vector<int>::iterator itL, itP, itD, itG, it2L, it2P, it2G, it2D;
	open.push_back(pusty);
	int i = 0;
	this->h = znajdzKoszt(wierzcholek);
	this->g = 0;
	this->f = 0 + this->h;
	open.push_back(wierzcholek);
	if (this->czyRozwiazano == false)
	{
		while (!open.empty())
		{
			if (porownaj(ostatniStan, open.back()) == true)
			{
				czyRozwiazano = true;
				break;
			}
			if (zero%m != 0){
				vector<int> sasiadLewo(wierzcholek);
				itL = sasiadLewo.begin();
				advance(itL, zero);
				it2L = itL;
				advance(it2L, -1);
				swap(*itL, *it2L);
				//wyswietlPlansze(nowyStan);
				open.push_back(sasiadLewo);
			}

			if (zero%m != (m - 1)){
				vector<int> sasiadPrawo(wierzcholek);
				itP = sasiadPrawo.begin();
				advance(itP, zero);
				it2P = itP;
				advance(it2P, +1);
				swap(*itP, *it2P);
				open.push_back(sasiadPrawo);
			}

			if (zero >= m){
				vector<int> sasiadGora(wierzcholek);
				itG = sasiadGora.begin();
				advance(itG, zero);
				vector<int>::iterator it2G = itG;
				advance(it2G, -m);
				swap(*itG, *it2G);
				open.push_back(sasiadGora);
			}

			if (zero < (n*m) - m){
				vector<int> sasiadDol(wierzcholek);
				itD = sasiadDol.begin();
				advance(itD, zero);
				vector<int>::iterator it2D = itD;
				advance(it2D, +1);
				swap(*itD, *it2D);
				open.push_back(sasiadDol);
			}

			open.pop_back();
		}
	}
	if (czyRozwiazano == true)
	{
		cout << "Udalo sie rozwiazac ukladanke!" << endl;
		return;
	}

}

Agwiazdka::~Agwiazdka()
{
}
