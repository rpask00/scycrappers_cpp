#pragma once
#include "Clue.h"
#include "City.h"
#include <string>
#include <vector>
#include <map>


class Puzzle {
public:
	int SIZE;
	std::map<std::string, std::vector<std::vector<int>>> views;
	std::vector<int> raw_clues;
	Clue clues[14];
	City city;

	Puzzle(std::vector<int> clue, int siz);
	std::vector<std::vector<int>> get_views(int front, int back);
	City solve();
	City after_solve();


	bool solve_recursion(Clue* clue);
};