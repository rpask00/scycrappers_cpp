#pragma once
#include <vector>


class City {
public:
	std::vector<std::vector<int>> city;
	int SIZE = 7;
	City();
	void insert_row(std::vector<int> row, int y);
	void insert_column(std::vector<int> column, int x);
	bool is_valid_row(std::vector<int> row, int y) ;
	bool is_valid_column(std::vector<int> column, int x);
	void print_city();
	void clear_city();
};

