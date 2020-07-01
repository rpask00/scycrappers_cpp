#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>    // std::next_permutation, std::sort

using namespace std;

map<string, vector<vector<int>>> get_permutations(int arr[], int n) {
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


class Puzzle {
public:
	int SIZE;
	map<string, vector<vector<int>>> views;
	vector<int> raw_clues;
	Clue clues[14];
	City city;

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

			vector<vector<int>> columns = get_views(col_front, col_back);
			vector<vector<int>> rows = get_views(row_front, row_back);

			clues[i].initialize(columns, col_front, col_back, true, i);
			clues[SIZE + i].initialize(rows, row_front, row_back, false, i);
		};
	};


	vector<vector<int>> get_views(int front, int back) {
		string key = to_string(front) + to_string(back);
		vector<vector<int>> view_storage = {};
		if (front != 0 && back != 0)
			return views[key];

		else if (front == 0 && back == 0) {
			for (int a = 1; a <= SIZE; a++) {
				for (int b = 1; b <= SIZE; b++) {
					key = to_string(a) + to_string(b);
					view_storage.reserve(views[key].size());
					view_storage.insert(view_storage.end(), views[key].begin(), views[key].end());
				}
			}
		}

		else if (front != 0) {
			for (int i = 1; i <= SIZE; i++) {
				key = to_string(front) + to_string(i);
				view_storage.reserve(views[key].size());
				view_storage.insert(view_storage.end(), views[key].begin(), views[key].end());
			}
		}
		else {
			for (int i = 1; i <= SIZE; i++) {
				key = to_string(i) + to_string(back);
				view_storage.reserve(views[key].size());
				view_storage.insert(view_storage.end(), views[key].begin(), views[key].end());
			}
		}


		return view_storage;
	};

	City solve() {

		while (true) {
			bool is_end = true;
			for (int x = 0; x < SIZE; x++) {
				for (int y = 0; y < SIZE; y++) {
					set<int> col_set;
					set<int> row_set;

					if (clues[x].views.size() == 0 || clues[SIZE + y].views.size() == 0)
						continue;

					for (vector<int> col : clues[x].views)
						col_set.insert(col[y]);

					for (vector<int> row : clues[SIZE + y].views)
						row_set.insert(row[x]);

					set<int>common;
					set_intersection(col_set.begin(), col_set.end(), row_set.begin(), row_set.end(), inserter(common, common.begin()));

					vector<vector<int>> new_cols(clues[x].views.size());
					vector<vector<int>> new_rows(clues[SIZE + y].views.size());


					auto new_col_end = copy_if(clues[x].views.begin(), clues[x].views.end(), new_cols.begin(), [y, common](vector<int> col) {return common.count(col[y]) == 1; });
					auto new_row_end = copy_if(clues[SIZE + y].views.begin(), clues[SIZE + y].views.end(), new_rows.begin(), [x, common](vector<int> row) {return common.count(row[x]) == 1; });

					new_cols.resize(distance(new_cols.begin(), new_col_end));
					new_rows.resize(distance(new_rows.begin(), new_row_end));


					if (clues[x].views.size() != new_cols.size() || clues[SIZE + y].views.size() != new_rows.size())
						is_end = false;

					clues[x].views = new_cols;
					clues[SIZE + y].views = new_rows;
				};

			};
			if (is_end) 
				break;
		
		};
		return after_solve();

	};

	City after_solve() {
		//Clue *clue = clues;
		for (vector<int> insertion : clues->views) {
			city.insert_column(insertion, clues->index);

			if (solve_recursion(clues))
				return city;

			city.clear_city();
		}

		return city;
	};

	bool solve_recursion(Clue* clue) {
		clue++;

		vector<vector<int>> backup = city.city;
		for (vector<int> insertion : clue->views) {
			if (clue->is_vertical && city.is_valid_column(insertion, clue->index)) {
				city.insert_column(insertion, clue->index);
				if (clue == &clues[2 * SIZE - 1])
					return true;

				if (solve_recursion(clue))
					return true;
			}

			if (!clue->is_vertical && city.is_valid_row(insertion, clue->index)) {
				city.insert_row(insertion, clue->index);
				if (clue == &clues[2 * SIZE - 1])
					return true;

				if (solve_recursion(clue))
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
	return puz.solve().city;
}


int main() {
	Puzzle puz1({ 3, 3, 2, 1, 2, 2, 3,   4, 3, 2, 4, 1, 4, 2,   2, 4, 1, 4, 5, 3, 2,   3, 1, 4, 2, 5, 2, 3 }, 7);
	/*Puzzle puz3({ 0, 0, 5, 3, 0, 2, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 3, 2, 5, 4, 2, 2, 0, 0, 0, 0, 5 },7);
	Puzzle puz4({ 7, 0, 0, 0, 2, 2, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 4 }, 7);
	Puzzle puz5({6, 4, 0, 2, 0, 0, 3, 0, 3, 3, 3, 0, 0, 4, 0, 5, 0, 5, 0, 2, 0, 0, 0, 0, 4, 0, 0, 3},7);
	Puzzle puz6({0, 0, 0, 5, 0, 0, 3, 0, 6, 3, 4, 0, 0, 0, 3, 0, 0, 0, 2, 4, 0, 2, 6, 2, 2, 2, 0, 0},7);
	Puzzle puz7({0, 0, 5, 0, 0, 0, 6, 4, 0, 0, 2, 0, 2, 0, 0, 5, 2, 0, 0, 0, 5, 0, 3, 0, 5, 0, 0, 3},7);
	Puzzle puz8({0, 0, 5, 3, 0, 2, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 3, 2, 5, 4, 2, 2, 0, 0, 0, 0, 5},7);
	Puzzle puz9({0, 2, 3, 0, 2, 0, 0, 5, 0, 4, 5, 0, 4, 0, 0, 4, 2, 0, 0, 0, 6, 5, 2, 2, 2, 2, 4, 1},7);
	Puzzle puz11({0, 2, 3, 0, 2, 0, 0, 5, 0, 4, 5, 0, 4, 0, 0, 4, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0},7);
	Puzzle puz12({3, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 4, 7, 0, 0, 0, 2, 2, 3, 0, 0, 3, 0, 0, 0, 0},7);
	Puzzle puz13({0, 0, 0, 0, 5, 0, 4, 7, 0, 0, 0, 2, 2, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 5, 0},7);
	Puzzle puz14({0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 4, 7, 0, 0, 0, 2, 2, 3},7);*/

	cout << "start" << endl;

	puz1.solve().print_city();
	//puz3.solve().print_city();
	//puz4.solve().print_city();
	//puz5.solve().print_city();
	//puz6.solve().print_city();
	//puz7.solve().print_city();
	//puz8.solve().print_city();
	//puz9.solve().print_city();
	//puz11.solve().print_city();
	//puz12.solve().print_city();
	//puz13.solve().print_city();
	//puz14.solve().print_city();
	
	cout << "stop" << endl;

	return 0;
}


