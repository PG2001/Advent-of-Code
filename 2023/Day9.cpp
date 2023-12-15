#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int one()
{
    fstream input;
    input.open("Day9.txt");

    int sum = 0;
    vector<int> numbers;

    string line;

    while (!input.eof())
    {
        getline(input, line);
        stringstream ss(line);

        while (!ss.eof())
        {
            int tmp;
            ss >> tmp;
            numbers.push_back(tmp);
        }

        vector<int> tmp_row, curr_row = numbers;

        vector<int> last;
        bool allZeros = false;

        last.push_back(numbers.back());
        while (!allZeros)
        {
            allZeros = true;
            for (int i = 1; i < curr_row.size(); i++)
            {
                int tmp = curr_row[i] - curr_row[i - 1];
                if (tmp != 0)
                    allZeros = false;

                tmp_row.push_back(tmp);
            }
            last.push_back(tmp_row.back());

            curr_row.clear();
            curr_row = tmp_row;
            tmp_row.clear();
        }

        int est = last.back();
        for (int i = last.size() - 2; i >= 0; i--)
        {
            est = last[i] + est;
        }

        sum += est;
        numbers.clear();

    }

    return sum;
}


int two()
{
    fstream input;
    input.open("Day9.txt");

    int sum = 0;
    vector<int> numbers;

    string line;

    while (!input.eof())
    {
        getline(input, line);
        stringstream ss(line);

        while (!ss.eof())
        {
            int tmp;
            ss >> tmp;
            numbers.push_back(tmp);
        }

        vector<int> tmp_row, curr_row = numbers;

        vector<int> first;
        bool allZeros = false;

        first.push_back(numbers[0]);
        while (!allZeros)
        {
            allZeros = true;
            for (int i = 1; i < curr_row.size(); i++)
            {
                int tmp = curr_row[i] - curr_row[i - 1];
                if (tmp != 0)
                    allZeros = false;

                tmp_row.push_back(tmp);
            }
            first.push_back(tmp_row[0]);

            curr_row.clear();
            curr_row = tmp_row;
            tmp_row.clear();
        }

        int est = first.back();
        for (int i = first.size() - 2; i >= 0; i--)
        {
            est = first[i] - est;
        }

        sum += est;
        numbers.clear();

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