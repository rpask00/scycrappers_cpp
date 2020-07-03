#pragma once
#include <string>
#include <vector>

class Clue {
public:
	int front_view;
	int back_view;
	int index;
	bool is_vertical;
	std::string key;
	std::vector<std::vector<int>> views ;
	void initialize(std::vector<std::vector<int>> viu, int front, int back, bool direction, int position);
};