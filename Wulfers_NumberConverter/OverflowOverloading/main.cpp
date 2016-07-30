/*
	Name: George Wulfers
	Email: george.wulfers@gmail.com
	Week: 1
	Class: Adv. Programming I.
	Prof: Frank Madrid.
	-----------------------------------
	main.cpp
*/

#include <iostream>
#include <string>

using namespace std;

typedef char		i8;
typedef short		i16;
typedef int			i32;
typedef long long	i64;

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;

/* NOTES FROM CLASS DID NOT COMPLETE IT AS YOU WANTED IT TEACHER

#define GROUP_COUNT 10
#define GROUP_SIZE 100

class BigN
{
public:
	BigN();
	~BigN();

	void appendDigit(int);
	void printNumber();


private:
	int group[GROUP_COUNT];
	bool negative;

	void normalizew();
	void carry();	//traverses through all groups from the smallest to the highest group count if any number with in the group is greater that the group size then we carry the group[i + 1] += group[i] / size;
	void borrow();	// iterate through all the groups if the number at the group[i] < 0. if the index + 1 is equal to the group_size then it is negative else borrow group[i] --; group[i + 1] += group_size;
};
*/

#define ArrayCount(Array) (sizeof(Array)/sizeof(Array[0]))

#define MAX_CHAR	0xFF
#define MAX_SHORT	0xFFFF
#define MAX_INT32	0xFFFFFFFF
#define MAX_INT64	0xFFFFFFFFFFFFFFFF
#define MAX_UCHAR	0xFF
#define MAX_USHORT	0xFFFF
#define MAX_UINT32	0xFFFFFFFF
#define MAX_UINT64	0xFFFFFFFFFFFFFFFF

struct BigNum
{
	u16 data[20];	//big number data
	i32 digits;		//number of digits the data holds.
};

void InitBigNum(BigNum* a)
{
	a->data[0] = 0;
	a->digits = 1;
}

bool operator==(BigNum& a, BigNum& b)
{
	bool result = false;

	for (int i = 0; i < b.digits; i++)
	{
		for (int j = i; j < i + 1; j++)
		{
			if (a.data[j] != b.data[i])
				return result;
		}
	}

	result = true;
	return result;
}

// bingnum = 0 + 20
// 20 % 10 = 0
// 20 / 10 = 2
BigNum& operator+=(BigNum& a, u64 b)
{
	i32 index = 0;
	u64 temp = b;
	i32 carry = 0;

	// b = 900
	// a = 300
	//    ---- it 1
	//       0
	for (int j = 0; j < a.digits; j++)
	{
		int x = a.data[j] + temp % 10 + carry; // a[0] + b % 10 (0) = 0
		a.data[j] = x % 10; // a[0] = 0
		carry = x / 10;
		temp /= 10; // carry = 30
	}

	while (temp > 0)
	{
		a.data[a.digits] = a.data[a.digits] + temp % 10; // 30 = 0
		temp /= 10; // 3
		if (a.digits < ArrayCount(a.data))
		{
			a.digits++;
		}
	}

	while (carry > 0)
	{
		a.data[a.digits] = a.data[a.digits] + carry % 10; // 30 = 0
		a.digits++;
		carry /= 10; // 3
	}

	return a;
}

BigNum& operator+=(BigNum& a, BigNum& b)
{
	u64 temp = b.data[0];
	i32 carry = 0;

	// b = 900
	// a = 300
	//     ---- it 1
	//       0
	for (int j = 0; j < a.digits; j++)
	{
		int x = a.data[j] + b.data[j] + carry; // a[0] + b % 10 (0) = 0
		a.data[j] = x % 10; // a[0] = 0
		carry = x / 10;
		temp /= 10; // carry = 30
	}

	while (temp > 0)
	{
		a.data[a.digits] = a.data[a.digits] + temp % 10; // 30 = 0
		a.digits++;
		temp /= 10; // 3
	}

	while (carry > 0)
	{
		a.data[a.digits] = a.data[a.digits] + carry % 10; // 30 = 0
		a.digits++;
		carry /= 10; // 3
	}

	return a;
}

bool operator==(u64& a, BigNum& b)
{
	BigNum num = {};
	num += a;
	return (num == b);
}

