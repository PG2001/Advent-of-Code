#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

long long HASH(string in)
{
    long long sum = 0;
    for (int i = 0; i < in.length(); i++)
    {
        sum += in[i];
        sum *= 17;
        sum = sum % 256;
    }

    return sum;
}

long long one()
{
    fstream input;
    input.open("Day15.txt");

    long long sum = 0;

    string line;
    vector<vector<char>> map;

    while (getline(input, line, ','))
    {
        sum += HASH(line);
    }

    return sum;
}

bool find(vector<tuple<string, int>>& b, string key, int& out)
{
    for (int i = 0; i < b.size(); i++)
    {
        if (key.compare(get<0>(b[i])) == 0)
        {
            out = i;
            return true;
        }
    }
    return false;
}

long long two()
{
    fstream input;
    input.open("Day15.txt");

    vector<vector<tuple<string, int>>> boxes;
    boxes.resize(256);

    long long sum = 0;

    string line;
    vector<vector<char>> map;

    while (getline(input, line, ','))
    {
        auto del = line.find('-');
        if (del == string::npos)
            del = line.find('=');

        string key = line.substr(0, del);
        int boxNum = HASH(key);
        int index;

        if (line[del] == '=')
        {
            string tmp = line.substr(del + 1);
            if (find(boxes[boxNum], key, index))
            {
                boxes[boxNum][index] = make_tuple(key, atoi(tmp.c_str()));

                continue;
            }
            else {

                boxes[boxNum].push_back(make_tuple(key, atoi(tmp.c_str())));
            }
        }
        else {
            if (find(boxes[boxNum], key, index))
            {
                boxes[boxNum].erase(boxes[boxNum].begin() + index);
            }
        }
    }

    for (int i = 0; i < boxes.size(); i++)
    {
        for (int j = 0; j < boxes[i].size(); j++)
        {
            sum += (i + 1) * (j + 1) * get<1>(boxes[i][j]);
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