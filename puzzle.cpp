#include "Puzzle.h"
#include <cmath>
#include <iostream>

//this class will return heuristics 

//i don't know how to code what a disaster
Puzzle::Puzzle(){}

//create a puzzle with a vector of given values, there is no check for this, but it is how it is
Puzzle::Puzzle(std::vector<int>vals){
	int count = 0;
	for (int r = 0; r < my_size; r++){
		for (int c = 0; c < my_size; c++){
			matrix[r][c] = vals[count];
			count++;
		}
	}
}

//get value at some row and col
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

//calculate manhattan distance
int Puzzle::manhattan_distance()  const { //assume goal state (123456780)
	int count = 0; //distance
	int curr_val; //index of location
	int curr_x, curr_y; //the current row and column values
	int change_x, change_y; //what the row and column values should be (real val)

	for (int row = 0; row < my_size; row ++){
		for (int col = 0; col < my_size; col++){
			//not including the blank tile, calculate manhattan distance for each tile and add them up
			//the manhattan distance is the absolute value of change in row + change in col
			if (matrix[row][col] != 0){
				curr_val = matrix[row][col]-1; //get index
				curr_x = row;
				curr_y = col;
				change_x = curr_val / my_size; //real row value is curr_val divided by 3 (0,1,2 -- row 1; 3,4,5 -- row 2...)
				change_y = curr_val % my_size; //real col value is curr_val mod by 3 (0,3,6 -- col 1, 1,4,7 -- col 2...)
				count += abs(curr_x-change_x) + abs(curr_y-change_y); 

			}
		}
	}
	return count;
}

//return number of tiles for which value does not match index-1 (or more correctly index + 1 does not match the value), excluding blank tile #9
int Puzzle::misplaced_tile() const{
	int count = 0;
	int check = 1;
	for (int r = 0; r < my_size; r++){
		for (int c = 0; c < my_size; c++){
			if (check != 9){
				if (matrix[r][c] != check){
					count++;
				}
				check++;
			}
		}
	}
	return count;
}


//if possible (ie if not in top rop), move blank tile up
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

//if possible (ie if not in bottom rop), move blank tile down
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

//if possible (ie if not in leftmost col), move blank tile left
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


//if possible (ie if not in rightmost col), move blank tile right
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

//set every index value equal
Puzzle &Puzzle::operator= (const Puzzle& p){
	for (int row =0; row < my_size; row++){
		for (int col =0; col <my_size; col++){
			matrix[row][col] = p.get_val(row, col);
		}
	}
	return *this;
}

//if values are equal at every index, puzzles are equal
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

//manhattan distance of 0 indicates goal state, so if is not 0, is not goal state
bool Puzzle::is_goal() const {
	return (this->manhattan_distance() == 0);
}
