#ifndef _PUZZLE_H__
#define _PUZZLE_H__

#include <vector>

class Puzzle {
private:
	int matrix[3][3];
	const int my_size = 3;

public:
	Puzzle();
	Puzzle(std::vector<int> v);
	int get_val(int row, int col) const;
	void set_val(int val, int row, int col);
	int get_row(int val) const;
	int get_col(int val) const;
	int get_size() const {return my_size;};
	void print() const;

	int manhattan_distance() const;
	int misplaced_tile() const;
	bool is_goal() const;

	Puzzle& operator=(const Puzzle& p);
	bool operator==(const Puzzle& rhs);
	bool operator!=(const Puzzle& rhs);

	
	Puzzle move_up();
	Puzzle move_down();
	Puzzle move_left();
	Puzzle move_right();

};

#endif
