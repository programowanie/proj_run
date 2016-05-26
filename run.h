#pragma once

#include <string>
#include <vector>

using namespace std;

class Runner
{
	static vector <string> names;

	string _name;
	int Max_velocity, _stamina, _clumsiness;

	static void init();

public:
	Runner();
//	~Runner();

	string name() {return _name;}
	int stamina() {return _stamina;}
	int clumsiness() {return _clumsiness;}

	double runnerSkill();
	string description();

	double velocity=Max_velocity,distance=0;
};