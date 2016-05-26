#include "run.h"
#include <stdlib.h>
#include <fstream>
#include <iterator>

vector <string> Runner::names;

void Runner::init()
{
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

int randomValue(int a, int b)
{
	return a + rand() % b;	
}

Runner::Runner()
{
	static int amountOfNames = (init(), names.size());
	_name = names[rand() % amountOfNames];
	Max_velocity = randomValue(15,30);
	_stamina = randomValue(25,75);
	_clumsiness = randomValue(25,75);
}

string Runner::description()
{
	return _name + 
		"\n\tMax Velocity: " + to_string(Max_velocity)  + "[km/h]" +
		"\n\tStamina: " + to_string(_stamina) + 
		"\n\tClumsiness: " + to_string(_clumsiness) + 
		"\n\tRunnerSkill: " + to_string(runnerSkill()) + "\n\t";
}


double Runner::runnerSkill()
{
	double skills = 
		(Max_velocity * _stamina) / (_clumsiness* 1000000.);
	return skills;
}