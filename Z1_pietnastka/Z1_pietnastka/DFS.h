#pragma once

#include "pietnastka.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

using namespace std;


class DFS :
	public pietnastka
{
public:
	DFS(int nn, int mm);
	virtual ~DFS();

	void szukajDFS(vector<char> sstrategia, vector<int> wierzcholek);
};

