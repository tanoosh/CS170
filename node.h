#ifndef __NODE_H__
#define __NODE_H__

#include <list>
#include "puzzle.h"
#include <iterator>
#include <iostream>

class Node {
	private:
		Puzzle my_puzzle;
		Node* my_parent;
		std::list <Node> my_children;
		int g_cost; //weight
		int h_cost; //heuristic
		int heuristic_type;

	public:
		Node();
		Node(Puzzle p, Node* parent, int heuristic);

		void expand(); //create children

		std::list<Node> get_children() const;
		int get_g() const;
		int get_h() const;
		int get_heur_type() const;
		Node* get_parent() const;
		Puzzle get_puzzle() const;

		void add_move_up();
		void add_move_down();
		void add_move_left();
		void add_move_right();

		bool is_goal() const;
		void print() const;

		bool operator<(const Node rhs);
		bool operator==(const Node rhs);
		Node operator=(const Node rhs);

};

#endif
