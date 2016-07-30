/*
Name: George Wulfers
Email: george.wulfers@gmail.com
Week: 1
Class: Adv. Programming I.
Prof: Frank Madrid.
-----------------------------------
main.cpp

project 1: create a program that converts from dec to hex and to bin of any length.
20 should be used by the teacher (plan for that possibly more!).
*/
#include <iostream>
#include <Windows.h>

int main()
{

	for (int i = 0; i < 17; i++)
	{
		system("cls");

		if (i & 16)
			i ^= 16;

		std::cout << i << std::endl;
		Sleep(50);
	}

	return 0;
}