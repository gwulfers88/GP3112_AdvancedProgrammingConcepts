/*
Name: George Wulfers
Email: george.wulfers@gmail.com
Week: 1
Class: Adv. Programming I.
Prof: Frank Madrid.
-----------------------------------
main.cpp

Problem 3. Keys and Doors Suppose you have a set of keys which open a set of doors.
Normally you mark a key and a door by assigning an id to the key and door and simply check
if the player owned the appropriate key but what if a single key can open multiple doors ? This
can get costly quickly.Using the concepts of masks and binary numbers, determine a much
quicker way to see if a key can open a particular door.Write a program which tests your
solution.
*/


#include <iostream>

using namespace std;

#define DOOR1 0b00001
#define DOOR2 0b00010
#define DOOR3 0b00100
#define DOOR4 0b01000
#define DOOR5 0b10000

#define DOOR_MASK_13 0b00101
#define DOOR_MASK_24 0b01010
#define DOOR_MASK_5  0b10000

int main()
{
	int Keys[3];
	Keys[0] = DOOR1 | DOOR2;
	Keys[1] = DOOR2 | DOOR4;
	Keys[2] = DOOR5;

	int Doors[5];
	Doors[0] = DOOR1;
	Doors[1] = DOOR2;
	Doors[2] = DOOR3;
	Doors[3] = DOOR4;
	Doors[4] = DOOR5;

#define ArrayCount(a) (sizeof(a)/sizeof(a[0]))

	for (int i = 0; i < ArrayCount(Keys); i++)
	{
		for (int j = 0; j < ArrayCount(Doors); j++)
		{
			if ((Keys[i] & DOOR_MASK_5) & Doors[j])
			{
				printf("Key %d opened door %d\n", i + 1, j + 1);
			}
			else if ((Keys[i] & DOOR_MASK_13) & Doors[j])
			{
				printf("Key %d opened door %d\n", i + 1, j + 1);
			}
			else if ((Keys[i] & DOOR_MASK_24) & Doors[j])
			{
				printf("Key %d opened door %d\n", i + 1, j + 1);
			}
		}
	}

	printf("Press Enter to exit..\n");
	getchar();

	return 0;
}