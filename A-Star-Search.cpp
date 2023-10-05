﻿// A-Star-Search.cpp : Defines the entry point for the application.

#include "A-Star-Search.h"
#include <vector>
#include <sstream>
using namespace std;

int main()
{

    vector <vector<State>> Board = ReadBoardFile("1.board");

    int start[] = { 0,0 };

    int goal[] = { 4,5 };

    Search(Board, start, goal);

    printBoard(ReadBoardFile("1.board"));

    return 0;
}


void printBoard(vector<vector<State>> grid)
{
    // Prints Vector of Vector ints in 2d Board Format
    for (size_t i = 0; i < grid.size(); ++i)
    {
        cout << " " << endl;
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            // Call CellString to convert State enum values to strings and print them.
            cout << CellString(grid[i][j]) << " ";
        }
    }

    cout << endl;
}



vector<vector<State>> ReadBoardFile(const string& filePath) {

    vector<vector<State>> board{};

    //Open the file for reading
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file. checking directory location might help " << endl;

    }
     

    string line;

    while (getline(inputFile, line)) {

        vector<State> parsedData = ParseLine(line);

        board.push_back(parsedData);
    }

    inputFile.close();

    return board;
}

vector<State> ParseLine(string line) {

    vector<State> result;
    istringstream iss(line);
    char comma;

    int num;
    while (iss >> num) {
        // Depending on the value in the line, add kEmpty or kObstacle to the result.
        if (num == 0)
        {
            result.push_back(kEmpty);
        }
        else
        {
            result.push_back(kObstacle);
        }
        if (iss >> comma) {
            if(comma != ',')
            {
                 cerr << "Error: Expected comma but found " << comma << " '.'" << endl;
                 break; //Handle error and exit the loop
            }

        }
    }

    return result;

}

vector<vector<State>> Search(vector<vector<State>> board, int start[2], int goal[2]) {

    vector<vector<int>> open = {};

    vector<vector<State>> solution;

    // Initialize the starting node.
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);

    AddToOpen(x, y, g, h, open, solution);

    vector<vector<int>> heuristic = { {9,8,7,6,5,4},
                                      {8,7,6,5,4,3},
                                      {7,6,5,4,3,2},
                                      {6,5,4,3,2,1},
                                      {5,4,3,2,1,0} };
    
    if (solution.empty())
    {
        cout << "No path found" << endl;
    }
    else if (!solution.empty())
    {

    }
    
    
    return solution;
    
   
}

int Heuristic(int x1, int y1, int x2, int y2)
{  
    // Calculate Manhattan distance - (md)
    int md = abs(x2 - x1) + abs(y2 - y1);

    return md;
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>>& open, vector<vector<State>>& grid)
{
    vector<int> node = { x, y, g, h };
    open.push_back(node);

    grid[x][y] = kClosed;

}

bool Compare(vector<int> node1, vector<int> node2)
{
    
    // Extract g & h values from node1 
    int g1 = node1[2];
    int h1 = node1[3];
    

    //Extract g & h values from node2
    int g2 = node2[2];
    int h2 = node2[3];

    // Calculate f values for node1 and node2 
    int f1 = g1 + h1; 
    int f2 = g2 + h2;

    //Compare the f values and return the result
    return f1 > f2;
}