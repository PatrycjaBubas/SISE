#pragma once

#include "pietnastka.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;


class Agwiazdka :
	public pietnastka
{

public:
	Agwiazdka(int nn, int mm);
	virtual ~Agwiazdka();

	vector<vector<int> > listaOpen;

	void szukajA(vector<int> wierzcholek);
	int znajdzLiczbe(int liczba, vector<int> wierzcholek);
	double znajdzKoszt(vector<int> wierzcholek);
	bool czyWOpen(vector<int> wierzcholek);
	int gdzieWOpen;
};

