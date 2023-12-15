#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <set>

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3


using namespace std;


void saveMaze(vector<vector<char>>& maze, int num)
{
    ofstream myfile;

    string name = "example.txt";
    name.append(to_string(num));
    myfile.open(name);
    for (int r = 0; r < maze.size(); r++)
    {
        for (int c = 0; c < maze[0].size();c++)
        {
            myfile << maze[r][c];
        }
        myfile << '\n';
    }
    myfile.close();
}

bool canMoveL(vector<vector<char>>& maze, int r, int c)
{
    if (c == 0)
        return false;

    if (maze[r][c] != '-' && maze[r][c] != 'J' && maze[r][c] != '7' && maze[r][c] != 'S')
        return false;

    if (maze[r][c - 1] == '-' || maze[r][c - 1] == 'F' || maze[r][c - 1] == 'L' || maze[r][c] != 'S')
        return true;

    return false;
}

bool canMoveR(vector<vector<char>>& maze, int r, int c)
{
    if (c == maze[0].size() - 1)
        return false;

    if (maze[r][c] != '-' && maze[r][c] != 'F' && maze[r][c] != 'L' && maze[r][c] != 'S')
        return false;

    if (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7' || maze[r][c] != 'S')
        return true;

    return false;
}

bool canMoveU(vector<vector<char>>& maze, int r, int c)
{
    if (r == 0)
        return false;

    if (maze[r][c] != '|' && maze[r][c] != 'J' && maze[r][c] != 'L' && maze[r][c] != 'S')
        return false;


    if (maze[r - 1][c] == '|' || maze[r - 1][c] == '7' || maze[r - 1][c] == 'F' || maze[r][c] != 'S')
        return true;

    return false;
}

bool canMoveD(vector<vector<char>>& maze, int r, int c)
{
    if (r == maze.size() - 1)
        return false;

    if (maze[r][c] != '|' && maze[r][c] != '7' && maze[r][c] != 'F' && maze[r][c] != 'S')
        return false;

    if (maze[r + 1][c] == '|' || maze[r + 1][c] == 'J' || maze[r + 1][c] == 'L' || maze[r][c] != 'S')
        return true;

    return false;
}


int one()
{
    fstream input;
    input.open("Day10.txt");

    int sum = 0;
    vector<vector<char>> maze, maze2;

    string line;

    int pathLength = 0;
    int sRow, sCol, cRow, cCol;

    while (!input.eof())
    {
        getline(input, line);
        vector<char> tmp;
        for (int i = 0; i < line.length(); i++)
        {
            tmp.push_back(line[i]);
            if (line[i] == 'S')
            {
                sRow = cRow = pathLength;
                sCol = cCol = i;
            }
        }

        pathLength++;
        maze.push_back(tmp);
    }

    maze2 = maze;

    pathLength = 1;
    int dirCameFrom;


    if (canMoveR(maze, sRow, sCol))
    {
        cCol++;
        dirCameFrom = LEFT;

    }
    else if (canMoveL(maze, sRow, sCol))
    {
        cCol--;
        dirCameFrom = RIGHT;
    }
    else if (canMoveD(maze, sRow, sCol))
    {
        cRow++;
        dirCameFrom = UP;
    }
    else
    {
        cRow--;
        dirCameFrom = DOWN;
    }


    while (cRow != sRow || cCol != sCol)
    {
        if (dirCameFrom != RIGHT && canMoveR(maze, cRow, cCol))
        {
            cCol++;
            dirCameFrom = LEFT;

        }
        else if (dirCameFrom != LEFT && canMoveL(maze, cRow, cCol))
        {
            cCol--;
            dirCameFrom = RIGHT;
        }
        else if (dirCameFrom != DOWN && canMoveD(maze, cRow, cCol))
        {
            cRow++;
            dirCameFrom = UP;
        }
        else
        {
            cRow--;
            dirCameFrom = DOWN;
        }

        pathLength++;
    }

    return pathLength / 2;

}

#define ENTRY set<tuple<char, char>>

int two()
{
    fstream input;
    input.open("Day10.txt");

    int sum = 0;
    vector<vector<char>> maze, bigMaze;
    set<tuple<int, int>> path;


    string line;

    int pathLength = 0;
    int sRow, sCol, cRow, cCol;

    while (!input.eof())
    {
        getline(input, line);
        vector<char> tmp;
        for (int i = 0; i < line.length(); i++)
        {
            tmp.push_back(line[i]);
            if (line[i] == 'S')
            {
                sRow = cRow = pathLength;
                sCol = cCol = i;
            }
        }

        pathLength++;
        maze.push_back(tmp);
    }

    pathLength = 1;
    int dirCameFrom;
    path.insert(make_tuple(sRow, sCol));

    if (canMoveR(maze, sRow, sCol))
    {
        cCol++;
        dirCameFrom = LEFT;

    }
    else if (canMoveL(maze, sRow, sCol))
    {
        cCol--;
        dirCameFrom = RIGHT;
    }
    else if (canMoveD(maze, sRow, sCol))
    {
        cRow++;
        dirCameFrom = UP;
    }
    else
    {
        cRow--;
        dirCameFrom = DOWN;
    }

    path.insert(make_tuple(cRow, cCol));

    while (cRow != sRow || cCol != sCol)
    {
        if (dirCameFrom != RIGHT && canMoveR(maze, cRow, cCol))
        {
            cCol++;
            path.insert(make_tuple(cRow, cCol));
            dirCameFrom = LEFT;
        }
        else if (dirCameFrom != LEFT && canMoveL(maze, cRow, cCol))
        {
            cCol--;
            path.insert(make_tuple(cRow, cCol));
            dirCameFrom = RIGHT;
        }
        else if (dirCameFrom != DOWN && canMoveD(maze, cRow, cCol))
        {
            cRow++;
            path.insert(make_tuple(cRow, cCol));
            dirCameFrom = UP;
        }
        else
        {
            cRow--;
            path.insert(make_tuple(cRow, cCol));
            dirCameFrom = DOWN;
        }
    }

    for (int r = 0; r < maze.size(); r++)
    {
        for (int c = 0; c < maze[0].size(); c++)
        {
            if (path.find(make_tuple(r, c)) == path.end())
            {
                maze[r][c] = ' ';
            }
        }
    }



    for (int r = 0; r < maze.size(); r++)
    {
        vector<char> x, y, z;
        for (int c = 0; c < maze[0].size(); c++)
        {
            switch (maze[r][c])
            {
            case '|':
                x.push_back(' '); x.push_back('|');x.push_back(' ');
                y.push_back(' '); y.push_back('|');y.push_back(' ');
                z.push_back(' '); z.push_back('|');z.push_back(' ');
                break;
            case '-':
                x.push_back(' '); x.push_back(' ');x.push_back(' ');
                y.push_back('-'); y.push_back('-');y.push_back('-');
                z.push_back(' '); z.push_back(' ');z.push_back(' ');
                break;
            case 'L':
                x.push_back(' '); x.push_back('|');x.push_back(' ');
                y.push_back(' '); y.push_back('|');y.push_back('-');
                z.push_back(' '); z.push_back(' ');z.push_back(' ');
                break;
            case 'J':
                x.push_back(' '); x.push_back('|');x.push_back(' ');
                y.push_back('-'); y.push_back('|');y.push_back(' ');
                z.push_back(' '); z.push_back(' ');z.push_back(' ');
                break;
            case '7':
                x.push_back(' '); x.push_back(' ');x.push_back(' ');
                y.push_back('-'); y.push_back('|');y.push_back(' ');
                z.push_back(' '); z.push_back('|');z.push_back(' ');
                break;
            case 'F':
                x.push_back(' '); x.push_back(' ');x.push_back(' ');
                y.push_back(' '); y.push_back('|');y.push_back('-');
                z.push_back(' '); z.push_back('|');z.push_back(' ');
                break;
            case 'S':
                if (r + 1 < maze.size() && r - 1 > 0)
                {
                    if ( // |
                        (maze[r + 1][c] == '|' && (maze[r - 1][c] == '|' || maze[r - 1][c] == '7' || maze[r - 1][c] == 'F'))
                        || (maze[r + 1][c] == 'J' && (maze[r - 1][c] == '|' || maze[r - 1][c] == '7' || maze[r - 1][c] == '7'))
                        || (maze[r + 1][c] == 'L' && (maze[r - 1][c] == '|' || maze[r - 1][c] == 'F' || maze[r - 1][c] == 'F'))
                        )
                    {
                        x.push_back(' '); x.push_back('|');x.push_back(' ');
                        y.push_back(' '); y.push_back('|');y.push_back(' ');
                        z.push_back(' '); z.push_back('|');z.push_back(' ');
                    }
                }

                if (c + 1 < maze[0].size() && c - 1 > 0)
                {
                    if ( // -
                        (maze[r][c - 1] == '-' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        || (maze[r][c - 1] == 'F' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        || (maze[r][c - 1] == 'L' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        )
                    {
                        x.push_back(' '); x.push_back(' ');x.push_back(' ');
                        y.push_back('-'); y.push_back('-');y.push_back('-');
                        z.push_back(' '); z.push_back(' ');z.push_back(' ');
                    }
                }
                if (c + 1 < maze[0].size() && r - 1 > 0)
                {
                    if ( // L
                        (maze[r - 1][c] == '|' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        || (maze[r - 1][c] == '7' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        || (maze[r - 1][c] == 'F' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        )
                    {
                        x.push_back(' '); x.push_back('|');x.push_back(' ');
                        y.push_back(' '); y.push_back('|');y.push_back('-');
                        z.push_back(' '); z.push_back(' ');z.push_back(' ');
                    }
                }
                if (c - 1 > 0 && r - 1 > 0)
                {
                    if ( // J
                        (maze[r - 1][c] == '|' && (maze[r][c - 1] == '-' || maze[r][c - 1] == 'L' || maze[r][c - 1] == 'F'))
                        || (maze[r - 1][c] == '7' && (maze[r][c - 1] == '-' || maze[r][c - 1] == 'L' || maze[r][c - 1] == 'F'))
                        || (maze[r - 1][c] == 'F' && (maze[r][c - 1] == '-' || maze[r][c - 1] == 'L' || maze[r][c - 1] == 'F'))
                        )
                    {
                        x.push_back(' '); x.push_back('|');x.push_back(' ');
                        y.push_back('-'); y.push_back('|');y.push_back(' ');
                        z.push_back(' '); z.push_back(' ');z.push_back(' ');
                    }
                }
                if (c - 1 > 0 && r + 1 < maze.size())
                {
                    if ( // 7
                        (maze[r + 1][c] == '|' && (maze[r][c - 1] == '-' || maze[r][c - 1] == 'L' || maze[r][c - 1] == 'F'))
                        || (maze[r + 1][c] == 'J' && (maze[r][c - 1] == '-' || maze[r][c - 1] == 'L' || maze[r][c - 1] == 'F'))
                        || (maze[r + 1][c] == 'L' && (maze[r][c - 1] == '-' || maze[r][c - 1] == 'L' || maze[r][c - 1] == 'F'))
                        )
                    {
                        x.push_back(' '); x.push_back(' ');x.push_back(' ');
                        y.push_back('-'); y.push_back('|');y.push_back(' ');
                        z.push_back(' '); z.push_back('|');z.push_back(' ');
                    }
                }
                if (c + 1 < maze[0].size() && r + 1 < maze.size())
                {
                    if ( // F
                        (maze[r + 1][c] == '|' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        || (maze[r + 1][c] == 'J' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        || (maze[r + 1][c] == 'L' && (maze[r][c + 1] == '-' || maze[r][c + 1] == 'J' || maze[r][c + 1] == '7'))
                        )
                    {
                        x.push_back(' '); x.push_back(' ');x.push_back(' ');
                        y.push_back(' '); y.push_back('*');y.push_back('-');
                        z.push_back(' '); z.push_back('|');z.push_back(' ');
                    }
                }
                break;
            default:
                x.push_back(' '); x.push_back(' ');x.push_back(' ');
                y.push_back(' '); y.push_back(' ');y.push_back(' ');
                z.push_back(' '); z.push_back(' ');z.push_back(' ');
            }
        }

        bigMaze.push_back(x);
        bigMaze.push_back(y);
        bigMaze.push_back(z);
    }

    for (int r = 1; r < bigMaze.size(); r += 3)
    {
        for (int c = 1; c < bigMaze[0].size(); c += 3)
        {
            if (bigMaze[r][c] != ' ')
                continue;

            int edgecount = 0;
            for (int i = c; i < bigMaze[0].size(); i += 3)
            {
                if (bigMaze[r + 1][i] == '|')
                {
                    edgecount++;
                }
            }
            if (edgecount % 2 == 1)
            {
                sum += 1;
                bigMaze[r][c] = 'a' + (edgecount % 26);
            }
            else {

            }
        }
    }
    saveMaze(bigMaze, 0);
    return sum;
}

int main()
{
    cout << one();
    cout << "\n";
    cout << two();

    return 0;
}



