#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

int one()
{
    fstream input;
    input.open("Day4.txt");

    string line;
    int sum = 0;

    while (!input.eof())
    {
        getline(input, line);

        stringstream ss(line);
        string tmpStr;
        int tmpInt;
        char tmpChar;
        set<int> intSet;

        ss >> tmpStr >> tmpInt >> tmpChar;

        for (int i = 0; i < 10; i++)
        {
            ss >> tmpInt;
            intSet.insert(tmpInt);
        }

        ss >> tmpChar;

        int count = 0;

        for (int i = 0; i < 25; i++)
        {
            ss >> tmpInt;
            if (intSet.find(tmpInt) != intSet.end())
            {
                count++;
            }
        }
        sum += pow(2, count - 1);
    }

    return sum;
}

int two()
{
    fstream input;
    input.open("Day4.txt");

    string line;
    int sum = 0;

    int numline = count(istreambuf_iterator<char>(input), istreambuf_iterator<char>(), '\n');
    input.clear();
    input.seekg(0, ios::beg);
    vector<int> counts(numline + 1, 1);

    while (!input.eof())
    {
        getline(input, line);

        stringstream ss(line);
        string tmpStr;
        int cardNum, tmpInt;
        char tmpChar;

        set<int> intSet;

        ss >> tmpStr >> cardNum >> tmpChar;

        for (int i = 0; i < 10; i++)
        {
            ss >> tmpInt;
            intSet.insert(tmpInt);
        }

        ss >> tmpChar;

        int c = cardNum;

        for (int i = 0; i < 25; i++)
        {
            ss >> tmpInt;
            if (intSet.find(tmpInt) != intSet.end())
            {
                counts[c] += 1 * counts[cardNum - 1];
                c++;
            }
        }
    }

    for (int i = 0; i < counts.size(); i++)
    {
        sum += counts[i];
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