BigNum& operator-=(BigNum& a, BigNum& b)
{
	u64 temp = b.data[0];
	i32 carry = 0;

	//8297
	//4386
	//3911

	for (int j = 0; j < a.digits; j++)
	{
		if (j + 1 != a.digits)
		{
			if (a.data[j] < b.data[j])
			{
				int n = j + 1; //check next number

				if (a.data[n] > 0)
				{
					a.data[n]--;
					n--;
				}
				else
				{
					//099
					//  5
					//----
					//  
					while (a.data[n] == 0)
					{
						n++;
					}
					//109
					a.data[n]--;
					if (a.data[n] == 0)
						a.digits--;

					while (--n > j)
					{
						a.data[n] += 10 - 1;
					}
				}

				a.data[n] += 10;
			}
		}

		int x = a.data[j] - b.data[j] + carry; // a[0] + b % 10 (0) = 0
		a.data[j] = x % 10; // a[0] = 0
		carry = x / 10;
		temp /= 10; // carry = 30
	}

	while (temp > 0)
	{
		a.data[a.digits] = a.data[a.digits] - temp % 10; // 30 = 0
		a.digits++;
		temp /= 10; // 3
	}

	while (carry > 0)
	{
		a.data[a.digits] = a.data[a.digits] - carry % 10; // 30 = 0
		a.digits++;
		carry /= 10; // 3
	}

	return a;
}

BigNum& operator*=(BigNum& a, BigNum& b)
{
	u64 temp = b.data[0];
	i32 carry = 0;
	BigNum* mult = (BigNum*)malloc(sizeof(BigNum)*b.digits);
	memset(mult, 0, sizeof(BigNum)*b.digits);
	BigNum* walker = mult;

	//a  16 -- [0][5]
	//b   2 -- [0][5]
	//- ----
	//   
	//------
	for (int i = 0; i < b.digits; i++)
	{
		for (int j = 0; j < a.digits; j++)
		{
			//25 % 10 = 5
			//25 / 10 = 2
			int x = a.data[j] * b.data[i] + carry; // a[0] + b % 10 (0) = 0
			walker->data[j + i] = x % 10; // a[0] = 0
			walker->digits++;
			carry = x / 10;
			temp /= 10; // carry = 30

			if (j == a.digits - 1)
			{
				while (carry > 0)
				{
					walker->data[walker->digits] = walker->data[walker->digits] + carry % 10; // 30 = 0
					walker->digits++;
					carry /= 10; // 3
				}
			}
		}
		BigNum* tmp = (walker + 1);
		tmp->digits = walker->digits - 1;
		walker++;
	}

	while (temp > 0)
	{
		a.data[a.digits] = a.data[a.digits] + temp % 10; // 30 = 0
		a.digits++;
		temp /= 10; // 3
	}

	while (carry > 0)
	{
		a.data[a.digits] = a.data[a.digits] + carry % 10; // 30 = 0
		a.digits++;
		carry /= 10; // 3
	}

	int i = 0;
	walker = mult;

	for (int i = 0; i < b.digits; i++)
	{
		a = *walker;
		if (i < b.digits - 1)
		{
			*walker++;
			if (walker)
				*walker += a;
		}
	}

	free(mult);

	return a;
}

void printBigNum(BigNum a)
{
	for (int i = a.digits - 1; i > -1; i--)
	{
		cout << a.data[i];
	}

	cout << endl;
}

#include <Windows.h>

#define Assert(expression){ if(!expression){ *(int*)0 = 0; } }

BigNum clearBigNum()
{
	BigNum result;
	result = {};
	result.digits++;
	return result;
}

int main()
{
	BigNum num1 = {};
	BigNum num2 = {};
	num2 = clearBigNum();
	num1 = clearBigNum();

	bool isRunning = true;

	while (isRunning)
	{
		int choice = -1;

		printf("0. Add\n1. Subtract\n2. Multiply\n3. Exit\n");

		cin >> choice;

		num2 = clearBigNum();

		switch (choice)
		{
		case 0: //ADD
		{
			int a = 0;
			
			printf("Enter a number: ");
			cin >> a;
			
			num2 += a;
			num1 += num2;

			printBigNum(num1);

		}break;
		case 1: //SUB
		{
			int a = 0;
			BigNum num2 = {};

			printf("Enter a number: ");
			cin >> a;

			num2 += a;
			num1 -= num2;

			printBigNum(num1);
		}break;
		case 2: //MULT
		{
			int a = 0;
			BigNum num2 = {};

			printf("Enter a number: ");
			cin >> a;

			num2 += a;
			num1 *= num2;

			printBigNum(num1);
		}break;
		case 3:
		{
			isRunning = false;
		}break;

		default:
			printf("Sorry cant do that\n");
		}
	}

	printf("Press enter to exit....\n");
	getchar();

	return 0;
}