#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <vector>
#include <map>
#include <tuple>

using namespace std;
int one()
{
    fstream input;
    input.open("Day8.txt");

    string line, curLoc = "AAA";
    int count = 0;
    vector<char> directions;
    map<string, pair<string, string>> dict;

    getline(input, line);

    for (int i = 0; i < line.length(); i++)
    {
        directions.push_back(line[i]);
    }

    getline(input, line);

    while (!input.eof())
    {
        getline(input, line);
        dict.insert(make_pair(line.substr(0, 3), make_pair(line.substr(7, 3), line.substr(12, 3))));
    }

    int dirCnt = 0;

    while (curLoc.compare("ZZZ") != 0)
    {
        if (directions[dirCnt] == 'L')
        {
            curLoc = dict.find(curLoc)->second.first;
        }
        else {
            curLoc = dict.find(curLoc)->second.second;
        }

        dirCnt = (dirCnt + 1) % directions.size();

        count++;
    }

    return count;
}

long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long lcm(vector<int> arr)
{
    long long ans = arr[0];

    for (int i = 1; i < arr.size(); i++)
        ans = (((arr[i] * ans)) / (gcd(arr[i], ans)));

    return ans;
}

long long two()
{
    fstream input;
    input.open("Day8.txt");

    string line;
    vector<string> curLocArray;
    vector<int> count;
    vector<char> directions;
    map<string, pair<string, string>> dict;

    getline(input, line);

    for (int i = 0; i < line.length(); i++)
    {
        directions.push_back(line[i]);
    }

    getline(input, line);

    while (!input.eof())
    {
        getline(input, line);
        string key = line.substr(0, 3);
        dict.insert(make_pair(key, make_pair(line.substr(7, 3), line.substr(12, 3))));

        if (key[2] == 'A')
            curLocArray.push_back(key);
    }

    int dirCnt = 0;

    for (int i = 0; i < curLocArray.size(); i++)
    {
        count.push_back(0);
        string curLoc = curLocArray[i];

        while (curLoc[2] != 'Z')
        {
            if (directions[dirCnt] == 'L')
            {
                curLoc = dict.find(curLoc)->second.first;
            }
            else {
                curLoc = dict.find(curLoc)->second.second;
            }

            dirCnt = (dirCnt + 1) % directions.size();

            count[i]++;
        }
    }

    return lcm(count);
}

int main()
{
    cout << one();
    cout << "\n";
    cout << two();

    return 0;
}