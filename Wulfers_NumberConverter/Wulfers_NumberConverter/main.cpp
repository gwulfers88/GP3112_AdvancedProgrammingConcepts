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

// TODO(George): use dynamic arrays instead of static ones to be able to go over the current limit (20 digits).
// TOOD(George): make it so users can use cmd to use the converter by specifying a number to convert, what base it is and the conversion base.

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

/*
	NOTE: used to raise a number to any power like 2^32 or 16^2 etc.
	I believe this function to be depricated, since it is no longer being used
	to calculate anything where it matters.
	Should it be deleted??
*/
u32 raiseToPower(u32 base, i32 power)
{
	u32 result = base;
	
	if (power == 0)
		return 1;

	for (i32 i = 0; i < power - 1; i++)
	{
		result *= base;
	}

	return result;
}

i32 wulfers_atoi(i8* str)
{
	i32 sign = 1;
	i32 val = 0;
	i8 c;

	if (*str == '-')
	{
		sign = -1;
	}

	//decimal
	while (1)
	{
		c = *str;
		str++;
		if (c < '0' || c > '9') //non numerical
			return sign * val;

		val = val * 10 + c - '0'; //subtract '0' or 48 from any ASCII numerical value to get the actual integer value.
	}

	return val * sign;
}

i32 HexToDec(i8* numberChunk)
{
	i32 result = 0;
	i8 c;

	while (1)
	{
		c = *numberChunk;
		numberChunk++;
		if (c >= '0' && c <= '9')
			result = result * 16 + c - '0';
		else if (c >= 'a' && c <= 'f')
			result = result * 16 + c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			result = result * 16 + c - 'A' + 10;
		else
			return result;
	}
}

i32 BinToDec(i8* numberChunk)
{
	i32 result = 0;
	i8 c;

	while (1)
	{
		c = *numberChunk;
		numberChunk++;
		if (c >= '0' && c <= '1')
			result = result * 2 + c - '0';
		else
			return result;
	}
}

struct HexNumber
{
	char data[20];
	i32 size;
};

void printHexNumber(HexNumber number)
{
	for (int i = number.size - 1; i > -1; i--)
	{
		cout << number.data[i];
	}

	cout << endl;
}

string HexNumToString(HexNumber number)
{
	string result;
	for (int i = number.size - 1; i > -1; i--)
	{
		result += number.data[i];
	}
	return result;
}

HexNumber DecToBin(u32 input)
{
	HexNumber result = {};
	static char BIN[] = "01";
	while (input > 0)
	{
		result.data[result.size++] = BIN[input & 0b1];
		input >>= 1;
	}
	return result;
}

string DecToBin(i8* numChunk)
{
	// 13 = 8 + 4 + 1 = 2^3 + 2^2 + 2^0 = 1101
	i32 n = wulfers_atoi(numChunk);
	string binary = HexNumToString(DecToBin(n));
	return binary;
}

HexNumber DecToHex(u32 input)
{
	HexNumber result = {};
	static char HEX[] = "0123456789ABCDEF";
	while (input > 0)
	{
		result.data[result.size++] = HEX[(input & 0xF)];
		input >>= 4;
	}
	return result;
}

string DecToHex(i8* numChunk)
{
	i32 n = wulfers_atoi(numChunk);
	string result = HexNumToString(DecToHex(n));
	return result;
}

//NOTE: deprecated or not used anymore in file.
int findPowerOfTwo(int n)
{
	int result = 0;
	int count = 0;
	bool found = false;

	while (!found)
	{
		int temp = raiseToPower(2, count);

		if (temp < n)
		{
			result = temp;
			count++;
		}
		else
		{
			found = true;
		}
	}

	return (count > 0 ? count - 1 : 0);
}

int wulfers_strCmp(char* str1, char* str2)
{
	while (*str1)
	{
		if (*str1 < *str2)
			return -1;
		else if (*str1 > *str2)
			return 1;

		str1++;
		str2++;
	}

	return 0;
}

#define ArrayCount(Array) (sizeof(Array)/sizeof(Array[0]))
#define HEX 0x0001
#define BIN 0x0010
#define DEC 0x0100

int main(int argc, char** args)
{
	if (argc < 4)
	{
		printf("Usage: program.exe [numberToConvert] [originalNumberBase] [converionNumberBase]\n\tex: Wulfers_NumberConverter.exe 123 10 16.\n");
	}
	else
	{
		char* number = args[1];
		char* baseOne = args[2];
		char* baseTwo = args[3];

		int originalBase = 0;
		int conversionBase = 0;

		printf("Converting ");

		if (!wulfers_strCmp(baseOne, "10"))
		{
			printf("DEC (%s) to", number);
			originalBase |= DEC;
		}
		else if (!wulfers_strCmp(baseOne, "16"))
		{
			printf("HEX (%s) to", number);
			originalBase |= HEX;
		}
		else if (!wulfers_strCmp(baseOne, "2"))
		{
			printf("BIN (%s) to", number);
			originalBase |= BIN;
		}
		else
		{
			printf("(%s) is not a proper base value, use 10, 16, or 2.\n");
		}

		if (!wulfers_strCmp(baseTwo, "10"))
		{
			printf(" DEC\n");
			conversionBase |= DEC;
		}
		else if (!wulfers_strCmp(baseTwo, "16"))
		{
			printf(" HEX\n");
			conversionBase |= HEX;
		}
		else if (!wulfers_strCmp(baseTwo, "2"))
		{
			printf(" BIN\n");
			conversionBase |= BIN;
		}

		string result;

		if (originalBase & DEC && conversionBase & HEX)
		{
			result = DecToHex(number);
		}
		else if (originalBase & DEC && conversionBase & BIN)
		{
			result = DecToBin(number);
		}
		else if (originalBase & HEX && conversionBase & DEC)
		{
			char buffer[24];
			int n = HexToDec(number);
			result = itoa(n, buffer, 10);
		}
		else if (originalBase & HEX && conversionBase & BIN)
		{
			char buffer[24];
			int n = HexToDec(number);
			itoa(n, buffer, 10);
			result = DecToBin(buffer);
		}
		else if (originalBase & BIN && conversionBase & DEC)
		{
			char buffer[24];
			int n = BinToDec(number);
			result = itoa(n, buffer, 10);
		}
		else if (originalBase & BIN && conversionBase & HEX)
		{
			char buffer[24];
			int n = BinToDec(number);
			itoa(n, buffer, 10);
			result = DecToHex(buffer);
		}

		cout << "Result: " << result << endl;
	}

	//int binaryNumber = 0b00001000;
	//int hexNumber = 0x00000010;
	//int hexNum = 0x0000000F;
	//int hexN = 0x000000F0;	// Shoulb be 16^1 * 15 = 240
	//
	//cout << "Binary Number: " << binaryNumber << endl;
	//cout << "Hexidecimal Number: " << hexNumber << endl;
	//cout << "Hexidecimal Number: " << hexNum << endl;
	//cout << "Hexidecimal Number: " << hexN << endl;
	//
	printf("press enter to exit...\n");
	getchar();

	return 0;
}