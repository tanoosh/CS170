#include "Puzzle.h"
#include <cmath>
#include <iostream>

//this class will return heuristics

Puzzle::Puzzle(){}

Puzzle::Puzzle(std::vector<int>vals){
	int count = 0;
	for (int r = 0; r < my_size; r++){
		for (int c = 0; c < my_size; c++){
			matrix[r][c] = vals[count];
			count++;
		}
	}
}

int Puzzle::get_val  (int row, int col) const {
	return matrix[row][col];
}
void Puzzle::set_val(int val, int row, int col){
	matrix[row][col] = val;

}

int Puzzle::get_row  (int val) const{
	for (int row = 0; row < my_size; row++){
		for (int col = 0; col < my_size; col++){
			if (matrix[row][col] == val){
				return row;
			}
		}
	}
	std::cout << "Error" << std::endl;
	return -1; 
}

int Puzzle::get_col  (int val) const {
	for (int row = 0; row < my_size; row++){
		for (int col = 0; col < my_size; col++){
			if (matrix[row][col] == val){
				return col;
			}
		}
	}
	std::cout << "Error" << std::endl;
	return -1; 
}

int Puzzle::manhattan_distance()  const { //assume goal state
	int count = 0; //distance
	int curr_val;
	int curr_x, curr_y;
	int change_x, change_y;

	for (int row = 0; row < my_size; row ++){
//std::cout << "Row: " << row << std::endl;
		for (int col = 0; col < my_size; col++){
			if (matrix[row][col] != 0){
				curr_val = matrix[row][col]-1;
				curr_x = row;
				curr_y = col;
				change_x = curr_val / my_size;
				change_y = curr_val % my_size;
				count += abs(curr_x-change_x) + abs(curr_y-change_y);

//std::cout << "\t" << matrix[row][col] << " moves " << (abs(curr_x-change_x) + abs(curr_y-change_y)) << std::endl;
			}
		}
	}
//std::cout << "Count: " << count << std::endl;
	return count;
}

int Puzzle::misplaced_tile() const{
	int count = 0;
	int check = 1;

	for (int r = 0; r < my_size; r++){
		for (int c = 0; c < my_size; c++){
			if (check != 9){
//std::cout << matrix[r][c] << " vs " << check << ", " << count << std::endl;
				if (matrix[r][c] != check){
					count++;
				}
				check++;
			}
		}
	}
	return count;
}


Puzzle Puzzle::move_up(){
	Puzzle p = *this;
	int temp;

	int r = get_row(0);
	int c = get_col(0);

	if (r != 0){
		temp = p.get_val(r-1, c);
		p.set_val(0, r-1, c);
		p.set_val(temp, r, c);
	}
		return p;
	
}

Puzzle Puzzle::move_down(){
	Puzzle p = *this;
	int temp;

	int r = get_row(0);
	int c = get_col(0);

	if (r != 2){
		temp = p.get_val(r+1, c);
		p.set_val(0, r+1, c);
		p.set_val(temp, r, c);
	}
		return p;
	
}

Puzzle Puzzle::move_left(){
	Puzzle p = *this;
	int temp;

	int r = get_row(0);
	int c = get_col(0);

	if (c != 0){
		temp = p.get_val(r,c-1);
		p.set_val(0, r, c-1);
		p.set_val(temp, r, c);
	}
		return p;
}


Puzzle Puzzle::move_right(){
	Puzzle p = *this;
	int temp;

	int r = get_row(0);
	int c = get_col(0);

	if (c != 2){
		temp = p.get_val(r, c+1);
		p.set_val(0, r, c+1);
		p.set_val(temp, r, c);
	}
		return p;
	
}

Puzzle &Puzzle::operator= (const Puzzle& p){
	for (int row =0; row < my_size; row++){
		for (int col =0; col <my_size; col++){
			matrix[row][col] = p.get_val(row, col);
		}
	}
	return *this;
}

bool Puzzle::operator== (const Puzzle& rhs){
	for (int r = 0; r < my_size; r++){
		for (int c = 0; c < my_size; c++){
			if (matrix[r][c] != rhs.get_val(r,c)){
				return false;
			}
		}
	}
	return true;
}

bool Puzzle::operator!= (const Puzzle& rhs){
	if (*this == rhs){
		return false;
	}
	else {
		return true;
	}
}


void Puzzle::print() const {
	for (int r = 0; r<my_size; r++){
		std::cout << "[";
		for (int c = 0; c<my_size; c++){
			std::cout << matrix[r][c] << ", "; 	
		}
		std::cout << "]" << std::endl;
	}
}

/*
friend std::ostream& operator<<(std::ostream& os, Puzzle const& p){
	std::string s;
	for (int r = 0; r<p.my_size; r++){
		s << "[";
		for (int c = 0; c<p.my_size; c++){
			s<< p.matrix[r][c] << ", "; 	
		}
		s << "] \n"; 
	}
	return os << s;
}
*/

bool Puzzle::is_goal() const {
	return (this->manhattan_distance() == 0);
}
