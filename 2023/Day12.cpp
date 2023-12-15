#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

long long reduce(string p, vector<int> ecc)
{

    string str = ".";

    int i = 0;
    int j = p.length() - 1;

    while (p[i] == '.')
        i++;

    while (p[j] == '.')
        j--;

    for (i; i <= j; i++)
    {
        str.append(p, i, 1);

    }

    vector<long long> curr;
    vector<long long> next;


    bool noBrokenSeen = true;
    curr.push_back(1);
    for (int i = 0; i < str.length(); i++)
    {
        if ((str[i] == '.' || str[i] == '?') && noBrokenSeen)
        {
            curr.push_back(1);
        }
        else {
            curr.push_back(0);
            noBrokenSeen = false;
        }

    }

    for (int e = 0; e < ecc.size(); e++)
    {
        next.resize(str.length() + 1);
        int runSize = 0;

        for (int i = 1; i < str.length(); i++)
        {
            if (str[i] == '.')
            {
                runSize = 0;
            }
            else {
                runSize += 1;
            }


            bool canFit = runSize >= ecc[e];
            int oldIndex = i - ecc[e] > 0 ? i - ecc[e] : 0;
            bool notContigous = str[oldIndex] != '#';
            bool isNotDamaged = str[i] != '#';
            bool dmgCanFit = canFit && notContigous;

            if (isNotDamaged && dmgCanFit)
                next[i + 1] = next[i] + curr[oldIndex];
            else if (str[i] == '#' && dmgCanFit)
                next[i + 1] = curr[oldIndex];
            else if (isNotDamaged)
                next[i + 1] = next[i];
            else
                next[i + 1] = 0;
        }

        curr.clear();
        curr = next;
    }

    return curr.back();

}



long long one()
{
    fstream input;
    input.open("Day12.txt");

    long long sum = 0;

    string line;

    while (!input.eof())
    {
        getline(input, line);

        auto sLoc = line.find(" ");

        string conditions = line.substr(0, sLoc);
        string ecc = line.substr(sLoc + 1, line.length() - sLoc);

        vector<int> eccVector;

        stringstream ss(ecc);
        while (!ss.eof())
        {
            int tmp;
            char tmpChar;
            ss >> tmp >> tmpChar;
            eccVector.push_back(tmp);
        }
        sum += reduce(conditions, eccVector);
    }

    return sum;
}

long long two()
{
    fstream input;
    input.open("Day12.txt");

    long long sum = 0;

    string line;

    while (!input.eof())
    {
        getline(input, line);

        auto sLoc = line.find(" ");

        string conditions = line.substr(0, sLoc);
        string ecc = line.substr(sLoc + 1, line.length() - sLoc);

        vector<int> eccVector;


        stringstream ss(ecc);
        while (!ss.eof())
        {
            int tmp;
            char tmpChar;
            ss >> tmp >> tmpChar;
            eccVector.push_back(tmp);
        }

        string c = conditions;
        vector<int> e = eccVector;
        for (int i = 0; i < 4; i++)
        {
            c.append("?");
            c.append(conditions);
            for (int i = 0; i < eccVector.size();i++)
            {
                e.push_back(eccVector[i]);
            }
        }


        sum += reduce(c, e);

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