#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>

#include "Player.h"
#include "Archerh.h"
#include "Sorcerer.h"

using namespace std;

class Warrior : public Player
{
	friend class Archer;
	friend class Sorcerer;
protected:
	int damage;

public:

	Warrior(int _x, int _y, string c, bool _team) : Player(_x, _y, c, _team)
	{
		srand((unsigned int)time(NULL));
		damage = 8;
	}
	~Warrior()
	{

	}
	int Attack()
	{
		return (rand() % damage) + damage - 1;
	}
	bool InRange(int _x, int _y)
	{
		int distance = sqrt(pow((_x - x), 2) + pow((_y - y), 2));
		if (distance == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool CollisionCheck(Warrior PW, Archer P1A, Archer P2A, Sorcerer P1S, Sorcerer P2S, string d)
	{
		int distance;
		if (d == "l")
		{
			if (x - 1 == 39)
			{
				return true;
			}
		}
		else if (d == "r")
		{
			if (x + 1 == 46)
			{
				return true;
			}
		}
		else if (d == "u")
		{
			if (y - 1 == 6)
			{
				return true;
			}
		}
		else if (d == "d")
		{
			if (y + 1 == 13)
			{
				return true;
			}
		}
		distance = sqrt(pow((PW.GetX() - x), 2) + pow((PW.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = sqrt(pow((P1A.GetX() - x), 2) + pow((P1A.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = sqrt(pow((P2A.GetX() - x), 2) + pow((P2A.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = sqrt(pow((P1S.GetX() - x), 2) + pow((P1S.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = sqrt(pow((P2S.GetX() - x), 2) + pow((P2S.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		return false;
	}
};