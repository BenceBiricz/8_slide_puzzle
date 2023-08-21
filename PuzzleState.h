#pragma once

#include <vector>
#include <iostream>

class PuzzleState
{
public:
	std::vector<int> state;
	int heuristicValue = 0;
	int pathCost = 0;
	int swapIndex = -1;
	std::vector<int> parent;
	//PuzzleState* parent = nullptr;
	PuzzleState(std::vector<int> state, int heuristicValue);
	//PuzzleState(std::vector<int> state, int heuristicValue, int pathCost, PuzzleState* parent); // Update parameter type
	PuzzleState(std::vector<int> state, int heuristicValue, int pathCost, std::vector<int> parent);
	// Overload comparison operator for priority queue
	bool operator>(const PuzzleState& other) const {
		return (pathCost + heuristicValue) > (other.pathCost + other.heuristicValue);
	}
};

