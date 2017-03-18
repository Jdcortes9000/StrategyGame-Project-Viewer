#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

class Player
{
protected:
	int x;
	int y;
	bool team;
	int health;
	string character;
	bool dead;
public:
	
	Player(int _x, int _y, string c, bool _team)
	{
		x = _x;
		y = _y;
		character = c;
		team = _team;
		health = 20;
		dead = false;
	}
	~Player()
	{

	}
	int GetHealth()
	{
		return health;
	}
	void ReduceHealth(int hp)
	{
		health = health - hp;
	}
	int GetX()
	{
		return x;
	}
	void SetX(int _x)
	{
		x = _x;
	}
	int GetY()
	{
		return y;
	}
	void SetY(int _y)
	{
		y = _y;
	}
	bool IsEnemy()
	{
		return team;
	}
	string GetCharacter()
	{
		return character;
	}
	void SetCharacter(string c)
	{
		character = c;
	}
	bool IsDead()
	{
		return dead;
	}
	void Killed(bool b)
	{
		dead = b;
		health = 0;
	}
	void Initialize()
	{
		health = 20;
		dead = false;
	}
	int Attack()
	{
		int damage;
		if (character == "W" || character == "w")
		{
			damage = 8;
			return (rand() % damage) + damage - 1;
		}
		else if (character == "S" || character == "s")
		{
			damage = 10;
			return (rand() % damage) + 1;
		}
		else if (character == "A" || character == "a")
		{
			damage = 6;
			return (rand() % damage) + 2;
		}
		return 0;
	}
	bool InRange(int _x, int _y)
	{
		//int distance = (int)sqrt(pow((_x - x), 2) + pow((_y - y), 2));
		int distance = (int)abs(_x - x) + abs(_y - y);
		if (character == "W" || character == "w")
		{
			if (distance == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (character == "S" || character == "s")
		{
			if (distance < 3 && distance > 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (character == "A" || character == "a")
		{
			if (distance < 5 && distance > 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	bool CollisionCheck(Player opposite, Player C1, Player C2, Player CC1, Player CC2, string d)
	{
		int distance;
		if (d == "l")
		{
			if (x - 1 == 39)
			{
				return true;
			}
			distance = (int)sqrt(pow((opposite.GetX() - x + 1), 2) + pow((opposite.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((C1.GetX() - x + 1), 2) + pow((C1.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((C2.GetX() - x + 1), 2) + pow((C2.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((CC1.GetX() - x + 1), 2) + pow((CC1.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((CC2.GetX() - x + 1), 2) + pow((CC2.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			return false;
		}
		else if (d == "r")
		{
			if (x + 1 == 46)
			{
				return true;
			}
			distance = (int)sqrt(pow((opposite.GetX() - x - 1), 2) + pow((opposite.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((C1.GetX() - x - 1), 2) + pow((C1.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((C2.GetX() - x - 1), 2) + pow((C2.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((CC1.GetX() - x - 1), 2) + pow((CC1.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((CC2.GetX() - x - 1), 2) + pow((CC2.GetY() - y), 2));
			if (distance == 0)
			{
				return true;
			}
			return false;
		}
		else if (d == "u")
		{
			if (y - 1 == 6)
			{
				return true;
			}
			distance = (int)sqrt(pow((opposite.GetX() - x), 2) + pow((opposite.GetY() - y + 1), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((C1.GetX() - x ), 2) + pow((C1.GetY() - y + 1), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((C2.GetX() - x ), 2) + pow((C2.GetY() - y + 1), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((CC1.GetX() - x ), 2) + pow((CC1.GetY() - y + 1), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((CC2.GetX() - x ), 2) + pow((CC2.GetY() - y + 1), 2));
			if (distance == 0)
			{
				return true;
			}
			return false;
		}
		else if (d == "d")
		{
			if (y + 1 == 13)
			{
				return true;
			}
			distance = (int)sqrt(pow((opposite.GetX() - x), 2) + pow((opposite.GetY() - y - 1), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((C1.GetX() - x), 2) + pow((C1.GetY() - y - 1), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((C2.GetX() - x), 2) + pow((C2.GetY() - y -1), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((CC1.GetX() - x), 2) + pow((CC1.GetY() - y - 1), 2));
			if (distance == 0)
			{
				return true;
			}
			distance = (int)sqrt(pow((CC2.GetX() - x), 2) + pow((CC2.GetY() - y - 1), 2));
			if (distance == 0)
			{
				return true;
			}
			return false;
		}
		return true;
	}
};

 
