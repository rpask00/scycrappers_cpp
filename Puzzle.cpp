#include "Puzzle.h"
#include "City.h"
#include "Clue.h"
#include "source.h"
#include "Funcs.h"

using namespace std;

Puzzle::Puzzle(vector<int> clue, int siz) {

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


	vector<vector<int>> Puzzle::get_views(int front, int back) {
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

	City Puzzle::solve() {

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

	City Puzzle::after_solve() {
		//Clue *clue = clues;
		for (vector<int> insertion : clues->views) {
			city.insert_column(insertion, clues->index);

			if (solve_recursion(clues))
				return city;

			city.clear_city();
		}

		return city;
	};

	bool Puzzle::solve_recursion(Clue* clue) {
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
