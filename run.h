#pragma once

#include <string>
#include <vector>

using namespace std;

class Runner
{
	static vector <string> names;

	string _name;

	static void init();

private:

	bool _isAlive=1;
	int Max_velocity, _stamina, _clumsiness;

public:

	Runner();
//	~Runner();

	string name() {return _name;}
	int stamina() {return _stamina;}
	int clumsiness() {return _clumsiness;}
	bool isAlive() {return _isAlive;}

	double runnerSkill();
	string description();

	double velocity,distance=0;

	bool falling();
	void Shoot();
	void weaken();

};