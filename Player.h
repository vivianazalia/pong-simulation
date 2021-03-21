#pragma once
#include<stdlib.h>
#include<time.h>

using namespace std;

class Player
{
	string name;
	float hit;
public:
	Player(string _n) {
		name = _n;
	}

	string GetName() {
		return name;
	}

	void SetName(string _newName) {
		name = _newName;
	}

	float GetHit() {
		srand(time(NULL));
		hit = rand() % 100;
		return hit;
	}
};

