#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

int getNum(vector<vector<char>>& a, int r, int& c)
{
	string tmp = "";
	tmp.insert(tmp.begin(), a[r][c]);
	c++;

	while (isdigit(a[r][c]))
	{
		tmp.insert(tmp.end(), a[r][c]);
		c++;
	}

	return atoi(tmp.c_str());
}

bool isValid(vector<vector<char>>& a, int r, int c)
{
	int x;
	while (isdigit(a[r][c]))
	{
		for (int rr = r - 1; rr <= r + 1; rr++)
		{
			for (int cc = c - 1; cc <= c + 1; cc++)
			{
				if (rr >= 0 && rr < a.size() && cc >= 0 && cc < a[r].size())
				{
					if (!isdigit(a[rr][cc]) && a[rr][cc] != '.')
						return true;
				}
			}
		}
		c++;
	}

	return false;
}

int one()
{
	fstream input;
	input.open("Day3.txt");

	string line;
	vector<vector<char>> array;

	int sum = 0;

	while (!input.eof())
	{
		getline(input, line);
		vector<char> tmp;

		for (int i = 0; i < line.length(); i++)
		{
			tmp.push_back(line[i]);
		}

		array.push_back(tmp);
	}

	for (int r = 0; r < array.size(); r++)
	{
		for (int c = 0; c < array[r].size(); c++)
		{
			if (isdigit(array[r][c]))
			{
				int old_c = c;
				int num = getNum(array, r, c);
				if (isValid(array, r, old_c))
				{
					sum += num;
				}
			}
		}
	}

	return sum;
}

bool numAround(vector<vector<char>> a, int r, int c, int& result)
{
	vector<int> tmp;
	set<tuple<int, int>> ts;

	for (int rr = r - 1; rr <= r + 1; rr++)
	{
		for (int cc = c - 1; cc <= c + 1; cc++)
		{
			if (rr >= 0 && rr < a.size() && cc >= 0 && cc < a[r].size())
			{
				if (isdigit(a[rr][cc]))
				{
					int ccc = cc;
					while (ccc >= 0 && ccc < a[r].size() && isdigit(a[rr][ccc]))
					{
						ccc--;
					}
					ccc++;

					if (ts.find(make_tuple(rr, ccc)) == ts.end())
					{
						ts.insert(make_tuple(rr, ccc));
						string s;
						s.insert(s.end(), a[rr][ccc++]);
						while (ccc < a[rr].size() && isdigit(a[rr][ccc]))
						{
							s.insert(s.end(), a[rr][ccc]);
							ccc++;
						}
						tmp.push_back(atoi(s.c_str()));
					}

				}
			}
		}
	}
	if (tmp.size() == 2)
	{
		result = tmp[0] * tmp[1];
		return true;
	}
	return false;
}


int two()
{
	fstream input;
	input.open("Day3.txt");

	string line;
	vector<vector<char>> array;

	int sum = 0;

	while (!input.eof())
	{
		getline(input, line);
		vector<char> tmp;

		for (int i = 0; i < line.length(); i++)
		{
			tmp.push_back(line[i]);
		}

		array.push_back(tmp);
	}

	for (int r = 0; r < array.size(); r++)
	{
		for (int c = 0; c < array[r].size(); c++)
		{
			int result;
			if (array[r][c] == '*')
			{
				if (numAround(array, r, c, result))
				{
					sum += result;
				}
			}
		}
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