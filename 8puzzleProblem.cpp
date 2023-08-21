// 8puzzleProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
How the game works:
    - Get a randomized starting state
    - It is possible to change the block with the empty block
    - Find the best results

To do:
    - Create a randozmized INITIAL STATE
    - DEFINE the data type for saving the values
    - DEFINE the neighbours
    - Use Astar algorithm to solve the puzzle
    - Show the different changeing states

 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include "PuzzleState.h"

using namespace std;

//Calculate the distance between current position and goal position
int manhattanDistance(vector<int> currentState, vector<int> goalState) {
    int manDistance = 0;
    int currentRow;
    int goalRow;
    int currentCol;
    int goalCol;

    for (int i = 0; i < currentState.size(); i++) {
        if (currentState[i] != 0) {

            currentCol = i % 3;

            if (i < 3) {
                currentRow = 0;
            }
            else if (i < 6) {
                currentRow = 1;
            }
            else {
                currentRow = 2;
            }

            //Goal col
            int goalIndex = distance(goalState.begin(), find(goalState.begin(), goalState.end(), currentState[i]));
            if (goalIndex < 3) {
                goalRow = 0;
            }
            else if (goalIndex < 6) {
                goalRow = 1;
            }
            else {
                goalRow = 2;
            }
            goalCol = goalIndex % 3;

            manDistance += abs(currentRow - goalRow) + abs(currentCol - goalCol);
        }
    }
    return manDistance;
}


//Print out the puzzle
void showPuzzle(vector<int> puzzle) {
    cout << "\n";
    for (int i = 0; i < puzzle.size(); i++) {
        if (i == 3 || i == 6) {
            cout << "\n";
        }

        if (puzzle[i] == 0) {
            cout << " ";
        }
        else {
            cout << puzzle[i];
        }
    }
    cout << "\n";
}

//Initialize the starting state
vector<int> createInitialPuzzle() {
    vector<int> initialPuzzle(9);

    for (int i = 0; i < initialPuzzle.size(); i++) {
        initialPuzzle[i] = i;
    }

    //Shuffle the ininial state
    int seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(initialPuzzle.begin(), initialPuzzle.end(), default_random_engine(seed));

    return initialPuzzle;
}

//Check if the puzzle is solvable
//Its not possible to solve if the number of inversions is odd
bool isSolvable(const vector<int>& puzzle) {
    int inversions = 0;
    int size = puzzle.size();

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (puzzle[i] > puzzle[j] && puzzle[i] != 0 && puzzle[j] != 0) {
                inversions++;
            }
        }
    }

    // If the number of inversions is even, the puzzle is solvable.
    return inversions % 2 == 0;
}

//Finding the index of the empty tile
int findEmptyValue(vector<int> state) {
    for (int i = 0; i < state.size(); i++) {
        if (state[i] == 0) {
            return i;
        }
    }
}

//Neighbour map
vector<int> neighbours(int index) {
    vector<int> neighboursVector;

    switch (index) {
    case 0:
        neighboursVector.push_back(1);
        neighboursVector.push_back(3);
        break;
    case 1:
        neighboursVector.push_back(0);
        neighboursVector.push_back(2);
        neighboursVector.push_back(4);
        break;
    case 2:
        neighboursVector.push_back(1);
        neighboursVector.push_back(5);
        break;
    case 3:
        neighboursVector.push_back(4);
        neighboursVector.push_back(0);
        neighboursVector.push_back(6);
        break;
    case 4:
        neighboursVector.push_back(3);
        neighboursVector.push_back(5);
        neighboursVector.push_back(1);
        neighboursVector.push_back(7);
        break;
    case 5:
        neighboursVector.push_back(4);
        neighboursVector.push_back(2);
        neighboursVector.push_back(8);
        break;
    case 6:
        neighboursVector.push_back(7);
        neighboursVector.push_back(3);
        break;
    case 7:
        neighboursVector.push_back(6);
        neighboursVector.push_back(8);
        neighboursVector.push_back(4);
        break;
    case 8:
        neighboursVector.push_back(7);
        neighboursVector.push_back(5);
        break;
    }
    return neighboursVector;
}
//Fuction for swapping tiles
vector<int> swapTiles(vector<int> state, int index1, int index2) {
    int tempValue = state[index1];
    state[index1] = state[index2];
    state[index2] = tempValue;

    return state;
}


int main()
{
    vector<int> goalStatePuzzle(9);
    for (int i = 0; i < goalStatePuzzle.size() - 1; i++) {
        goalStatePuzzle[i] = i + 1;
    }
    goalStatePuzzle[8] = 0;

    //Start or the game --> initialize and randomize the starting state
    vector<int> startingPuzzle(9);
    startingPuzzle = createInitialPuzzle();

    //Show the puzzle
    cout << "Starting state:\n";
    showPuzzle(startingPuzzle);
    cout << "\n\nGoal:\n";
    showPuzzle(goalStatePuzzle);

    //Decide if the puzzle is solvable
    cout << "\n";
    if (isSolvable(startingPuzzle) == false) {
        cout << "\nPuzzle is NOT solvable!";
        cout << "\n\nDo you want to reshuffle? (Y/N): ";

        string s;
        cin >> s;

        if (s == "Y") {
            main();
        }
    }
    else {
        cout << "\nPuzzle is solvable!";

        // A* Algorithm Loop
        priority_queue<PuzzleState, vector<PuzzleState>, greater<PuzzleState>> stateQueue;
        stateQueue.push(PuzzleState(startingPuzzle, manhattanDistance(startingPuzzle, goalStatePuzzle), 0, {}));

        int startHeurestic = manhattanDistance(startingPuzzle, goalStatePuzzle);

        while (!stateQueue.empty()) {
            PuzzleState currentState = stateQueue.top();
            stateQueue.pop();
                
            // Show the current state
            if (currentState.heuristicValue < startHeurestic) {
                showPuzzle(currentState.state);
                startHeurestic = currentState.heuristicValue;
            }
            
            // Check if current state is the goal state
            if (currentState.state == goalStatePuzzle) {
                cout << "\n\nSolved the puzzle!\n";
                break; // Exit the loop since we've found the solution
            }

            // Generate and enqueue valid neighbors
            int emptyIndex = findEmptyValue(currentState.state);
            vector<int> neighborIndices = neighbours(emptyIndex);

            //Swapping around with the neighbours and checking the best heuristic value
            for (int neighborIndex : neighborIndices) {
                vector<int> nextState = swapTiles(currentState.state, emptyIndex, neighborIndex);
                int heuristicValue = manhattanDistance(nextState, goalStatePuzzle);
                int pathCost = currentState.pathCost + 1;
                stateQueue.push(PuzzleState(nextState, heuristicValue, pathCost, currentState.state));
            }
        }
    }
    cout << "\n";

    return 0;
}

