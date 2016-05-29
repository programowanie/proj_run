#include "run.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

#define N 3 //ilość zawodników

using namespace std;


bool report(int timepiece,Runner runners[], int dead);
int winning_one(Runner runners[]);
int losing_one(Runner runners[]);

int main(int argc, char const *argv[])
{
	srand(argc == 2 
		? atoi(argv[1]) 
		: time(NULL));
	
	//Tablica zawodników
	Runner runners[N];

	//Opisy zawodników
	for (int i=0; i<N; i++)
		printf("%s\n", runners[i].description().c_str());

	//Ilość zabitych
	int dead=0;

	//Wyścig
	for(int timepiece=0;;timepiece+=10)
	{
		//Raport
		if(timepiece==0) cout << "\t\tSTART!" << endl;
		else if(report(timepiece,runners,dead)) break;

		if(timepiece%30==0 && timepiece!=0) // Co 30 minut najgorszy zostaje zastrzelony
		{
			cout << "\n\t" << runners[losing_one(runners)].name() << " został zastrzelony bo biegł ostatni!" << endl;
			runners[losing_one(runners)].Shoot();
			dead++;
		}

		//Efekty biegu
		for(int i=0;i<N; i++)
		{

			if(runners[i].isAlive())
			{
				if(runners[i].falling()) //Szansa na upadek/zastrzelenie
				{
					runners[i].Shoot();
					dead++;
					cout << "\n\t" << runners[i].name() << " upadł i został zastrzelony!" << endl;
				}
				else
				{
					runners[i].distance+=(runners[i].velocity/6);
					runners[i].weaken();
				}
			}
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
	int worst;
	for(int i=0;i<N;i++) if(runners[i].isAlive()) {worst=i; break;}
	for(int i=0;i<N;i++) if(runners[i].distance<runners[worst].distance && runners[i].isAlive()) worst=i;
	return worst;
}

bool report(int timepiece,Runner runners[],int dead)
{
	if(dead==N)
	{
		cout << "\n\t    WSZYSCY NIE ŻYJĄ!\n";
		for(int i=0;i<N; i++)
		cout << "\t" << runners[i].name() << "[" << i+1 << "] pokonał " << runners[i].distance << "km" << endl;
		cout << "\t    NAJDALEJ DOBIEGŁ " << runners[winning_one(runners)].name() << endl;
		return 1;
	}

	else
	{
	cout << endl << "Minęło " << timepiece << " minut." << endl;
	for(int i=0;i<N; i++)
		{
			
			cout << runners[i].name() << "[" << i+1 << "] pokonał " << runners[i].distance << "km"
			<< "\tAktualna predkosc: " << runners[i].velocity;
			if(!runners[i].isAlive()) cout << "\tDEAD";
			cout << endl;
		}
	return 0;
	}

}