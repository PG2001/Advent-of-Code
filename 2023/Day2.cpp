#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>

using namespace std;
int one()
{	
	fstream input;
	input.open("Day2.txt");

	string line;

	int sum = 0;

	while (!input.eof())
	{
		getline(input, line);
		
		int game = std::stoi(line.substr(5, line.find(":")));
		
		stringstream ss(line.substr(8, line.length() - 8));
		string str;

		bool good = true;

		while (std::getline(ss, str, ';'))
		{
			stringstream ss2(str);
			string str2;

			int red, green, blue;
			red = green = blue = 0;

			while (std::getline(ss2, str2, ','))
			{
				stringstream ss3(str2);

				int value;
				string color;

				ss3 >> value >> color;

				if (color.compare("red") == 0)
					red = value;
				if (color.compare("blue") == 0)
					blue = value;
				if (color.compare("green") == 0)
					green = value;					
			}

			if (red > 12 || green > 13 || blue > 14)
				good = false;
		}

		if (good)
			sum += game;

	}

	return sum;
}


int two()
{
	fstream input;
	input.open("Day2.txt");

	string line;

	int sum = 0;

	while (!input.eof())
	{
		getline(input, line);

		int game = std::stoi(line.substr(5, line.find(":")));

		stringstream ss(line.substr(8, line.length() - 8));
		string str;

		bool good = true;

		int minr, ming, minb;
		minr = ming = minb = 0;

		while (std::getline(ss, str, ';'))
		{
			stringstream ss2(str);
			string str2;

			int red, green, blue;
			red = green = blue = 0;

			while (std::getline(ss2, str2, ','))
			{
				stringstream ss3(str2);

				int value;
				string color;

				ss3 >> value >> color;

				if (color.compare("red") == 0)
					red = value;
				if (color.compare("blue") == 0)
					blue = value;
				if (color.compare("green") == 0)
					green = value;
			}

			if (red > minr)
				minr = red;
			if (green > ming)
				ming = green;
			if (blue > minb)
				minb = blue;
		}

			sum += minr * ming * minb;

	}

	return sum;
}

int main()
{
	cout << one();
	cout << "\n";
	cout << two();

	return 0;
}