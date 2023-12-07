#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

#define FIVE 7
#define FOUR 6
#define FULL 5
#define THREE 4
#define TWO_PAIR 3
#define PAIR 2
#define HIGH 1

using namespace std;

class Hand {
public:

    vector<int> cards;
    unsigned long long bet;
    int type;

    Hand(string cardStr, string bet)
    {

        set<char> test;

        for (int i = 0; i < cardStr.length(); i++)
        {
            test.insert(cardStr[i]);
            switch (cardStr[i])
            {
            case 'A':
                cards.push_back(14);
                break;
            case 'K':
                cards.push_back(13);
                break;
            case 'Q':
                cards.push_back(12);
                break;
            case 'J':
                cards.push_back(11);
                break;
            case 'T':
                cards.push_back(10);
                break;
            default:
                cards.push_back(cardStr[i] - '0');
            }
        }
        this->bet = atoll(bet.c_str());

        if (test.size() == 5)
            type = HIGH;
        else if (test.size() == 4)
            type = PAIR;

        else if (test.size() == 3)
        {
            type = TWO_PAIR;
            map<char, int> t;
            t[cardStr[0]] = 1;
            for (int i = 1; i < cardStr.length(); i++)
            {
                if (t.find(cardStr[i]) == t.end())
                    t[cardStr[i]] = 1;
                else
                    t[cardStr[i]] += 1;
            }
            for (map<char, int>::iterator it = t.begin(); it != t.end(); it++)
            {
                if (it->second == 3)
                {
                    type = THREE;
                    break;
                }
            }
        }
        else if (test.size() == 2)
        {
            char a;
            a = cardStr[0];
            int aCnt, bCnt;
            aCnt = bCnt = 0;
            for (int i = 0; i < cardStr.length(); i++)
            {
                if (cardStr[i] == a)
                    aCnt++;
                else
                    bCnt++;
            }
            if (aCnt == 1 || aCnt == 4)
                type = FOUR;
            else
                type = FULL;
        }
        else
            type = FIVE;

    }

    bool operator<(Hand const& right)
    {
        if (this->type < right.type)
            return true;
        else if (this->type > right.type)
            return false;
        else
            for (int i = 0; i < this->cards.size(); i++)
            {
                if (this->cards[i] < right.cards[i])
                    return true;
                else if (this->cards[i] > right.cards[i])
                    return false;
            }
        return false;
    }
};

unsigned long long one()
{
    fstream input;
    input.open("Day7.txt");

    string line;
    unsigned long long sum = 0;

    int numline = count(istreambuf_iterator<char>(input), istreambuf_iterator<char>(), '\n');
    input.clear();
    input.seekg(0, ios::beg);

    vector<Hand> hands, final;

    while (!input.eof())
    {
        getline(input, line);
        auto space = line.find_first_of(" ");
        Hand tmp(line.substr(0, space), line.substr(space + 1, line.length() - space));
        hands.push_back(tmp);
    }

    sort(hands.begin(), hands.end());

    for (unsigned long long i = 0; i < hands.size(); i++)
        sum += hands[i].bet * (i + 1);


    return sum;
}

class JHand {
public:

    vector<int> cards;
    unsigned long long bet;
    int type;

    JHand(string cardStr, string bet)
    {

        set<char> test;
        int jCnt = 0;

        for (int i = 0; i < cardStr.length(); i++)
        {
            test.insert(cardStr[i]);
            switch (cardStr[i])
            {
            case 'A':
                cards.push_back(14);
                break;
            case 'K':
                cards.push_back(13);
                break;
            case 'Q':
                cards.push_back(12);
                break;
            case 'J':
                cards.push_back(0);
                jCnt++;
                break;
            case 'T':
                cards.push_back(10);
                break;
            default:
                cards.push_back(cardStr[i] - '0');
            }
        }
        this->bet = atoll(bet.c_str());

        if (test.size() == 5 && jCnt == 0)
            type = HIGH;
        else if (test.size() == 5)
            type = PAIR;

        else if (test.size() == 4 && jCnt == 0)
            type = PAIR;
        else if (test.size() == 4 && jCnt == 1)
            type = THREE;
        else if (test.size() == 4 && jCnt == 2)
            type = THREE;

        else if (test.size() == 3 && jCnt == 0)
        {
            type = 3;
            map<char, int> t;
            t[cardStr[0]] = 1;
            for (int i = 1; i < cardStr.length(); i++)
            {
                if (t.find(cardStr[i]) == t.end())
                    t[cardStr[i]] = 1;
                else
                    t[cardStr[i]] += 1;
            }
            for (map<char, int>::iterator it = t.begin(); it != t.end(); it++)
            {
                if (it->second == 3)
                {
                    type = 4;
                    break;
                }
            }
        }
        else if (test.size() == 3 && jCnt == 1)
        {
            type = FULL;
            map<char, int> t;
            t[cardStr[0]] = 1;
            for (int i = 1; i < cardStr.length(); i++)
            {
                if (t.find(cardStr[i]) == t.end())
                    t[cardStr[i]] = 1;
                else
                    t[cardStr[i]] += 1;
            }
            for (map<char, int>::iterator it = t.begin(); it != t.end(); it++)
            {
                if (it->second == 3)
                {
                    type = FOUR;
                    break;
                }
            }
        }
        else if (test.size() == 3 && jCnt == 2)
        {
            type = FOUR;
            map<char, int> t;
            t[cardStr[0]] = 1;
            for (int i = 1; i < cardStr.length(); i++)
            {
                if (t.find(cardStr[i]) == t.end())
                    t[cardStr[i]] = 1;
                else
                    t[cardStr[i]] += 1;
            }
            for (map<char, int>::iterator it = t.begin(); it != t.end(); it++)
            {
                if (it->second == 3)
                {
                    type = FIVE;
                    break;
                }
            }
        }
        else if (test.size() == 3 && jCnt == 3)
        {
            type = FOUR;
        }

        else if (test.size() == 2, jCnt == 0)
        {
            char a;
            a = cardStr[0];
            int aCnt, bCnt;
            aCnt = bCnt = 0;
            for (int i = 0; i < cardStr.length(); i++)
            {
                if (cardStr[i] == a)
                    aCnt++;
                else
                    bCnt++;
            }
            if (aCnt == 1 || aCnt == 4)
                type = FOUR;
            else
                type = FULL;
        }
        else
            type = FIVE;
    }

    bool operator<(JHand const& right)
    {
        if (this->type < right.type)
            return true;
        else if (this->type > right.type)
            return false;
        else
            for (int i = 0; i < this->cards.size(); i++)
            {
                if (this->cards[i] < right.cards[i])
                    return true;
                else if (this->cards[i] > right.cards[i])
                    return false;
            }
        return false;
    }
};

unsigned long long two()
{
    fstream input;
    input.open("Day7.txt");

    string line;
    unsigned long long sum = 0;

    int numline = count(istreambuf_iterator<char>(input), istreambuf_iterator<char>(), '\n');
    input.clear();
    input.seekg(0, ios::beg);

    vector<JHand> hands, final;

    while (!input.eof())
    {
        getline(input, line);
        auto space = line.find_first_of(" ");
        JHand tmp(line.substr(0, space), line.substr(space + 1, line.length() - space));
        hands.push_back(tmp);
    }

    sort(hands.begin(), hands.end());

    for (unsigned long long i = 0; i < hands.size(); i++)
        sum += hands[i].bet * (i + 1);


    return sum;
}

int main()
{
    cout << unsigned long long(one());
    cout << "\n";
    cout << unsigned long long(two());
    return 0;
}