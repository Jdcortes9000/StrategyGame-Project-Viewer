#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>

#include "Player.h"
#include "Archerh.h"
#include "Warrior.h"

using namespace std;

class Sorcerer : public Player
{
	friend class Archer;
	friend class Warrior;
protected:
	int damage;

public:

	Sorcerer(int _x, int _y, string c, bool _team) : Player(_x, _y, c, _team)
	{
		srand((unsigned int)time(NULL));
		damage = 10;
	}
	~Sorcerer()
	{

	}
	int Attack()
	{
		return (rand() % damage) + 1;
	}
	bool InRange(int _x, int _y)
	{
		int distance = sqrt(pow((_x - x), 2) + pow((_y - y), 2));
		if (distance < 3 && distance > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool CollisionCheck(Sorcerer PS, Archer P1A, Archer P2A, Warrior P1W, Warrior P2W, string d)
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
		distance = sqrt(pow((PS.GetX() - x), 2) + pow((PS.GetY() - y), 2));
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
		distance = sqrt(pow((P1W.GetX() - x), 2) + pow((P1W.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = sqrt(pow((P2W.GetX() - x), 2) + pow((P2W.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		return false;
	}
};