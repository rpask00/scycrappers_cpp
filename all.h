#pragma once
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>    // std::next_permutation, std::sort

class Clue {
public:
	int front_view;
	int back_view;
	int index;
	bool is_vertical;
	string key;
	vector<vector<int>> views;

	Clue(vector<vector<int>> viu = { {} }, int front = 0, int back = 0, bool direction = false, int position = 0) {
		index = position;
		front_view = front;
		back_view = back;
		is_vertical = direction;
		key = to_string(front_view) + to_string(back_view);
		views = viu;
	};

	void initialize(vector<vector<int>> viu, int front, int back, bool direction, int position) {
		index = position;
		front_view = front;
		back_view = back;
		is_vertical = direction;
		key = to_string(front_view) + to_string(back_view);
		views = viu;
	};
};