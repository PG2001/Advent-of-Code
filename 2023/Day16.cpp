#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

long long count(vector<vector<char>> m)
{
    long long sum = 0;

    for (int c = 0; c < m.size(); c++)
    {
        for (int r = 0; r < m[0].size(); r++)
        {
            if (m[c][r] == '*')
                sum += 1;
        }
    }
    return sum;
}

void shootBeam(
    std::vector<std::vector<char>>& energy,
    std::vector<std::vector<char>>& map,
    int row, int col, char dir)
{

    queue<tuple<int, int, char>> q;
    set<tuple<int, int, char>> s;
    energy = map;
    q.push(make_tuple(row, col, dir));
    s.insert(make_tuple(row, col, dir));

    while (!q.empty())
    {
        auto tmp = q.front();
        q.pop();
        int r = get<0>(tmp);
        int c = get<1>(tmp);
        char dir = get<2>(tmp);

        switch (dir)
        {
        case 'u':
            for (int rr = r; rr >= 0; rr--)
            {
                if (map[rr][c] == '\\')
                {
                    if (s.find(make_tuple(rr, c - 1, 'l')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(rr, c - 1, 'l'));

                    energy[rr][c] = '*';
                    q.push(make_tuple(rr, c - 1, 'l'));
                    break;
                }
                if (map[rr][c] == '/')
                {
                    if (s.find(make_tuple(rr, c + 1, 'r')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(rr, c + 1, 'r'));
                    energy[rr][c] = '*';
                    q.push(make_tuple(rr, c + 1, 'r'));
                    break;
                }
                if (map[rr][c] == '-')
                {
                    energy[rr][c] = '*';
                    if (s.find(make_tuple(rr, c - 1, 'l')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(rr, c - 1, 'l'));
                    q.push(make_tuple(rr, c + 1, 'r'));
                    q.push(make_tuple(rr, c - 1, 'l'));
                    break;
                }
                energy[rr][c] = '*';
            }
            break;
        case 'd':
            for (int rr = r; rr < map.size(); rr++)
            {
                if (map[rr][c] == '\\')
                {
                    if (s.find(make_tuple(rr, c + 1, 'r')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(rr, c + 1, 'r'));
                    energy[rr][c] = '*';
                    q.push(make_tuple(rr, c + 1, 'r'));
                    break;
                }
                if (map[rr][c] == '/')
                {
                    if (s.find(make_tuple(rr, c - 1, 'l')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(rr, c - 1, 'l'));
                    energy[rr][c] = '*';
                    q.push(make_tuple(rr, c - 1, 'l'));
                    break;
                }
                if (map[rr][c] == '-')
                {
                    if (s.find(make_tuple(rr, c + 1, 'r')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(rr, c + 1, 'r'));
                    energy[rr][c] = '*';
                    q.push(make_tuple(rr, c + 1, 'r'));
                    q.push(make_tuple(rr, c - 1, 'l'));
                    break;
                }
                energy[rr][c] = '*';
            }
            break;
        case 'l':
            for (int cc = c; cc >= 0; cc--)
            {
                if (map[r][cc] == '\\')
                {
                    if (s.find(make_tuple(r - 1, cc, 'u')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(r - 1, cc, 'u'));

                    energy[r][cc] = '*';
                    q.push(make_tuple(r - 1, cc, 'u'));
                    break;
                }
                if (map[r][cc] == '/')
                {
                    if (s.find(make_tuple(r + 1, cc, 'd')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(r + 1, cc, 'd'));
                    energy[r][cc] = '*';
                    q.push(make_tuple(r + 1, cc, 'd'));
                    break;
                }
                if (map[r][cc] == '|')
                {
                    if (s.find(make_tuple(r + 1, cc, 'd')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(r + 1, cc, 'd'));
                    energy[r][cc] = '*';
                    q.push(make_tuple(r - 1, cc, 'u'));
                    q.push(make_tuple(r + 1, cc, 'd'));
                    break;
                }
                energy[r][cc] = '*';
            }
            break;
        default:
            for (int cc = c; cc < map[r].size(); cc++)
            {
                if (map[r][cc] == '\\')
                {
                    if (s.find(make_tuple(r + 1, cc, 'd')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(r + 1, cc, 'd'));
                    energy[r][cc] = '*';
                    q.push(make_tuple(r + 1, cc, 'd'));
                    break;
                }
                if (map[r][cc] == '/')
                {
                    if (s.find(make_tuple(r - 1, cc, 'u')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(r - 1, cc, 'u'));
                    energy[r][cc] = '*';
                    q.push(make_tuple(r - 1, cc, 'u'));
                    break;
                }
                if (map[r][cc] == '|')
                {
                    if (s.find(make_tuple(r + 1, cc, 'd')) != s.end())
                        break;
                    else
                        s.insert(make_tuple(r + 1, cc, 'd'));
                    energy[r][cc] = '*';
                    q.push(make_tuple(r - 1, cc, 'u'));
                    q.push(make_tuple(r + 1, cc, 'd'));
                    break;
                }
                energy[r][cc] = '*';
            }
        }
    }
}

long long one()
{
    fstream input;
    input.open("Day16.txt");

    long long sum = 0;

    string line;
    vector<vector<char>> map;
    vector<vector<char>> energy;

    while (getline(input, line))
    {
        vector <char> tmp;
        for (int i = 0; i < line.length(); i++)
        {
            tmp.push_back(line[i]);
        }
        map.push_back(tmp);
    }

    shootBeam(energy, map, 0, 0, 'r');

    sum = count(energy);

    return sum;
}

long long two()
{
    fstream input;
    input.open("Day16.txt");

    long long sum = 0;

    string line;
    vector<vector<char>> map;
    vector<vector<char>> energy;
    queue<tuple<int, int, char>> q;
    set<tuple<int, int, char>> s;

    while (getline(input, line))
    {
        vector <char> tmp;
        for (int i = 0; i < line.length(); i++)
        {
            tmp.push_back(line[i]);
        }
        map.push_back(tmp);
    }


    for (int i = 0; i < map.size();i++)
    {
        shootBeam(energy, map, i, 0, 'r');

        int tmp = count(energy);
        if (tmp > sum)
            sum = tmp;

        shootBeam(energy, map, i, map[0].size() - 1, 'l');
        tmp = count(energy);
        if (tmp > sum)
            sum = tmp;
    }

    for (int i = 0; i < map[0].size(); i++)
    {
        shootBeam(energy, map, 0, i, 'd');

        int tmp = count(energy);
        if (tmp > sum)
            sum = tmp;

        shootBeam(energy, map, map.size() - 1, i, 'u');
        tmp = count(energy);
        if (tmp > sum)
            sum = tmp;
    }

    return sum;
}


int main()
{
    //cout << one();
    cout << "\n";
    cout << two();

    return 0;
}