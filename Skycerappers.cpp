#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>    // std::next_permutation, std::sort

using namespace std;

map<int, vector<vector<int>>> get_permutations(int arr[], int n) {
	auto vertigo = [](vector<int> permutation) {
		int count = 1;
		int previous = permutation[0];

		for (int p : permutation) {
			if (p > previous) {
				previous = p;
				count++;
			}
		}

		return count;
	};

	sort(arr, arr + n);

	vector<int>temp;
	map<string, vector<vector<int>> > views;

	do {
		for (int i = 0; i < n; i++)
			temp.push_back(arr[i]);

		int back_view = vertigo(temp);
		reverse(temp.begin(), temp.end());
		int fron_view = vertigo(temp);

		views[to_string(fron_view) + to_string(back_view)].push_back(temp);
		temp.clear();

	} while (next_permutation(arr, arr + n));

	return views;
};

class City {
public:
	vector<vector<int>> city;
	int SIZE = 7;
	City() {
		for (int i = 0; i < SIZE; i++) {
			city.push_back({});
			for (int j = 0; j < SIZE; j++)
				city[i].push_back(0);

		}
		print_city();
	};

	void insert_row(vector<int> row, int y) {
		for (int i = 0; i < SIZE; i++)
			city[y][i] = row[i];
	};

	void insert_column(vector<int> column, int x) {
		for (int i = 0; i < SIZE; i++)
			city[i][x] = column[i];
	};

	bool is_valid_row(vector<int> row, int y) {
		for (int i = 0; i < SIZE; i++) {
			if (city[y][i] == 0)
				continue;


			if (city[y][i] != row[i])
				return false;
		}
		return true;
	};

	bool is_valid_column(vector<int> column, int x) {
		for (int i = 0; i < SIZE; i++) {
			if (city[i][x] == 0)
				continue;

			if (city[i][x] != column[i])
				return false;
		}
		return true;
	};

	void print_city() {
		cout << "--------------" << endl;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				cout << city[i][j] << " ";
			}
			cout << endl;
		}
		cout << "--------------" << endl;
	};

	void clear_city() {
		for (int i = 0; i < SIZE; i++) {
			city[i].clear();
		};

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				city[i].push_back(0);

			};
		};



	};


};



class Puzzle {
public:
	int SIZE;
	map<string, vector<vector<int>>> views;
	list<Clue>clues;
	City city;
	vector<int> raw_clues;

	Puzzle(vector<int> clue, int siz) {
		raw_clues = clue;
		SIZE = siz;
		city.SIZE = SIZE;
		int example[7] = { 1,2,3,4,5,6,7 };
		views = get_permutations(example, 7);

		for (int i = 0; i < SIZE; i++) {
			int col_front = clue[i];
			int col_back = clue[3 * SIZE - 1 - i];
			int row_front = clue[4 * SIZE - 1 - i];
			int row_back = clue[SIZE + i];

			vector<vector<int>> column = get_views(col_front, col_back);
			vector<vector<int>> row = get_views(row_front, row_back);

			clues.push_back(Clue(column, col_front, col_back, true, i));
			clues.push_back(Clue(row, row_front, row_back, false, i));
		};
	};

	vector<vector<int>> get_views(int front, int back) {
		string key = to_string(front) + to_string(back);
		if (front != 0 && back != 0) {
			return views[key];
		}

		vector<vector<int>> view_storage = {};

		if (front != 0) {
			for (int i = 0; i < SIZE; i++) {
				key = to_string(front) + to_string(i);
				view_storage.reserve(views[key].size());
				view_storage.insert(view_storage.end(), views[key].begin(), views[key].end());
			}
			return view_storage;
		}

		for (int i = 0; i < SIZE; i++) {
			key = to_string(i) + to_string(back);
			view_storage.reserve(views[key].size());
			view_storage.insert(view_storage.end(), views[key].begin(), views[key].end());
		}
		return view_storage;
	};

	void pre_solve() {
		for (int i = 0; i < SIZE; i++) {
			int col_front = raw_clues[i];
			int col_back = raw_clues[3 * SIZE - 1 - i];
			int row_front = raw_clues[4 * SIZE - 1 - i];
			int row_back = raw_clues[SIZE + i];

			string col_key = to_string(col_front) + to_string(col_back);
			string row_key = to_string(row_front) + to_string(row_back);


			for (int i = 0; i < SIZE; i++) {

				set<int> col_set;


			};

		};

	};

	City solve() {
		list<Clue>::iterator clue = clues.begin();
		for (vector<int> insertion : clue->views) {
			city.insert_column(insertion, clue->index);

			if (solve_puzzle(clue))
				return city;

			city.clear_city();
		}

		return city;
	};

	bool solve_puzzle(list<Clue>::iterator clue) {
		clue++;
		vector<vector<int>> backup = city.city;
		for (vector<int> insertion : clue->views) {
			//city.print_city();
			if (clue->is_vertical && city.is_valid_column(insertion, clue->index)) {
				city.insert_column(insertion, clue->index);
				if (clue == clues.end())
					return true;

				if (solve_puzzle(clue))
					return true;
			}

			if (!clue->is_vertical && city.is_valid_row(insertion, clue->index)) {
				city.insert_row(insertion, clue->index);
				if (clue == clues.end())
					return true;

				if (solve_puzzle(clue))
					return true;
			}
			city.city = backup;
		}
		return false;
	};
};


std::vector<std::vector<int>> SolvePuzzle(const std::vector<int>& clues)
{
	Puzzle puz(clues, 7);
	return {};
}


int main() {
	Puzzle puz({ 3, 3, 2, 1, 2, 2, 3,   4, 3, 2, 4, 1, 4, 2,   2, 4, 1, 4, 5, 3, 2,   3, 1, 4, 2, 5, 2, 3 }, 7);

	puz.solve().print_city();


	return 0;
}


