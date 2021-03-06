#include "node.h"

//i am pretty sure this constructor is useless, but i made it at some point for some reason and am now too scared to remove it
Node::Node(){
	g_cost = 1;
	h_cost = 0;
	my_parent = NULL;
}


Node::Node(Puzzle p, Node* parent, int h){
	my_puzzle = p;
	my_parent = parent;
	heuristic_type = h;

	//if parent is NULL, then is source node, so depth is 0, otherwise, add 1 to the depth of the parent
	if (parent != nullptr) {
		g_cost = parent->get_g() + 1;
	} else {
		g_cost = 0;
	}

	//calculate heuristic based off of initial user input h
	switch(h){
		case 1: 
			h_cost = my_puzzle.manhattan_distance();
			break;
		case 2: 
			h_cost = my_puzzle.misplaced_tile();
			break;
		default: h_cost = 0;
	}
}
	
//returns if puzzle is goal
bool Node::is_goal() const {
	return my_puzzle.is_goal();
}

std::list<Node> Node::get_children() const{
	return my_children;
}

Node* Node::get_parent() const{
	return my_parent;
}

Puzzle Node::get_puzzle() const{
	return my_puzzle;
}

int Node::get_g() const {
	return g_cost;
}
int Node::get_h() const {
	return h_cost;
}
int Node::get_heur_type() const {
	return heuristic_type;
}

//a node is "less than" another if the value of their total heuristic cost (g(n) + h(n)) is greater.
bool Node::operator<(const Node rhs){
	return (get_g() + get_h()) > (rhs.get_g()+rhs.get_h());
}

//a node equals another if their puzzles are the same
bool Node::operator==(const Node rhs){ 
	return my_puzzle == rhs.get_puzzle();	
}
Node Node::operator= (const Node rhs){
	my_puzzle = rhs.get_puzzle();
	my_parent = rhs.get_parent();
	my_children = rhs.get_children();
	h_cost = rhs.get_h();
	g_cost = rhs.get_g();
	heuristic_type = rhs.get_heur_type();
	return *this;
}

//create a child node with the blank tile moved up one (if possible)
void Node::add_move_up(){
	Puzzle up = my_puzzle.move_up();
	if (up != my_puzzle){	
		Node c (up, this, heuristic_type);
		my_children.push_back(c);			
	}
}

//create a child node with the blank tile moved down one (if possible)
void Node::add_move_down(){
	Puzzle down = my_puzzle.move_down();
	if (down != my_puzzle){
		Node c(down, this, heuristic_type);
		my_children.push_back(c);
	}
}

//create a child node with the blank tile moved left one (if possible)
void Node::add_move_left(){
	Puzzle left = my_puzzle.move_left();
	if (left != my_puzzle){
		Node c (left, this, heuristic_type); 
		my_children.push_back(c);
	}
}

//create a child node with the blank tile moved right one (if possible)
void Node::add_move_right(){
	Puzzle right = my_puzzle.move_right();
	if (right != my_puzzle){
		Node c(right, this, heuristic_type);
		my_children.push_back(c);
	}
}

//create all possible children
void Node::expand(){
	add_move_up();
	add_move_down();
	add_move_left();
	add_move_right();
}
void Node::print() const {

	my_puzzle.print();
	std::cout << "Heuristic: " << g_cost << " + " << h_cost << std::endl; 
}
