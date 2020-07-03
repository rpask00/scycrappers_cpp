#include "Funcs.h"
#include <algorithm>    // std::next_permutation, std::sort


std::map<std::string, std::vector<std::vector<int>>> get_permutations(int arr[], int n) {
	auto vertigo = [](std::vector<int> permutation) {
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

	std::sort(arr, arr + n);

	std::vector<int>temp;
	std::map<std::string, std::vector<std::vector<int>> > views;

	do {
		for (int i = 0; i < n; i++)
			temp.push_back(arr[i]);

		int back_view = vertigo(temp);
		reverse(temp.begin(), temp.end());
		int fron_view = vertigo(temp);

		views[std::to_string(fron_view) + std::to_string(back_view)].push_back(temp);

		temp.clear();

	} while (std::next_permutation(arr, arr + n));

	return views;
};