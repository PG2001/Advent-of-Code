#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

#include <chrono>

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

void moveNorth(std::vector<std::vector<char>>& map)
{
    bool stillMoving = true;

    while (stillMoving)
    {
        stillMoving = false;
        for (int r = 1; r < map.size(); r++)
        {
            for (int c = 0; c < map[0].size(); c++)
            {
                if (map[r][c] == 'O')
                {
                    int rr = r - 1;
                    while (map[rr][c] == '.')
                    {
                        map[rr][c] = map[r][c];
                        map[r][c] = '.';
                        stillMoving = true;
                        rr--;
                        if (rr < 0)
                            break;
                    }
                }
            }
        }
    }
}

void moveWest(std::vector<std::vector<char>>& map)
{
    bool stillMoving = true;

    while (stillMoving)
    {
        stillMoving = false;
        for (int r = 0; r < map.size(); r++)
        {
            for (int c = 1; c < map[0].size(); c++)
            {
                if (map[r][c] == 'O')
                {
                    int cc = c - 1;
                    while (map[r][cc] == '.')
                    {
                        map[r][cc] = map[r][c];
                        map[r][c] = '.';
                        stillMoving = true;
                        cc--;
                        if (cc < 0)
                            break;
                    }
                }
            }
        }
    }
}

void moveSouth(std::vector<std::vector<char>>& map)
{
    bool stillMoving = true;

    while (stillMoving)
    {
        stillMoving = false;
        for (int r = map.size() - 2; r >= 0; r--)
        {
            for (int c = 0; c < map[0].size(); c++)
            {
                if (map[r][c] == 'O')
                {
                    int rr = r + 1;
                    while (map[rr][c] == '.')
                    {
                        map[rr][c] = map[r][c];
                        map[r][c] = '.';
                        stillMoving = true;
                        rr++;
                        if (rr > map.size() - 1)
                            break;
                    }
                }
            }
        }
    }
}

void moveEast(std::vector<std::vector<char>>& map)
{
    bool stillMoving = true;

    while (stillMoving)
    {
        stillMoving = false;
        for (int r = 0; r < map.size(); r++)
        {
            for (int c = map[0].size() - 2; c >= 0; c--)
            {
                if (map[r][c] == 'O')
                {
                    int cc = c + 1;
                    while (map[r][cc] == '.')
                    {
                        map[r][cc] = map[r][c];
                        map[r][c] = '.';
                        stillMoving = true;
                        cc++;
                        if (cc > map[0].size() - 1)
                            break;
                    }
                }
            }
        }
    }
}

bool find(vector<vector<vector<char>>>& s, vector<vector<char>> f, int& out)
{
    for (int i = 0; i < s.size(); i++)
    {

        if (s[i] == f)
        {
            out = i;
            return true;
        }
    }
    return false;
}

long long one()
{
    fstream input;
    input.open("Day14.txt");

    long long sum = 0;

    string line;
    vector<vector<char>> map;

    while (!input.eof())
    {
        getline(input, line);
        vector<char> tmp;
        for (int i = 0; i < line.length();i++)
        {
            tmp.push_back(line[i]);
        }
        map.push_back(tmp);

    }

    moveNorth(map);

    for (int c = 0; c < map.size(); c++)
    {
        for (int r = 0; r < map[0].size(); r++)
        {
            if (map[r][c] == 'O')
            {
                sum += map.size() - r;
            }
        }
    }

    return sum;
}

long long two()
{
    fstream input;
    input.open("Day14.txt");

    long long sum = 0;

    string line;

    vector<vector<char>> map;

    vector <vector<vector<char>>> s;

    while (!input.eof())
    {
        getline(input, line);
        vector<char> tmp;
        for (int i = 0; i < line.length();i++)
        {
            tmp.push_back(line[i]);
        }
        map.push_back(tmp);
    }

    int start, end;
    for (int i = 0; i < 100000000; i++)
    {

        moveNorth(map);
        moveWest(map);
        moveSouth(map);
        moveEast(map);

        if (!find(s, map, start))
        {
            s.push_back(map);
        }
        else {
            end = i;
            break;
        }
    }

    int val = (1000000000 - (start + 1)) % (end - start);


    for (int c = 0; c < map.size(); c++)
    {
        for (int r = 0; r < map[0].size(); r++)
        {
            if (s[start + val][r][c] == 'O')
            {
                sum += map.size() - r;
            }
        }
    }

    return sum;
}

int main()
{
    cout << one();
    cout << "\n";
    auto t1 = chrono::high_resolution_clock::now();
    cout << two();
    auto t2 = chrono::high_resolution_clock::now();
    auto ms_int = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
    std::cout << '\n' << ms_int.count() << "ms\n";

    return 0;
}