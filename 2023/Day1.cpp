#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>

using namespace std;
int one_day1()
{	
	fstream input;
	input.open("Day1.txt");

	string line;

	int current = 0;

	while (!input.eof())
	{
		getline(input, line);
		int f, l;

		for (int i = 0; i < line.length(); i++)
		{
			if (isdigit(line[i]))
			{
				f = (line[i] - '0') * 10;
				break;
			}			
		}
		for (int i = line.length()-1; i >=0; i--)
		{
			if (isdigit(line[i]))
			{
				l = (line[i] - '0');
				break;
			}
		}
		current += f + l;
	}

	return current;
}

bool isSpelled(string in, int i, int &out)
{
	if (in.substr(i, 3).compare("one") == 0)
	{
		out = 1;
		return true;
	}
	if (in.substr(i, 3).compare("two") == 0)
	{
		out = 2;
		return true;
	}
	if (in.substr(i, 5).compare("three") == 0)
	{
		out = 3;
		return true;
	}
	if (in.substr(i, 4).compare("four") == 0)
	{
		out = 4;
		return true;
	}
	if (in.substr(i, 4).compare("five") == 0)
	{
		out = 5;
		return true;
	}
	if (in.substr(i, 3).compare("six") == 0)
	{
		out = 6;
		return true;
	}
	if (in.substr(i, 5).compare("seven") == 0)
	{
		out = 7;
		return true;
	}
	if (in.substr(i, 5).compare("eight") == 0)
	{
		out = 8;
		return true;
	}
	if (in.substr(i, 4).compare("nine") == 0)
	{
		out = 9;
		return true;
	}
	
	return false;
}

int toInt(string in, int i)
{
	if (in.substr(i, 3).compare("one") == 0)
		return 1;
	if (in.substr(i, 3).compare("two") == 0)
		return 2;
	if (in.substr(i, 5).compare("three") == 0)
		return 3;
	if (in.substr(i, 4).compare("four") == 0)
		return 4;
	if (in.substr(i, 4).compare("five") == 0)
		return 5;
	if (in.substr(i, 3).compare("six") == 0)
		return 6;
	if (in.substr(i, 5).compare("seven") == 0)
		return 7;
	if (in.substr(i, 5).compare("eight") == 0)
		return 8;
	if (in.substr(i, 4).compare("nine") == 0)
		return 9;
}

int two_day1()
{
	fstream input;
	input.open("Day1.txt");

	string line;

	int current = 0;
	int max = 0;

	while (!input.eof())
	{
		getline(input, line);
		int f, l;

		for (int i = 0; i < line.length(); i++)
		{
			if (isdigit(line[i]))
			{
				f = (line[i] - '0') * 10;
				break;
			}
			if (isSpelled(line, i, f))
			{	
				f *= 10;
				break;
			}
		}
		for (int i = line.length() - 1; i >= 0; i--)
		{
			if (isdigit(line[i]))
			{
				l = (line[i] - '0');
				break;
			}
			if (isSpelled(line, i, l))
			{				
				break;
			}
		}
		current += f + l;
	}

	return current;
}

int main()
{
	cout << one_day1();
	cout << "\n";
	cout << two_day1();

	return 0;
}