#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int one()
{
    fstream input;
    input.open("Day11.txt");

    int sum = 0;
    vector<vector<char>> galaxy;
    vector<int> rCoord, cCoord;

    string line;

    while (!input.eof())
    {
        getline(input, line);
        vector<char> row;

        bool empty = true;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                empty = false;
            }
            row.push_back(line[i]);
        }

        galaxy.push_back(row);

        if (empty)
        {
            galaxy.push_back(row);
        }
    }

    for (int c = 0; c < galaxy[0].size(); c++)
    {
        bool empty = true;
        for (int r = 0; r < galaxy.size(); r++)
        {
            if (galaxy[r][c] == '#')
                empty = false;
        }
        if (empty)
        {

            for (int r = 0; r < galaxy.size(); r++)
            {
                vector<char>::iterator it = (galaxy[r]).begin() + c;
                (galaxy[r]).insert(it, '.');
            }
            c++;
        }
    }

    for (int r = 0; r < galaxy.size(); r++)
    {
        for (int c = 0; c < galaxy[0].size(); c++)
        {
            if (galaxy[r][c] == '#')
            {
                rCoord.push_back(r);
                cCoord.push_back(c);
            }
        }
    }

    for (int i = 0; i < rCoord.size(); i++)
    {
        for (int j = i + 1; j < rCoord.size(); j++)
        {
            sum += abs(rCoord[j] - rCoord[i]) + abs(cCoord[j] - cCoord[i]);
        }
    }


    return sum;
}

long long two()
{
    fstream input;
    input.open("Day11.txt");

    long long sum = 0;
    vector<vector<char>> universe;
    vector<long long> rCoord, cCoord;

    vector<int> emptyRows;
    vector<int> emptyCols;

    string line;

    long long tmp = 0;

    while (!input.eof())
    {
        getline(input, line);
        vector<char> row;

        bool empty = true;

        for (int i = 0; i < line.length(); i++)
        {
            row.push_back(line[i]);
            if (line[i] == '#')
                empty = false;
        }

        if (empty)
        {
            emptyRows.push_back(tmp);
        }

        tmp++;

        universe.push_back(row);
    }

    for (int c = 0; c < universe[0].size(); c++)
    {
        bool empty = true;
        for (int r = 0; r < universe.size(); r++)
        {
            if (universe[r][c] == '#')
            {
                rCoord.push_back(r);
                cCoord.push_back(c);
                empty = false;
            }
        }
        if (empty)
            emptyCols.push_back(c);
    }

    long long  delta = 999999.0;

    for (int i = 0; i < rCoord.size(); i++)
    {
        for (int j = i + 1; j < rCoord.size(); j++)
        {
            long long ER1, ER2, EC1, EC2;
            ER1 = ER2 = EC1 = EC2 = 0;

            for (int k = 0; k < emptyRows.size();k++)
            {
                if (emptyRows[k] < rCoord[i])
                    ER1 += delta;
                if (emptyRows[k] < rCoord[j])
                    ER2 += delta;
            }
            for (int k = 0; k < emptyCols.size();k++)
            {
                if (emptyCols[k] < cCoord[i])
                    EC1 += delta;
                if (emptyCols[k] < cCoord[j])
                    EC2 += delta;
            }

            sum += abs((rCoord[j] + ER2) - (rCoord[i] + ER1)) + abs((cCoord[j] + EC2) - (cCoord[i] + EC1));
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