#include "PuzzleState.h"

PuzzleState::PuzzleState(std::vector<int> state, int heuristicValue) {
	this->state = state;
	this->heuristicValue = heuristicValue;
}

PuzzleState::PuzzleState(std::vector<int> state, int heuristicValue, int pathCost, std::vector<int> parent) {
	this->state = state;
	this->heuristicValue = heuristicValue;
	this->pathCost = pathCost;
	this->parent = parent;
}

