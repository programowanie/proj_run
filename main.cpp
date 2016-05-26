#include "run.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

#define N 3

using namespace std;


void report(int timepiece,Runner runners[],vector<int> shot);
int winning_one(Runner runners[]);
int losing_one(Runner runners[]);
bool falling(int chance);

int main(int argc, char const *argv[])
{
	srand(argc == 2 
		? atoi(argv[1]) 
		: time(NULL));
	
	Runner runners[N];
	//Opisy zawodników
	for (int i=0; i<N; i++)
		printf("%s\n", runners[i].description().c_str());

	//wektor zastrzelonych
	vector<int> shot;

	//Wyscig
	for(int timepiece=0;timepiece<101;timepiece+=10)
	{
		if(timepiece==0) cout << "\tSTART!" << endl;
		else report(timepiece,runners,shot);

		for(int i=0;i<N; i++)
		{
			bool ifshot=0;
			for(int j=0;j<shot.size();j++) //Sprawdza czy zawodnik zostal juz zabity
			{if(i==shot[j]) ifshot=1;}

			if(falling(runners[i].clumsiness())) //Szansa na upadek/zastrzelenie
			{
			cout << runners[i].name() << " upadł i został zastrzelony!" << endl;
			shot.push_back(i);
			} 
			else if(ifshot=0)
			{

			runners[i].distance+=runners[i].velocity; //!!! ŹLE DODAJE || prędkość jest w km/h, przemnóż przez 1/6 aby dobry dystans był
			runners[i].velocity-=1/runners[i].stamina();
			}
		}

		if(timepiece%30==0&&timepiece!=0) // Co 30 minut najgorszy zostaje zastrzelony
		{
			shot.push_back(losing_one(runners));
			cout << runners[losing_one(runners)].name() << " został zastrzelony bo biegł ostatni" << endl;
		}

		if(shot.size()==N-1)
		{
			cout << runners[winning_one(runners)].name() << " jest ostatnim żyjącym zawodnikiem! Wygrał i jako nagrodę dostaje kulkę w łeb" << endl;
		}
	}
}

int winning_one(Runner runners[])
{
	int best=0;
	for(int i=0;i<N;i++) if(runners[i].distance>runners[best].distance) best=i;
	return best;
}
int losing_one(Runner runners[])
{
	int worst=0;
	for(int i=0;i<N;i++) if(runners[i].distance<runners[worst].distance) worst=i;
	return worst;
}

void report(int timepiece,Runner runners[],vector<int> shot)
{
	cout << endl << "Minęło " << timepiece << " minut." << endl;
	for(int i=0;i<N; i++)
		{
			bool ifshot=0;
			for(int j=0;j<shot.size();j++) //Sprawdza czy zawodnik zostal juz zabity
			{if(i==shot[j]) ifshot=1;}

			if(ifshot==0)
			{
			cout << runners[i].name() << "[" << i+1 << "] pokonał " << runners[i].distance << "km"
			<< "\tAktualna predkosc: " << runners[i].velocity << endl;
			break;
			}
		}

}

bool falling(int chance)
{
	if(rand()%750<chance) return 1;
	else return 0;
}