#pragma once

#include "pietnastka.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

using namespace std;


class BFS :
	public pietnastka
{
public:
	BFS(int nn, int mm);
	virtual ~BFS();

	void szukajBFS(char* sstrategia, vector<int> wierzcholek);
};

