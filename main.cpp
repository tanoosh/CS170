#include <iostream> 
#include <fstream>
#include <chrono>
#include <cmath>
#include <time.h>
#include <vector>
#include <queue>
#include "Puzzle.h"
#include "node.h"
#include <algorithm>

//did not know how to make a priority queue for objects, idea taken from https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
class Compare {
	public: 
		bool operator()(Node lhs, Node rhs){
			return lhs < rhs;
		}
};

//check for duplicate nodes (uses "master" vector that contains every node with a distinct puzzle) 
bool contains(Node node, std::vector<Node> nodes){
	for (Node n : nodes){
		if (node == n){
			return true;
		}
	}
	return false;
}


int main(){
	int puzzle_type;
	std::vector <int> vals;
	int temp;
	Puzzle puzzle;
	int heuristic;
	

	std::cout << "Welcome to the 8 puzzle solver" << std::endl;
	std::cout <<"Enter in your puzzle, using '0' to represent the blank and spaces to separate your values" << std::endl;

	//get user input, create puzzle row by row
	for (int row = 0; row < puzzle.get_size(); row++) {

		std::cout << "Enter row " << row+1 << ": ";

		for (int i = 0; i < puzzle.get_size(); i++){
			std::cin >> temp;
			vals.push_back(temp);
		}

		for (int col = 0; col <puzzle.get_size(); col++){
			puzzle.set_val(vals.at(col), row, col);
		}

		vals.clear();

	}
	std::cout << "Enter how to solve (1 for A* Manhattan Distance, 2 for A* Misplaced Tile, 3 for Uniform Cost Search)" << std::endl;	

	std::cin >> heuristic;

	/****************Init Stuff*****************/
	Node source(puzzle, NULL, heuristic);
	std::vector <Puzzle> check;

	int max_queue_size = 1;
	int num_nodes_expanded = 0;
	int depth;
	clock_t t;

	//create fringe and visited list (also a vector of all visited puzzles bc i don't know how else to check)
	std::priority_queue<Node, std::vector<Node>, Compare> fringe;
	std::queue<Node> visited; 
	std::vector<Node> all;

	//add source node to fringe
	fringe.push(source);
	all.push_back(source);
	
	//check if source is already at goal
	if (source.is_goal()){
		std::cout<< "This is already the goal state, silly billy" << std::endl;
		return 1;
	}

	/**************Search**************/
	t = clock(); //start clock? i think?
	auto begin = std::chrono::high_resolution_clock::now();	//start another clock??? idk how this works

	//while fringe is not empty & less than 5 minutes has elapsed (i do not have the patience to run this program for longer than that) 
	//the 5 minutes elapsed thing never worked out and i just manually ended it every time. again, i don't know how the clock works
	while(!fringe.empty()  &&  ((float)t/CLOCKS_PER_SEC)<300) {
		//pop min node
		Node temp = fringe.top();
		fringe.pop();

		//some traceback output
		std::cout << "The best node to expand: \n";
		temp.print();

		visited.push(temp); //add node to vistied list

		//expand min node
		temp.expand();
		num_nodes_expanded++;	
		std::list<Node> expansion = temp.get_children();

		for (std::list<Node>::iterator it = expansion.begin(); it != expansion.end(); ++it){
			//if one of the children is goal, success!
			if (it->is_goal()){ 
				auto end = std::chrono::high_resolution_clock::now();
				t = clock() - t;

				//some data output
				std::cout<<"Success!" << std::endl;							
				depth = it->get_g();	
				std::cout <<"Depth: " << depth << ", Max Queue Size: " << max_queue_size << ", Number of Nodes Expanded: " << num_nodes_expanded << std::endl;
				std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << " ns, " << (float)t/CLOCKS_PER_SEC << " s" << std::endl;
				return 1;//end program
			}
			else {
				//if not in fringe or in visisted, add to fringe
				if (!contains(*it, all)){
					fringe.push(*it);
					all.push_back(*it);
				}
			}

		}
		//when i did not make this an int, i got an error, not sure why, too lazy to figure out
		int k = fringe.size();
		max_queue_size = std::max(k, max_queue_size);
	}

	std::cout << "Could not find a solution, sorry :((" << std::endl;
	std::cout <<"Depth: " << depth << ", Max Queue Size: " << max_queue_size << ", Number of Nodes Expanded: " << num_nodes_expanded << std::endl;
	std::cout <<"Time: " << ((float)t)/CLOCKS_PER_SEC << std::endl;
	return -1;
				
}


