#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>

#include "Player.h"
#include "Warrior.h"
#include "Sorcerer.h"

using namespace std;

class Archer : public Player
{
	friend class Warrior;
	friend class Sorcerer;
protected:
	int damage;

public:

	Archer(int _x, int _y, string c, bool _team) : Player(_x, _y, c, _team)
	{
		srand((unsigned int)time(NULL));
		damage = 6;
	}
	~Archer()
	{

	}
	int Attack()
	{
		return (rand() % damage) + 2;
	}
	bool InRange(int _x, int _y)
	{
		int distance = sqrt(pow((_x - x), 2) + pow((_y - y), 2));
		if (distance < 5 && distance > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool CollisionCheck(Archer PA, Warrior P1W, Warrior P2W, Sorcerer P1S, Sorcerer P2S, string d)
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
		distance = (int)sqrt(pow((PA.GetX() - x), 2) + pow((PA.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = (int)sqrt(pow((P1W.GetX() - x), 2) + pow((P1W.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = (int)sqrt(pow((P2W.GetX() - x), 2) + pow((P2W.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = (int)sqrt(pow((P1S.GetX() - x), 2) + pow((P1S.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		distance = (int)sqrt(pow((P2S.GetX() - x), 2) + pow((P2S.GetY() - y), 2));
		if (distance == 0)
		{
			return true;
		}
		return false;
	}
};