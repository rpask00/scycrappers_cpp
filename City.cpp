#include "City.h"
#include <iostream>


City::City() {
		for (int i = 0; i < SIZE; i++) {
			city.push_back({});
			for (int j = 0; j < SIZE; j++)
				city[i].push_back(0);

		}
	};

void City::insert_row(std::vector<int> row, int y) {
	for (int i = 0; i < SIZE; i++)
		city[y][i] = row[i];
};

void City::insert_column(std::vector<int> column, int x) {
	for (int i = 0; i < SIZE; i++)
		city[i][x] = column[i];
};

bool City::is_valid_row(std::vector<int> row, int y) {
	for (int i = 0; i < SIZE; i++) {
		if (city[y][i] == 0)
			continue;


		if (city[y][i] != row[i])
			return false;
	}
	return true;
};

bool City::is_valid_column(std::vector<int> column, int x) {
	for (int y = 0; y < SIZE; y++) {
		for (int i = 0; i < SIZE; i++) {
			if (i == x)
				continue;

			if (city[y][i] == column[y])
				return false;
		}

		if (city[y][x] == 0)
			continue;

		if (city[y][x] != column[y])
			return false;
	}
	return true;
};

void City::print_city() {
	std::cout << "--------------" << std::endl;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << city[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "--------------" << std::endl;
};

void City::clear_city() {
		for (int i = 0; i < SIZE; i++) {
			city[i].clear();
		};

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				city[i].push_back(0);

			};
		};
	};
