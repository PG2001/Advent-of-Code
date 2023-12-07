#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;


int one()
{
    fstream input;
    input.open("Day6.txt");

    string line, line2, tmpStr;
    char tmpChar;
    double b, c;
    double sum = 1;

    getline(input, line);
    getline(input, line2);

    stringstream ss(line);
    stringstream ss2(line2);

    ss >> tmpStr;
    ss2 >> tmpStr;

    while (!ss.eof())
    {
        ss >> b;
        ss2 >> c;
        double plus = floor((-b + sqrt(pow(b, 2) - 4.0 * -1.0 * -c)) / (2.0 * -1.0));
        double minus = ceil((-b - sqrt(pow(b, 2) - 4.0 * -1.0 * -c)) / (2.0 * -1.0));
        sum *= (minus - plus - 1);
    }

    return sum;
}


double two()
{
    fstream input;
    input.open("Day6.txt");

    string line, line2, tmpStr, tmpStr2;
    char tmpChar;
    double b, c;
    double sum = 1;

    getline(input, line);
    getline(input, line2);

    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    line2.erase(remove(line2.begin(), line2.end(), ' '), line2.end());

    stringstream ss(line);
    stringstream ss2(line2);

    getline(ss, tmpStr, ':');
    getline(ss, tmpStr, ':');
    b = (double)atoll(tmpStr.c_str());

    getline(ss2, tmpStr, ':');
    getline(ss2, tmpStr, ':');

    c = (double)atoll(tmpStr.c_str());

    double plus = floor((-b + sqrt(pow(b, 2) - 4.0 * -1.0 * -c)) / (2.0 * -1.0));
    double minus = ceil((-b - sqrt(pow(b, 2) - 4.0 * -1.0 * -c)) / (2.0 * -1.0));

    sum = (minus - plus - 1);

    return sum;
}


int main()
{
    cout << unsigned long long(one());
    cout << "\n";
    cout << unsigned long long(two());
    return 0;
}
