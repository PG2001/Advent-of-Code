#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

void print(vector<vector<char>> m)
{
    cout << "-------------------\n";
    for (int c = 0; c < m.size(); c++)
    {
        for (int r = 0; r < m[0].size(); r++)
        {
            cout << m[c][r];
        }
        cout << '\n';
    }
    cout << "-------------------\n";
}

void rotate(vector<vector<char>>& m)
{
    vector<vector<char>> output;

    for (int c = 0; c < m[0].size(); c++)
    {
        vector<char> tmp;
        for (int r = 0; r < m.size(); r++)
        {
            tmp.push_back(m[r][c]);
        }
        output.push_back(tmp);
    }

    m = output;
}

int horizontal(vector<vector<char>> m)
{
    int ret;
    for (int i = 1; i < m.size(); i++)
    {
        bool match = true;
        int j = i - 1;
        int k = i;
        while (match && (j >= 0) & (k < m.size()))
        {
            if (m[j] != m[k])
            {
                match = false;
                break;
            }
            j--;
            k++;
        }
        if (match)
            return i;
    }
    return 0;
}

bool slop(vector<char> l, vector<char> r, int& out)
{
    out = 0;

    for (int i = 0; i < l.size(); i++)
    {
        if (l[i] == r[i])
            continue;

        out++;
    }

    return (out != 0);
}

int horizontalSlop(vector<vector<char>> m, int old)
{
    int ret;
    for (int i = 1; i < m.size(); i++)
    {
        if (i == old)
            continue;

        bool match = true;
        bool oneOff = false;
        int j = i - 1;
        int k = i;
        while (match && (j >= 0) & (k < m.size()))
        {
            int numOff = 0;
            if (slop(m[j], m[k], numOff))
            {
                if (numOff > 1 || oneOff)
                {
                    match = false;
                    break;
                }
                oneOff = true;
            }
            j--;
            k++;
        }
        if (match && i != old)
            return i;
    }
    return 0;
}

int one()
{
    fstream input;
    input.open("Day13.txt");

    int sum = 0;

    string line = " ";

    vector<vector<char>> maze;

    while (!input.eof())
    {
        while (true)
        {
            getline(input, line);
            if (line.length() == 0)
                break;
            vector<char> tmp;

            for (int i = 0; i < line.length();i++)
            {
                tmp.push_back(line[i]);
            }
            maze.push_back(tmp);
            if (input.eof())
                break;
        }

        sum += horizontal(maze) * 100;
        //print(maze);
        rotate(maze);
        //print(maze);
        sum += horizontal(maze); // vertical

        maze.clear();
    }

    return sum;
}

int two()
{
    fstream input;
    input.open("Day13.txt");

    int sum = 0;

    string line = " ";

    vector<vector<char>> maze;

    while (!input.eof())
    {
        while (true)
        {
            getline(input, line);
            if (line.length() == 0)
                break;
            vector<char> tmp;

            for (int i = 0; i < line.length();i++)
            {
                tmp.push_back(line[i]);
            }
            maze.push_back(tmp);
            if (input.eof())
                break;
        }

        int h = horizontal(maze);
        sum += horizontalSlop(maze, h) * 100;
        rotate(maze);
        int v = horizontal(maze);
        sum += horizontalSlop(maze, v); // vertical

        maze.clear();
    }

    return sum;
}

int main()
{
    //cout << one();
    //cout << "\n";
    cout << two();

    return 0;
}