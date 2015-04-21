#include "DFS.h"

#define GLEBOKOSC 50

using namespace std;


DFS::DFS(int nn, int mm) : pietnastka(nn, mm)
{
}

void DFS::szukajDFS(vector<char> sstrategia, vector<int> wierzcholek)
{
	int zero;
	int i;
	while((this->czyRozwiazano == false) && (this->depth < GLEBOKOSC) && (this->depth >= 0))
	{
		zero=znajdzZero(wierzcholek);
		i=0;
		this->depth += 1;
		do
		{

			cout << "\n Strategia: " << sstrategia.at(i) << endl;
			if ((sstrategia.at(i) == 'L' || sstrategia.at(i) == 'l') && zero%m != 0)
			{
				vector<int> nowyStan(wierzcholek);
				vector<int>::iterator it1 = nowyStan.begin();
				advance(it1, zero);
				vector<int>::iterator it2 = it1;
				advance(it2, -1);
				swap(*it1, *it2);

				if((porownaj(nowyStan, this->ostatniStan))==true)
				{
					wyswietlPlansze(nowyStan);
					this->czyRozwiazano = true;
					break;
				}
				else if((this->depth < GLEBOKOSC) && (czyOdwiedzony(nowyStan)==false))
				{
					cout << "\n \n Wejscie w L \n \n" ; 
					wyswietlPlansze(nowyStan);
					this->listaStanow.push_back(nowyStan);

					this->ruchy.push_back('L');
					this->iloscKrokow += 1;
					szukajDFS(sstrategia, nowyStan);
					return;
				}
				else if(czyOdwiedzony(nowyStan)==true)
				{
					this->depth -= 1;
				}
			}
			else if((sstrategia.at(i) == 'P' || sstrategia.at(i) == 'p') && zero%m != (m - 1))
			{

				vector<int> nowyStan(wierzcholek);
				vector<int>::iterator it1 = nowyStan.begin();
				advance(it1, zero);
				vector<int>::iterator it2 = it1;
				advance(it2, +1);
				swap(*it1, *it2);


				if((porownaj(nowyStan, this->ostatniStan))==true)
				{
					wyswietlPlansze(nowyStan);
					this->czyRozwiazano = true;
					break;
				}
				else if((this->depth < GLEBOKOSC) && (czyOdwiedzony(nowyStan)==false))
				{
					cout << "\n \n Wejscie w P \n \n" ; 
					this->listaStanow.push_back(nowyStan);
					wyswietlPlansze(nowyStan);
					this->ruchy.push_back('P');
					this->iloscKrokow += 1;
					szukajDFS(sstrategia, nowyStan);
					return;
				}
				else if(czyOdwiedzony(nowyStan)==true)
				{
					this->depth -= 1;
				}
			}
			else if((sstrategia.at(i) == 'G' || sstrategia.at(i) == 'g') && zero >= m)
			{

				vector<int> nowyStan(wierzcholek);
				vector<int>::iterator it1 = nowyStan.begin();
				advance(it1, zero);
				vector<int>::iterator it2 = it1;
				advance(it2, -m);
				swap(*it1, *it2);

				if((porownaj(nowyStan, this->ostatniStan))==true)
				{
					wyswietlPlansze(nowyStan);
					this->czyRozwiazano = true;
					break;
				}
				else if((this->depth < GLEBOKOSC) && (czyOdwiedzony(nowyStan)==false))
				{
					cout << "\n \n Wejscie w G \n \n" ; 
					this->listaStanow.push_back(nowyStan);
					wyswietlPlansze(nowyStan);
					this->ruchy.push_back('G');
					this->iloscKrokow += 1;
					szukajDFS(sstrategia, nowyStan);
					return;
				}
				else if(czyOdwiedzony(nowyStan)==true)
				{
					this->depth -= 1;
				}
			}
			else if((sstrategia.at(i) == 'D' || sstrategia.at(i) == 'd') && zero < (n*m) - m)
			{

				vector<int> nowyStan(wierzcholek);
				vector<int>::iterator it1 = nowyStan.begin();
				advance(it1, zero);
				vector<int>::iterator it2 = it1;
				advance(it2, +m);
				swap(*it1, *it2);

				if((porownaj(nowyStan, this->ostatniStan))==true)
				{
					wyswietlPlansze(nowyStan);
					this->czyRozwiazano = true;
					break;
				}
				else if((this->depth < GLEBOKOSC) && (czyOdwiedzony(nowyStan)==false))
				{
					cout << "\n \n Wejscie w D \n \n" ;
					this->listaStanow.push_back(nowyStan);
					wyswietlPlansze(nowyStan);
					this->ruchy.push_back('D');
					this->iloscKrokow += 1;
					szukajDFS(sstrategia, nowyStan);
					return;
				}
				else if(czyOdwiedzony(nowyStan)==true)
				{
					this->depth -= 1;
				}
			}


			i++;
		}
		while((i<4) && this->czyRozwiazano==false);
	}
	if(this->czyRozwiazano == true)
	{
		cout << "Udalo sie rozwiazac ukladanke!" << endl;
		cout << "Liczba iteracji: " << this->iloscKrokow << endl;
		cout << "Sciezka przeszukiwania: ";
		wyswietlRuchy(ruchy);
		cout << endl << endl;
		return;
	}
	else
	{
		cout << "\n \n -1 \n";
		return;
	}
}

DFS::~DFS()
{
}
