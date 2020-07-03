#include "Clue.h"

void Clue::initialize(std::vector<std::vector<int>> viu, int front, int back, bool direction, int position) {
	index = position;
	front_view = front;
	back_view = back;
	is_vertical = direction;
	key = std::to_string(front_view) + std::to_string(back_view);
	views = viu;
};
