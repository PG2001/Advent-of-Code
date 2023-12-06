#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

#define ull double

void findSeedMap(std::vector<double>& seeds, std::vector<std::tuple<double, double, double>>& seedToSoil)
{
    for (int i = 0; i < seeds.size(); i++)
    {
        for (int j = 0; j < seedToSoil.size(); j++)
        {
            double s, d, l;
            s = get<0>(seedToSoil[j]);
            d = get<1>(seedToSoil[j]);
            l = get<2>(seedToSoil[j]);
            if (seeds[i] >= s && seeds[i] < s + l)
            {
                seeds[i] = seeds[i] - s + d;
                break;
            }
        }
    }
}

void readSDL(std::string& line, std::stringstream& ss, double& dest, double& source, double& length, std::vector<std::tuple<double, double, double>>& seedToSoil, std::fstream& input)
{
    while (isdigit(line[0]))
    {
        ss.clear();
        ss.str(line);
        ss >> dest >> source >> length;
        seedToSoil.push_back(make_tuple(source, dest, length));
        getline(input, line);
        if (input.eof())
            break;
    }
}

double one()
{
    fstream input;
    input.open("Day5.txt");

    string line;
    double sum = ULLONG_MAX;

    vector<double> seeds;

    getline(input, line);

    stringstream ss(line);

    string tmpStr;
    double tmp, source, dest, length;

    ss >> tmpStr;

    while (ss >> tmp)
    {
        seeds.push_back(tmp);
    }

    getline(input, line);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> seedToSoil;
    readSDL(line, ss, dest, source, length, seedToSoil, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> soilToFert;
    readSDL(line, ss, dest, source, length, soilToFert, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> fertToWater;
    readSDL(line, ss, dest, source, length, fertToWater, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> waterToLight;
    readSDL(line, ss, dest, source, length, waterToLight, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> lightToTemp;
    readSDL(line, ss, dest, source, length, lightToTemp, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> tempToHumid;
    readSDL(line, ss, dest, source, length, tempToHumid, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> humidToLoc;
    readSDL(line, ss, dest, source, length, humidToLoc, input);

    findSeedMap(seeds, seedToSoil);
    findSeedMap(seeds, soilToFert);
    findSeedMap(seeds, fertToWater);
    findSeedMap(seeds, waterToLight);
    findSeedMap(seeds, lightToTemp);
    findSeedMap(seeds, tempToHumid);
    findSeedMap(seeds, humidToLoc);

    for (int i = 0; i < seeds.size(); i++)
    {
        if (seeds[i] < sum)
            sum = seeds[i];
    }

    return sum;
}

void findSeedMap2(vector<tuple<double, double>>& seeds, std::vector<std::tuple<double, double, double>>& seedToSoil)
{
    for (int i = 0; i < seeds.size(); i++)
    {
        for (int j = 0; j < seedToSoil.size(); j++)
        {
            ull s, d, l, ss, ll;
            s = get<0>(seedToSoil[j]); // map source
            d = get<1>(seedToSoil[j]); // map destination
            l = get<2>(seedToSoil[j]); // map range

            ss = get<0>(seeds[i]); // seed start
            ll = get<1>(seeds[i]); // seed range
            if (ss >= s && ss + ll <= s + l)
            {
                seeds[i] = make_tuple(ss - s + d, ll);
                break;
            }
            else if (ss >= s && ss < s + l)
            {
                ull numMappedSeeds = s + l - ss;
                seeds[i] = make_tuple(ss - s + d, numMappedSeeds);
                seeds.push_back(make_tuple(s + l, ll - numMappedSeeds));
                break;
            }
            else if (ss + ll < s + l && ss + ll > s)
            {
                ull numMappedSeeds = ss + ll - s;
                seeds[i] = make_tuple(s - s + d, numMappedSeeds);
                seeds.push_back(make_tuple(ss, ll - numMappedSeeds));
                break;
            }
            else if (ss < s && ss + ll > s + l)
            {
                seeds[i] = make_tuple(s - s + d, l);
                seeds.push_back(make_tuple(ss, s - ss));
                seeds.push_back(make_tuple(s + l, ss + ll - (s + l)));
                break;
            }
        }
    }
}

double two()
{
    fstream input;
    input.open("Day5.txt");

    string line;
    double sum = ULLONG_MAX;

    vector<tuple<double, double>> seeds;

    getline(input, line);

    stringstream ss(line);

    string tmpStr;
    double tmp, source, dest, length;

    ss >> tmpStr;

    while (ss >> tmp)
    {
        int tmp2;
        ss >> tmp2;
        seeds.push_back(make_tuple(tmp, tmp2));
    }

    getline(input, line);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> seedToSoil;
    readSDL(line, ss, dest, source, length, seedToSoil, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> soilToFert;
    readSDL(line, ss, dest, source, length, soilToFert, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> fertToWater;
    readSDL(line, ss, dest, source, length, fertToWater, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> waterToLight;
    readSDL(line, ss, dest, source, length, waterToLight, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> lightToTemp;
    readSDL(line, ss, dest, source, length, lightToTemp, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> tempToHumid;
    readSDL(line, ss, dest, source, length, tempToHumid, input);
    getline(input, line);
    getline(input, line);

    vector<tuple<double, double, double>> humidToLoc;
    readSDL(line, ss, dest, source, length, humidToLoc, input);

    findSeedMap2(seeds, seedToSoil);
    findSeedMap2(seeds, soilToFert);
    findSeedMap2(seeds, fertToWater);
    findSeedMap2(seeds, waterToLight);
    findSeedMap2(seeds, lightToTemp);
    findSeedMap2(seeds, tempToHumid);
    findSeedMap2(seeds, humidToLoc);

    for (int i = 0; i < seeds.size(); i++)
    {
        if (get<0>(seeds[i]) < sum)
            sum = get<0>(seeds[i]);
    }

    return sum;
}

int main()
{
    cout << unsigned long long(one());
    cout << "\n";
    cout << unsigned long long(two());

    return 0;
}