#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
#include "Player.h"


#define _CRTDBG_MAP_ALLOC
#include<cstdlib>
#include<crtdbg.h>


using namespace std;
class DTSTimer
{
	unsigned int startTime;
public:
	DTSTimer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime()
	{
		return (clock() - startTime);
	}

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while (clock() - st < milli) {}
	}

};
void SetXYPosition(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Display(Player P1Warrior, Player P2Warrior, Player P1Archer, Player P2Archer, Player P1Sorcerer, Player P2Sorcerer, int round, vector<int> order)
{
	
	system("cls");
	cout << "  Round: " << round;
	cout << "\n";
	cout << "Turn Order: ";
	for (unsigned int i = 0; i < order.size(); i++)
	{
		if (order[i] == 1)
		{
			if(P1Warrior.IsDead() == false)
			cout << "W ";
		}
		else if (order[i] == 2)
		{
			if (P1Sorcerer.IsDead() == false)
			cout << "S ";
		}
		else if (order[i] == 3)
		{
			if (P1Archer.IsDead() == false)
			cout << "A ";
		}
		else if (order[i] == 4)
		{
			if (P2Warrior.IsDead() == false)
			cout << "w ";
		}
		else if (order[i] == 5)
		{
			if (P2Sorcerer.IsDead() == false)
			cout << "s ";
		}
		else if (order[i] == 6)
		{
			if (P2Archer.IsDead() == false)
			cout << "a ";
		}
	}
	cout << "\n\n\n";
	cout << "P1: W: " << P1Warrior.GetHealth() << "/20, A: " << P1Archer.GetHealth() << "/20, S: " << P1Sorcerer.GetHealth() << "/20 \n";
	cout << "P2: w: " << P2Warrior.GetHealth() << "/20, a: " << P2Archer.GetHealth() << "/20, s: " << P2Sorcerer.GetHealth() << "/20 \n\n";
	cout << "\t\t\t\t\t******\n";
	cout << "\t\t\t\t\t******\n";
	cout << "\t\t\t\t\t******\n";
	cout << "\t\t\t\t\t******\n";
	cout << "\t\t\t\t\t******\n";
	cout << "\t\t\t\t\t******\n";
	SetXYPosition(P1Warrior.GetX(), P1Warrior.GetY());
	cout << P1Warrior.GetCharacter();
	SetXYPosition(P1Archer.GetX(), P1Archer.GetY());
	cout << P1Archer.GetCharacter();
	SetXYPosition(P1Sorcerer.GetX(), P1Sorcerer.GetY());
	cout << P1Sorcerer.GetCharacter();
	SetXYPosition(P2Warrior.GetX(), P2Warrior.GetY());
	cout << P2Warrior.GetCharacter();
	SetXYPosition(P2Archer.GetX(), P2Archer.GetY());
	cout << P2Archer.GetCharacter();
	SetXYPosition(P2Sorcerer.GetX(), P2Sorcerer.GetY());
	cout << P2Sorcerer.GetCharacter();
	cout << "\n\n\n\n";
	SetXYPosition(0, 16);
	
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);
	DTSTimer timer;
	int round = 1;
	bool P1Win = false;
	bool P2Win = false;
	Player P1Warrior(41, 7, "W", true);
	Player P2Warrior(44, 12, "w", false);
	Player P1Archer(40, 7, "A", true);
	Player P2Archer(45, 12, "a", false);
	Player P1Sorcerer(40, 8, "S", true);
	Player P2Sorcerer(45, 11, "s", false);
	vector<int> RoundOrder;
	for (int i = 1; i < 7; i++)
	{
		RoundOrder.push_back(i);
	}
	while (true)
	{
		srand((int)time(NULL));
		random_shuffle(RoundOrder.begin(), RoundOrder.end());
		Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
		for (unsigned int i = 0; i < RoundOrder.size(); i++)
		{
			string input;
			bool left = false;
			bool right = false;
			bool up = false;
			bool down = false;
			bool opposite = false;
			bool A = false;
			bool Sw = false;
			if (RoundOrder[i] == 1)
			{
				if (P1Warrior.IsDead() == false)
				{
					if (P1Warrior.CollisionCheck(P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, "l") == false)
					{
						left = false;
					}
					else
					{
						left = true;
					}
					if (P1Warrior.CollisionCheck(P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, "r") == false)
					{
						right = false;
					}
					else
					{
						right = true;
					}
					if (P1Warrior.CollisionCheck(P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, "u") == false)
					{
						up = false;
					}
					else
					{
						up = true;
					}
					if (P1Warrior.CollisionCheck(P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, "d") == false)
					{
						down = false;
					}
					else
					{
						down = true;
					}
					cout << "It's P1 Warrior's turn...\n";
					if (left == true && right == true && up == true && down == true)
					{
						cout << "There are no possible moves for this character. \n";
					}
					else
					{
						cout << "Would you like to move? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							
							cout << "Where would you like to move? ";
							if (left == false)
							{
								cout << "Left(l) ";
							}
							if (right == false)
							{
								cout << "Right(r) ";
							}
							if (up == false)
							{
								cout << "Up(u) ";
							}
							if (down == false)
							{
								cout << "Down(d) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "l"&& left == false || input == "r" && right == false ||  input == "u" && up == false || input == "d" && down == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else if (input == "l")
									{
										P1Warrior.SetX(P1Warrior.GetX() - 1);

									}
									else if (input == "r")
									{
										P1Warrior.SetX(P1Warrior.GetX() + 1);

									}
									else if (input == "u")
									{
										P1Warrior.SetY(P1Warrior.GetY() - 1);

									}
									else if (input == "d")
									{
										P1Warrior.SetY(P1Warrior.GetY() + 1);

									}
									break;	
								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
					}

					if (P1Warrior.InRange(P2Warrior.GetX(), P2Warrior.GetY()) == true && P2Warrior.IsDead() == false)
					{
						opposite = true;
					}
					else
					{
						opposite = false;
					}
					if (P1Warrior.InRange(P2Archer.GetX(), P2Archer.GetY()) == true && P2Archer.IsDead() == false)
					{
						A = true;
					}
					else
					{
						A = false;
					}
					if (P1Warrior.InRange(P2Sorcerer.GetX(), P2Sorcerer.GetY()) == true && P2Sorcerer.IsDead() == false)
					{
						Sw = true;
					}
					else
					{
						Sw = false;
					}
					if (opposite == false && A == false && Sw == false)
					{
						
						cout << "Your character is too far away to attack anyone \n";
					}
					else
					{
						
						cout << "Would you like to attack? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							
							"Who would you like to attack? Available attacks: ";
							if (opposite == true && P2Warrior.IsDead() == false)
							{
								cout << "Warrior(w) ";
							}
							if (A == true && P2Archer.IsDead() == false)
							{
								cout << "Archer(a) ";  
							}
							if (Sw == true && P2Sorcerer.IsDead() == false)
							{
								cout << "Sorcerer(s) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "w" && opposite == true && P2Warrior.IsDead() == false || input == "a" && A == true && P2Archer.IsDead() == false || input == "s" && Sw == true && P2Sorcerer.IsDead() == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else
									{
										if (input == "w")
										{
											P2Warrior.ReduceHealth(P1Warrior.Attack());
											if (P2Warrior.GetHealth() < 1)
											{
												P2Warrior.Killed(true);
												P2Warrior.SetCharacter("d");
											}
											break;
										}
										else if (input == "a")
										{	
											P2Archer.ReduceHealth(P1Warrior.Attack());
											if (P2Archer.GetHealth() < 1)
											{
												P2Archer.Killed(true);
												P2Archer.SetCharacter("d");
											}
											break;
										}
										else if (input == "s")
										{
											P2Sorcerer.ReduceHealth(P1Warrior.Attack());
											if (P2Sorcerer.GetHealth() < 1)
											{
												P2Sorcerer.Killed(true);
												P2Sorcerer.SetCharacter("d");
											}
											break;
										}
									}
									
								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
							Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						}
					}
					
					cout << " End of turn... \n";
					timer.reset();
					while (timer.getElapsedTime() < 3000)
					{

					}
					if (P1Warrior.IsDead() == true && P1Sorcerer.IsDead() == true && P1Archer.IsDead() == true)
					{
						P2Win = true;
						i = 10;
					}
					else if (P2Warrior.IsDead() == true && P2Sorcerer.IsDead() == true && P2Archer.IsDead() == true)
					{
						P1Win = true;
						i = 10;
					}
				}
				Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
			}
			else if (RoundOrder[i] == 2)
			{
				if (P1Sorcerer.IsDead() == false)
				{
					if (P1Sorcerer.CollisionCheck(P2Warrior, P1Archer, P2Archer, P1Warrior, P2Sorcerer, "l") == false)
					{
						left = false;
					}
					else
					{
						left = true;
					}
					if (P1Sorcerer.CollisionCheck(P2Warrior, P1Archer, P2Archer, P1Warrior, P2Sorcerer, "r") == false)
					{
						right = false;
					}
					else
					{
						right = true;
					}
					if (P1Sorcerer.CollisionCheck(P2Warrior, P1Archer, P2Archer, P1Warrior, P2Sorcerer, "u") == false)
					{
						up = false;
					}
					else
					{
						up = true;
					}
					if (P1Sorcerer.CollisionCheck(P2Warrior, P1Archer, P2Archer, P1Warrior, P2Sorcerer, "d") == false)
					{
						down = false;
					}
					else
					{
						down = true;
					}					
					cout << "It's P1 Sorcerer's turn...\n";
					if (left == true && right == true && up == true && down == true)
					{
						cout << "There are no possible moves for this character. \n";
					}
					else
					{
						cout << "Would you like to move? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							cout << "Where would you like to move? ";
							if (left == false)
							{
								cout << "Left(l) ";
							}
							if (right == false)
							{
								cout << "Right(r) ";
							}
							if (up == false)
							{
								cout << "Up(u) ";
							}
							if (down == false)
							{
								cout << "Down(d) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "l"&& left == false || input == "r" && right == false || input == "u" && up == false || input == "d" && down == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else if (input == "l")
									{
										P1Sorcerer.SetX(P1Sorcerer.GetX() - 1);

									}
									else if (input == "r")
									{
										P1Sorcerer.SetX(P1Sorcerer.GetX() + 1);

									}
									else if (input == "u")
									{
										P1Sorcerer.SetY(P1Sorcerer.GetY() - 1);

									}
									else if (input == "d")
									{
										P1Sorcerer.SetY(P1Sorcerer.GetY() + 1);

									}
									break;
								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
					}

					
					if (P1Sorcerer.InRange(P2Warrior.GetX(), P2Warrior.GetY()) == true && P2Warrior.IsDead() == false)
					{
						opposite = true;
					}
					else
					{
						opposite = false;
					}
					if (P1Sorcerer.InRange(P2Archer.GetX(), P2Archer.GetY()) == true && P2Archer.IsDead() == false)
					{
						A = true;
					}
					else
					{
						A = false;
					}
					if (P1Sorcerer.InRange(P2Sorcerer.GetX(), P2Sorcerer.GetY()) == true && P2Sorcerer.IsDead() == false)
					{
						Sw = true;
					}
					else
					{
						Sw = false;
					}
					if (opposite == false && A == false && Sw == false)
					{
						
						cout << "Your character is too far away to attack anyone \n";
					}
					else
					{
					
						cout << "Would you like to attack? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							
							"Who would you like to attack? Available attacks: ";
							if (opposite == true && P2Warrior.IsDead() == false)
							{
								cout << "Warrior(w) ";
							}
							if (A == true && P2Archer.IsDead() == false)
							{
								cout << "Archer(a) ";
							}
							if (Sw == true && P2Sorcerer.IsDead() == false)
							{
								cout << "Sorcerer(s) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "w" && opposite == true && P2Warrior.IsDead() == false || input == "a" && A == true && P2Archer.IsDead() == false || input == "s" && Sw == true && P2Sorcerer.IsDead() == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else
									{
										if (input == "w")
										{
											P2Warrior.ReduceHealth(P1Sorcerer.Attack());
											if (P2Warrior.GetHealth() < 1)
											{
												P2Warrior.Killed(true);
												P2Warrior.SetCharacter("d");
											}
											break;
										}
										else if (input == "a")
										{
											P2Archer.ReduceHealth(P1Sorcerer.Attack());
											if (P2Archer.GetHealth() < 1)
											{
												P2Archer.Killed(true);
												P2Archer.SetCharacter("d");
											}
											break;
										}
										else if (input == "s")
										{
											P2Sorcerer.ReduceHealth(P1Sorcerer.Attack());
											if (P2Sorcerer.GetHealth() < 1)
											{
												P2Sorcerer.Killed(true);
												P2Sorcerer.SetCharacter("d");
											}
											break;
										}
									}

								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
							Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						}
					}
					cout << " End of turn... \n";
					timer.reset();
					while (timer.getElapsedTime() < 3000)
					{

					}
					if (P1Warrior.IsDead() == true && P1Sorcerer.IsDead() == true && P1Archer.IsDead() == true)
					{
						P2Win = true;
						i = 10;
					}
					else if (P2Warrior.IsDead() == true && P2Sorcerer.IsDead() == true && P2Archer.IsDead() == true)
					{
						P1Win = true;
						i = 10;
					}
				}
				Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
			}
			else if (RoundOrder[i] == 3)
			{
				if (P1Archer.IsDead() == false)
				{
					if (P1Archer.CollisionCheck(P2Warrior, P1Warrior, P2Archer, P1Sorcerer, P2Sorcerer, "l") == false)
					{
						left = false;
					}
					else
					{
						left = true;
					}
					if (P1Archer.CollisionCheck(P2Warrior, P1Warrior, P2Archer, P1Sorcerer, P2Sorcerer, "r") == false)
					{
						right = false;
					}
					else
					{
						right = true;
					}
					if (P1Archer.CollisionCheck(P2Warrior, P1Warrior, P2Archer, P1Sorcerer, P2Sorcerer, "u") == false)
					{
						up = false;
					}
					else
					{
						up = true;
					}
					if (P1Archer.CollisionCheck(P2Warrior, P1Warrior, P2Archer, P1Sorcerer, P2Sorcerer, "d") == false)
					{
						down = false;
					}
					else
					{
						down = true;
					}
					cout << "It's P1 Archer's turn...\n";
					if (left == true && right == true && up == true && down == true)
					{
						cout << "There are no possible moves for this character. \n";
					}
					else
					{
						cout << "Would you like to move? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							cout << "Where would you like to move? ";
							if (left == false)
							{
								cout << "Left(l) ";
							}
							if (right == false)
							{
								cout << "Right(r) ";
							}
							if (up == false)
							{
								cout << "Up(u) ";
							}
							if (down == false)
							{
								cout << "Down(d) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "l"&& left == false || input == "r" && right == false || input == "u" && up == false || input == "d" && down == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else if (input == "l")
									{
										P1Archer.SetX(P1Archer.GetX() - 1);

									}
									else if (input == "r")
									{
										P1Archer.SetX(P1Archer.GetX() + 1);

									}
									else if (input == "u")
									{
										P1Archer.SetY(P1Archer.GetY() - 1);

									}
									else if (input == "d")
									{
										P1Archer.SetY(P1Archer.GetY() + 1);

									}
									break;
								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
					}

					
					if (P1Archer.InRange(P2Warrior.GetX(), P2Warrior.GetY()) == true && P2Warrior.IsDead() == false)
					{
						opposite = true;
					}
					else
					{
						opposite = false;
					}
					if (P1Archer.InRange(P2Archer.GetX(), P2Archer.GetY()) == true && P2Archer.IsDead() == false)
					{
						A = true;
					}
					else
					{
						A = false;
					}
					if (P1Archer.InRange(P2Sorcerer.GetX(), P2Sorcerer.GetY()) == true && P2Sorcerer.IsDead() == false)
					{
						Sw = true;
					}
					else
					{
						Sw = false;
					}
					if (opposite == false && A == false && Sw == false)
					{
						cout << "Your character is too far away to attack anyone \n";
					}
					else
					{
						cout << "Would you like to attack? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							"Who would you like to attack? Available attacks: ";
							if (opposite == true && P2Warrior.IsDead() == false)
							{
								cout << "Warrior(w) ";
							}
							if (A == true && P2Archer.IsDead() == false)
							{
								cout << "Archer(a) ";
							}
							if (Sw == true && P2Sorcerer.IsDead() == false)
							{
								cout << "Sorcerer(s) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "w" && opposite == true && P2Warrior.IsDead() == false || input == "a" && A == true && P2Archer.IsDead() == false || input == "s" && Sw == true && P2Sorcerer.IsDead() == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else
									{
										if (input == "w")
										{
											P2Warrior.ReduceHealth(P1Archer.Attack());
											if (P2Warrior.GetHealth() < 1)
											{
												P2Warrior.Killed(true);
												P2Warrior.SetCharacter("d");
											}
											break;
										}
										else if (input == "a")
										{
											P2Archer.ReduceHealth(P1Archer.Attack());
											if (P2Archer.GetHealth() < 1)
											{
												P2Archer.Killed(true);
												P2Archer.SetCharacter("d");
											}
											break;
										}
										else if (input == "s")
										{
											P2Sorcerer.ReduceHealth(P1Archer.Attack());
											if (P2Sorcerer.GetHealth() < 1)
											{
												P2Sorcerer.Killed(true);
												P2Sorcerer.SetCharacter("d");
											}
											break;
										}
									}

								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
							Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						}
					}

					cout << " End of turn... \n";
					timer.reset();
					while (timer.getElapsedTime() < 3000)
					{

					}
					if (P1Warrior.IsDead() == true && P1Sorcerer.IsDead() == true && P1Archer.IsDead() == true)
					{
						P2Win = true;
						i = 10;
					}
					else if (P2Warrior.IsDead() == true && P2Sorcerer.IsDead() == true && P2Archer.IsDead() == true)
					{
						P1Win = true;
						i = 10;
					}
				}
				Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
			}
			else if (RoundOrder[i] == 4)
			{
				if (P2Warrior.IsDead() == false)
				{
					if (P2Warrior.CollisionCheck(P1Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, "l") == false)
					{
						left = false;
					}
					else
					{
						left = true;
					}
					if (P2Warrior.CollisionCheck(P1Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, "r") == false)
					{
						right = false;
					}
					else
					{
						right = true;
					}
					if (P2Warrior.CollisionCheck(P1Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, "u") == false)
					{
						up = false;
					}
					else
					{
						up = true;
					}
					if (P2Warrior.CollisionCheck(P1Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, "d") == false)
					{
						down = false;
					}
					else
					{
						down = true;
					}
					cout << "It's P2 Warrior's turn...\n";
					if (left == true && right == true && up == true && down == true)
					{
						cout << "There are no possible moves for this character. \n";
					}
					else
					{
						cout << "Would you like to move? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							cout << "Where would you like to move? ";
							if (left == false)
							{
								cout << "Left(l) ";
							}
							if (right == false)
							{
								cout << "Right(r) ";
							}
							if (up == false)
							{
								cout << "Up(u) ";
							}
							if (down == false)
							{
								cout << "Down(d) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "l"&& left == false || input == "r" && right == false || input == "u" && up == false || input == "d" && down == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else if (input == "l")
									{
										P2Warrior.SetX(P2Warrior.GetX() - 1);

									}
									else if (input == "r")
									{
										P2Warrior.SetX(P2Warrior.GetX() + 1);

									}
									else if (input == "u")
									{
										P2Warrior.SetY(P2Warrior.GetY() - 1);

									}
									else if (input == "d")
									{
										P2Warrior.SetY(P2Warrior.GetY() + 1);

									}
									break;
								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
					}

					
					if (P2Warrior.InRange(P1Warrior.GetX(), P1Warrior.GetY()) == true && P1Warrior.IsDead() == false)
					{
						opposite = true;
					}
					else
					{
						opposite = false;
					}
					if (P2Warrior.InRange(P1Archer.GetX(), P1Archer.GetY()) == true && P1Archer.IsDead() == false)
					{
						A = true;
					}
					else
					{
						A = false;
					}
					if (P2Warrior.InRange(P1Sorcerer.GetX(), P1Sorcerer.GetY()) == true && P1Sorcerer.IsDead() == false)
					{
						Sw = true;
					}
					else
					{
						Sw = false;
					}
					if (opposite == false && A == false && Sw == false)
					{
						cout << "Your character is too far away to attack anyone \n";
					}
					else
					{
						cout << "Would you like to attack? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							"Who would you like to attack? Available attacks: ";
							if (opposite == true && P1Warrior.IsDead() == false)
							{
								cout << "Warrior(w) ";
							}
							if (A == true && P1Archer.IsDead() == false)
							{
								cout << "Archer(a) ";
							}
							if (Sw == true && P1Sorcerer.IsDead() == false)
							{
								cout << "Sorcerer(s) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "w" && opposite == true && P1Warrior.IsDead() == false || input == "a" && A == true && P1Archer.IsDead() == false || input == "s" && Sw == true && P1Sorcerer.IsDead() == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else
									{
										if (input == "w")
										{
											P1Warrior.ReduceHealth(P2Warrior.Attack());
											if (P1Warrior.GetHealth() < 1)
											{
												P1Warrior.Killed(true);
												P1Warrior.SetCharacter("D");
											}
											break;
										}
										else if (input == "a")
										{
											P1Archer.ReduceHealth(P2Warrior.Attack());
											if (P1Archer.GetHealth() < 1)
											{
												P1Archer.Killed(true);
												P1Archer.SetCharacter("D");
											}
											break;
										}
										else if (input == "s")
										{
											P1Sorcerer.ReduceHealth(P2Warrior.Attack());
											if (P1Sorcerer.GetHealth() < 1)
											{
												P1Sorcerer.Killed(true);
												P1Sorcerer.SetCharacter("D");
											}
											break;
										}
									}

								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
							Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						}
					}

					cout << " End of turn... \n";
					timer.reset();
					while (timer.getElapsedTime() < 3000)
					{

					}
					if (P1Warrior.IsDead() == true && P1Sorcerer.IsDead() == true && P1Archer.IsDead() == true)
					{
						P2Win = true;
						i = 10;
					}
					else if (P2Warrior.IsDead() == true && P2Sorcerer.IsDead() == true && P2Archer.IsDead() == true)
					{
						P1Win = true;
						i = 10;
					}
				}
				Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
			}
			else if (RoundOrder[i] == 5)
			{
				if (P2Sorcerer.IsDead() == false)
				{
					if (P2Sorcerer.CollisionCheck(P1Warrior, P1Archer, P2Archer, P1Sorcerer, P2Warrior, "l") == false)
					{
						left = false;
					}
					else
					{
						left = true;
					}
					if (P2Sorcerer.CollisionCheck(P1Warrior, P1Archer, P2Archer, P1Sorcerer, P2Warrior, "r") == false)
					{
						right = false;
					}
					else
					{
						right = true;
					}
					if (P2Sorcerer.CollisionCheck(P1Warrior, P1Archer, P2Archer, P1Sorcerer, P2Warrior, "u") == false)
					{
						up = false;
					}
					else
					{
						up = true;
					}
					if (P2Sorcerer.CollisionCheck(P1Warrior, P1Archer, P2Archer, P1Sorcerer, P2Warrior, "d") == false)
					{
						down = false;
					}
					else
					{
						down = true;
					}
					cout << "It's P2 Sorcerer's turn...\n";
					if (left == true && right == true && up == true && down == true)
					{
						cout << "There are no possible moves for this character. \n";
					}
					else
					{
						cout << "Would you like to move? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							cout << "Where would you like to move? ";
							if (left == false)
							{
								cout << "Left(l) ";
							}
							if (right == false)
							{
								cout << "Right(r) ";
							}
							if (up == false)
							{
								cout << "Up(u) ";
							}
							if (down == false)
							{
								cout << "Down(d) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "l"&& left == false || input == "r" && right == false || input == "u" && up == false || input == "d" && down == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else if (input == "l")
									{
										P2Sorcerer.SetX(P2Sorcerer.GetX() - 1);

									}
									else if (input == "r")
									{
										P2Sorcerer.SetX(P2Sorcerer.GetX() + 1);

									}
									else if (input == "u")
									{
										P2Sorcerer.SetY(P2Sorcerer.GetY() - 1);

									}
									else if (input == "d")
									{
										P2Sorcerer.SetY(P2Sorcerer.GetY() + 1);

									}
									break;
								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
					}

					if (P2Sorcerer.InRange(P1Warrior.GetX(), P1Warrior.GetY()) == true && P1Warrior.IsDead() == false)
					{
						opposite = true;
					}
					else
					{
						opposite = false;
					}
					if (P2Sorcerer.InRange(P1Archer.GetX(), P1Archer.GetY()) == true && P1Archer.IsDead() == false)
					{
						A = true;
					}
					else
					{
						A = false;
					}
					if (P2Sorcerer.InRange(P1Sorcerer.GetX(), P1Sorcerer.GetY()) == true && P1Sorcerer.IsDead() == false)
					{
						Sw = true;
					}
					else
					{
						Sw = false;
					}
					if (opposite == false && A == false && Sw == false)
					{
						cout << "Your character is too far away to attack anyone \n";
					}
					else
					{
						cout << "Would you like to attack? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							"Who would you like to attack? Available attacks: ";
							if (opposite == true && P1Warrior.IsDead() == false)
							{
								cout << "Warrior(w) ";
							}
							if (A == true && P1Archer.IsDead() == false)
							{
								cout << "Archer(a) ";
							}
							if (Sw == true && P1Sorcerer.IsDead() == false)
							{
								cout << "Sorcerer(s) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "w" && opposite == true && P1Warrior.IsDead() == false || input == "a" && A == true && P1Archer.IsDead() == false || input == "s" && Sw == true && P1Sorcerer.IsDead() == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else
									{
										if (input == "w")
										{
											P1Warrior.ReduceHealth(P2Sorcerer.Attack());
											if (P1Warrior.GetHealth() < 1)
											{
												P1Warrior.Killed(true);
												P1Warrior.SetCharacter("D");
											}
											break;
										}
										else if (input == "a")
										{
											P1Archer.ReduceHealth(P2Sorcerer.Attack());
											if (P1Archer.GetHealth() < 1)
											{
												P1Archer.Killed(true);
												P1Archer.SetCharacter("D");
											}
											break;
										}
										else if (input == "s")
										{
											P1Sorcerer.ReduceHealth(P2Sorcerer.Attack());
											if (P1Sorcerer.GetHealth() < 1)
											{
												P1Sorcerer.Killed(true);
												P1Sorcerer.SetCharacter("D");
											}
											break;
										}
									}

								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
							Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						}
					}

					cout << " End of turn... \n";
					timer.reset();
					while (timer.getElapsedTime() < 3000)
					{

					}
					if (P1Warrior.IsDead() == true && P1Sorcerer.IsDead() == true && P1Archer.IsDead() == true)
					{
						P2Win = true;
						i = 10;
					}
					else if (P2Warrior.IsDead() == true && P2Sorcerer.IsDead() == true && P2Archer.IsDead() == true)
					{
						P1Win = true;
						i = 10;
					}
				}
				Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
			}
			else if (RoundOrder[i] == 6)
			{
				if (P2Archer.IsDead() == false)
				{
					if (P2Archer.CollisionCheck(P1Warrior, P1Archer, P2Warrior, P1Sorcerer, P2Sorcerer, "l") == false)
					{
						left = false;
					}
					else
					{
						left = true;
					}
					if (P2Archer.CollisionCheck(P1Warrior, P1Archer, P2Warrior, P1Sorcerer, P2Sorcerer, "r") == false)
					{
						right = false;
					}
					else
					{
						right = true;
					}
					if (P2Archer.CollisionCheck(P1Warrior, P1Archer, P2Warrior, P1Sorcerer, P2Sorcerer, "u") == false)
					{
						up = false;
					}
					else
					{
						up = true;
					}
					if (P2Archer.CollisionCheck(P1Warrior, P1Archer, P2Warrior, P1Sorcerer, P2Sorcerer, "d") == false)
					{
						down = false;
					}
					else
					{
						down = true;
					}
					cout << "It's P2 Archer's turn...\n";
					if (left == true && right == true && up == true && down == true)
					{
						cout << "There are no possible moves for this character. \n";
					}
					else
					{
						cout << "Would you like to move? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							cout << "Where would you like to move? ";
							if (left == false)
							{
								cout << "Left(l) ";
							}
							if (right == false)
							{
								cout << "Right(r) ";
							}
							if (up == false)
							{
								cout << "Up(u) ";
							}
							if (down == false)
							{
								cout << "Down(d) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "l"&& left == false || input == "r" && right == false || input == "u" && up == false || input == "d" && down == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else if (input == "l")
									{
										P2Archer.SetX(P2Archer.GetX() - 1);

									}
									else if (input == "r")
									{
										P2Archer.SetX(P2Archer.GetX() + 1);

									}
									else if (input == "u")
									{
										P2Archer.SetY(P2Archer.GetY() - 1);

									}
									else if (input == "d")
									{
										P2Archer.SetY(P2Archer.GetY() + 1);

									}
									break;
								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
					}

					
					if (P2Archer.InRange(P1Warrior.GetX(), P1Warrior.GetY()) == true && P1Warrior.IsDead() == false)
					{
						opposite = true;
					}
					else
					{
						opposite = false;
					}
					if (P2Archer.InRange(P1Archer.GetX(), P1Archer.GetY()) == true && P1Archer.IsDead() == false)
					{
						A = true;
					}
					else
					{
						A = false;
					}
					if (P2Archer.InRange(P1Sorcerer.GetX(), P1Sorcerer.GetY()) == true && P1Sorcerer.IsDead() == false)
					{
						Sw = true;
					}
					else
					{
						Sw = false;
					}
					if (opposite == false && A == false && Sw == false)
					{
						cout << "Your character is too far away to attack anyone \n";
					}
					else
					{
						cout << "Would you like to attack? (y/n) \n";
						while (true)
						{
							cin >> input;
							if (input == "y" || input == "n")
								break;
							else
							{
								cout << "Invalid Input \n";
							}
						}
						Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						if (input == "y")
						{
							"Who would you like to attack? Available attacks: ";
							if (opposite == true && P1Warrior.IsDead() == false)
							{
								cout << "Warrior(w) ";
							}
							if (A == true && P1Archer.IsDead() == false)
							{
								cout << "Archer(a) ";
							}
							if (Sw == true && P1Sorcerer.IsDead() == false)
							{
								cout << "Sorcerer(s) ";
							}
							cout << "Cancel(c) \n";
							while (true)
							{
								cin >> input;
								if (input == "w" && opposite == true && P1Warrior.IsDead() == false || input == "a" && A == true && P1Archer.IsDead() == false || input == "s" && Sw == true && P1Sorcerer.IsDead() == false || input == "c")
								{
									if (input == "c")
									{
										break;
									}
									else
									{
										if (input == "w")
										{
											P1Warrior.ReduceHealth(P2Archer.Attack());
											if (P1Warrior.GetHealth() < 1)
											{
												P1Warrior.Killed(true);
												P1Warrior.SetCharacter("D");
											}
											break;
										}
										else if (input == "a")
										{
											P1Archer.ReduceHealth(P2Archer.Attack());
											if (P1Archer.GetHealth() < 1)
											{
												P1Archer.Killed(true);
												P1Archer.SetCharacter("D");
											}
											break;
										}
										else if (input == "s")
										{
											P1Sorcerer.ReduceHealth(P2Archer.Attack());
											if (P1Sorcerer.GetHealth() < 1)
											{
												P1Sorcerer.Killed(true);
												P1Sorcerer.SetCharacter("D");
											}
											break;
										}
									}

								}
								else
								{
									cout << "Invalid Input \n";
								}
							}
							Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
						}
					}

					cout << " End of turn... \n";
					timer.reset();
					while (timer.getElapsedTime() < 3000)
					{

					}
					if (P1Warrior.IsDead() == true && P1Sorcerer.IsDead() == true && P1Archer.IsDead() == true)
					{
						P2Win = true;
						i = 10;
					}
					else if (P2Warrior.IsDead() == true && P2Sorcerer.IsDead() == true && P2Archer.IsDead() == true)
					{
						P1Win = true;
						i = 10;
					}
				}
				Display(P1Warrior, P2Warrior, P1Archer, P2Archer, P1Sorcerer, P2Sorcerer, round, RoundOrder);
			}

		}
		
		timer.delay(100);
		round = round + 1;
		if (P1Win == true)
		{
			string answer;
			system("cls");
			cout << " \n\n\n\n\n\n \t\t\t Game Over! \n";
			cout << "\t\t\t Player 1 wins! \n";
			cout << "\t\t\t Play again? (y/n)\n";
			while (true)
			{
				cin >> answer;
				if (answer == "y" || answer == "n")
					break;
				else
					cout << "Invalid Input! \n";
			}
			if (answer == "n")
				break;
			else
			{
				P1Warrior.SetX(41); P1Warrior.SetY(7); P1Warrior.SetCharacter("W"); P1Warrior.Initialize();
				P2Warrior.SetX(44); P2Warrior.SetY(12); P2Warrior.SetCharacter("w"); P2Warrior.Initialize();
				P1Archer.SetX(40); P1Archer.SetY(7); P1Archer.SetCharacter("A"); P1Archer.Initialize();
				P2Archer.SetX(45); P2Archer.SetY(12); P2Archer.SetCharacter("a"); P2Archer.Initialize();
				P1Sorcerer.SetX(40); P1Sorcerer.SetY(8); P1Sorcerer.SetCharacter("S"); P1Sorcerer.Initialize();
				P2Sorcerer.SetX(45); P2Sorcerer.SetY(11); P2Sorcerer.SetCharacter("s"); P2Sorcerer.Initialize();
				round = 1;
				P1Win = false;
			}
		}
		else if (P2Win == true)
		{
			string answer;
			system("cls");
			cout << " \n\n\n\n\n\n \t\t\t Game Over! \n";
			cout << "\t\t\t Player 2 wins! \n";
			cout << "\t\t\t Play again? (y/n)\n";
			while (true)
			{
				cin >> answer;
				if (answer == "y" || answer == "n")
					break;
				else
					cout << "Invalid Input! \n";
			}
			if (answer == "n")
				break;
			else
			{
				P1Warrior.SetX(41); P1Warrior.SetY(7); P1Warrior.SetCharacter("W"); P1Warrior.Initialize();
				P2Warrior.SetX(44); P2Warrior.SetY(12); P2Warrior.SetCharacter("w"); P2Warrior.Initialize();
				P1Archer.SetX(40); P1Archer.SetY(7); P1Archer.SetCharacter("A"); P1Archer.Initialize();
				P2Archer.SetX(45); P2Archer.SetY(12); P2Archer.SetCharacter("a"); P2Archer.Initialize();
				P1Sorcerer.SetX(40); P1Sorcerer.SetY(8); P1Sorcerer.SetCharacter("S"); P1Sorcerer.Initialize();
				P2Sorcerer.SetX(45); P2Sorcerer.SetY(11); P2Sorcerer.SetCharacter("s"); P2Sorcerer.Initialize();
				round = 1;
				P2Win = false;
			}
		}
	}
	return 0;
}