﻿#include "source.h"
#include "Puzzle.h"

int main() {
	
	Puzzle puz1({ 3, 3, 2, 1, 2, 2, 3,   4, 3, 2, 4, 1, 4, 2,   2, 4, 1, 4, 5, 3, 2,   3, 1, 4, 2, 5, 2, 3 }, 7);
	puz1.solve().print_city();
	Puzzle puz3({ 0, 0, 5, 3, 0, 2, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 3, 2, 5, 4, 2, 2, 0, 0, 0, 0, 5 },7);
	puz3.solve().print_city();
	Puzzle puz4({ 7, 0, 0, 0, 2, 2, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 4 }, 7);
	puz4.solve().print_city();
	Puzzle puz5({ 6, 4, 0, 2, 0, 0, 3, 0, 3, 3, 3, 0, 0, 4, 0, 5, 0, 5, 0, 2, 0, 0, 0, 0, 4, 0, 0, 3 }, 7);
	puz5.solve().print_city();
	Puzzle puz6({ 0, 0, 0, 5, 0, 0, 3, 0, 6, 3, 4, 0, 0, 0, 3, 0, 0, 0, 2, 4, 0, 2, 6, 2, 2, 2, 0, 0 }, 7);
	puz6.solve().print_city();
	Puzzle puz7({ 0, 0, 5, 0, 0, 0, 6, 4, 0, 0, 2, 0, 2, 0, 0, 5, 2, 0, 0, 0, 5, 0, 3, 0, 5, 0, 0, 3 }, 7);
	puz7.solve().print_city();
	Puzzle puz8({ 0, 0, 5, 3, 0, 2, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 3, 2, 5, 4, 2, 2, 0, 0, 0, 0, 5 }, 7);
	puz8.solve().print_city();
	Puzzle puz9({ 0, 2, 3, 0, 2, 0, 0, 5, 0, 4, 5, 0, 4, 0, 0, 4, 2, 0, 0, 0, 6, 5, 2, 2, 2, 2, 4, 1 }, 7);
	puz9.solve().print_city();
	Puzzle puz11({ 0, 2, 3, 0, 2, 0, 0, 5, 0, 4, 5, 0, 4, 0, 0, 4, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0 }, 7);
	puz11.solve().print_city();
	Puzzle puz12({ 3, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 4, 7, 0, 0, 0, 2, 2, 3, 0, 0, 3, 0, 0, 0, 0 }, 7);
	puz12.solve().print_city();
	Puzzle puz13({ 0, 0, 0, 0, 5, 0, 4, 7, 0, 0, 0, 2, 2, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 5, 0 }, 7);
	puz13.solve().print_city();
	Puzzle puz14({ 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 4, 7, 0, 0, 0, 2, 2, 3 }, 7);
	puz14.solve().print_city(); 

	return 0;
}

