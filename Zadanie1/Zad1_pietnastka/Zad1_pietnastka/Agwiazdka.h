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

protected:
	vector<vector<int> > open;

	int h;
	int g;
	int f;

public:
	Agwiazdka(int nn, int mm);
	virtual ~Agwiazdka();

	void szukajA(char* sstrategia, vector<int> wierzcholek);
	int znajdzKoszt(vector<int> wierzcholek);
};

