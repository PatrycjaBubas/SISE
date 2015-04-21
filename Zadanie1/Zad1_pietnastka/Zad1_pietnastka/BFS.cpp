#include "BFS.h"


BFS::BFS(int nn, int mm) : pietnastka(nn, mm)
{
}

void BFS::szukajBFS(char* sstrategia, vector<int> wierzcholek)
{

	int zero;
	int i;
	while((this->czyRozwiazano == false) && (!this->listaStanow.empty()) )
	{
		zero = znajdzZero(wierzcholek);
		i = 0;
		do
		{
			cout << "Strategia: " << sstrategia[i] << endl;
			if ((sstrategia[i] == 'L' || sstrategia[i] == 'l') && zero%m != 0)
			{
				cout << "\n \n Wejscie w L \n \n" ; 
				vector<int> nowyStan(wierzcholek);
				vector<int>::iterator it1 = nowyStan.begin();
				advance(it1, zero);
				vector<int>::iterator it2 = it1;
				advance(it2, -1);
				swap(*it1, *it2);
				wyswietlPlansze(nowyStan);
				this->ruchy.push_back('L');
				this->iloscKrokow += 1;


				if((porownaj(nowyStan, this->ostatniStan) == false) && (czyOdwiedzony(nowyStan) == false))
				{
					this->listaStanow.push_back(nowyStan);
				}
				if((porownaj(nowyStan, this->ostatniStan)) == true)
				{
					this->czyRozwiazano = true;
					break;
				}


			}
			else if((sstrategia[i] == 'P' || sstrategia[i] == 'p') && zero%m != (m - 1))
			{
				cout << "\n \n Wejscie w P \n \n" ; 
				vector<int> nowyStan(wierzcholek);
				vector<int>::iterator it1 = nowyStan.begin();
				advance(it1, zero);
				vector<int>::iterator it2 = it1;
				advance(it2, +1);
				swap(*it1, *it2);
				wyswietlPlansze(nowyStan);
				this->ruchy.push_back('P');
				this->iloscKrokow += 1;

				if((porownaj(nowyStan, this->ostatniStan) == false) && (czyOdwiedzony(nowyStan) == false))
				{
					this->listaStanow.push_back(nowyStan);
				}
				if((porownaj(nowyStan, this->ostatniStan)) == true)
				{
					this->czyRozwiazano = true;
					break;
				}

			}
			else if((sstrategia[i] == 'G' || sstrategia[i] == 'g') && zero >= m)
			{
				cout << "\n \n Wejscie w G \n \n" ; 
				vector<int> nowyStan(wierzcholek);
				vector<int>::iterator it1 = nowyStan.begin();
				advance(it1, zero);
				vector<int>::iterator it2 = it1;
				advance(it2, -m);
				swap(*it1, *it2);
				wyswietlPlansze(nowyStan);
				this->ruchy.push_back('G');
				this->iloscKrokow += 1;

				if((porownaj(nowyStan, this->ostatniStan) == false) && (czyOdwiedzony(nowyStan) == false))
				{
					this->listaStanow.push_back(nowyStan);
				}
				if((porownaj(nowyStan, this->ostatniStan)) == true)
				{
					this->czyRozwiazano = true;
					break;
				}

			}
			else if((sstrategia[i] == 'D' || sstrategia[i] == 'd') && zero < (n*m) - m)
			{
				cout << "\n \n Wejscie w D \n \n" ; 
				vector<int> nowyStan(wierzcholek);
				vector<int>::iterator it1 = nowyStan.begin();
				advance(it1, zero);
				vector<int>::iterator it2 = it1;
				advance(it2, +m);
				swap(*it1, *it2);
				wyswietlPlansze(nowyStan);
				this->ruchy.push_back('D');
				this->iloscKrokow += 1;

				if((porownaj(nowyStan, this->ostatniStan) == false) && (czyOdwiedzony(nowyStan) == false))
				{
					this->listaStanow.push_back(nowyStan);
				}
				if((porownaj(nowyStan, this->ostatniStan)) == true)
				{
					this->czyRozwiazano = true;
					break;
				}

			}

			i++;
		} while((i<4) && (this->czyRozwiazano==false));
		
		this->listaStanow.erase(this->listaStanow.begin());
		if((!this->listaStanow.empty()) && (this->czyRozwiazano==false))
		{vector<vector<int> >::iterator iterSasiad = this->listaStanow.begin();
		szukajBFS(sstrategia, (*iterSasiad));
		return;}
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
	if(this->listaStanow.empty())
	{
		cout << "\n \n -1 ";
		return;
	}
}

BFS::~BFS()
{
}
