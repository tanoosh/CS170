#include <iostream> 
#include <vector>
#include <queue>
#include "Puzzle.h"
#include "node.h"
#include <algorithm>

class Compare {
	public: 
		bool operator()(Node lhs, Node rhs){
			return lhs < rhs;
		}
};

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
	

	std::cout << "Welcome to the 8 puzzle solver. Enter '1' to use a default puzzle or '2' to create your own." << std::endl;
	std::cin >> puzzle_type;
	if (puzzle_type == 2){
		std::cout <<"Enter in your puzzle, using '0' to represent the blank and spaces to separate your values" << std::endl;

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
	}
	std::cout << "Enter how to solve (1 for A* Manhattan Distance, 2 for A* Misplaced Tile, 3 for Uniform Cost Search)" << std::endl;	

	std::cin >> heuristic;

	/****************Init Stuff*****************/
	Node source(puzzle, NULL, heuristic);
	std::vector <Puzzle> check;

	std::priority_queue<Node, std::vector<Node>, Compare> fringe;
	std::queue<Node> visited; 
	std::vector<Node> all;

	fringe.push(source);
	all.push_back(source);
	/*

	std::vector<int> v1 {1,2,3,4,5,6,7,8,0};
	std::vector<int> v2 {1,6,7,5,0,3,4,8,2};
	std::vector<int> v3 {1,2,3,0,4,6,7,5,8};
	std::vector<int> v4 {1,2,3,4,5,6,0,7,8};

	Puzzle p1(v1); Node n1(p1, NULL, 1);
	Puzzle p2(v2); Node n2(p2, NULL, 1);
	Puzzle p3(v3); Node n3(p3, NULL, 1);
	Puzzle p4(v4); Node n4(p4, NULL, 1);

	fringe.push(n1); fringe.push(n2); fringe.push(n3);

	while(!fringe.empty()){
		(fringe.top()).print();
		fringe.pop();
	}
	*/
	if (source.is_goal()){
		std::cout<<"initial success!" << std::endl;
	}
	/**************Search**************/
	while(!fringe.empty()){
		//pop min node
		Node temp = fringe.top();
		fringe.pop();
		temp.print();

		visited.push(temp); //add node to vistied list

		temp.expand();
		std::list<Node> expansion = temp.get_children();
		for (std::list<Node>::iterator it = expansion.begin(); it != expansion.end(); ++it){
			if (it->is_goal()){
				//success and traceback	
				std::cout<<"Success!" << std::endl;							
				//traceback
				return 1;
			}
			else {
				//if not in fringe or in visisted, add to fringe
				if (!contains(*it, all)){
					fringe.push(*it);
					all.push_back(*it);
				}
			}

		}
	}

	//failure

}


