#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include "Triangles.h"

namespace Tree {

	class Ternary_Tree {

	public:
		class Node {

		public:
			Node* left;
			Node* middle;
			Node* right;
			Triangles::Triangle elem;
		
			Node(const Triangles::Triangle& tr) : elem(tr), left(nullptr), middle(nullptr), right(nullptr) {};

			Node* create_node(const Triangles::Triangle& elem);
			void push_left(const Triangles::Triangle& new_elem);
			void push_right(const Triangles::Triangle& new_elem);
			void push_middle(const Triangles::Triangle& new_elem);
			void push_in(const Triangles::Triangle& new_elem);
			void check(std::vector<bool>& arr);
			void check_branch(std::vector<bool>& arr, Ternary_Tree::Node* that);
			void free();
		};

	private:
		Node* head;

	public:
		Ternary_Tree() : head(nullptr) {};

		bool tr_push(const Triangles::Triangle& elem);
		void undergo(std::vector<bool>& arr);
		void free();

	};

	//create new node and return pointer on it
	Ternary_Tree::Node* Ternary_Tree::Node::create_node(const Triangles::Triangle& elem)
	{
		Node* nodeptr = new Node{ elem };
		return nodeptr;
	}

	//push new_elem in left branch
	void Ternary_Tree::Node::push_left(const Triangles::Triangle& new_elem)
	{
		if (left == nullptr)
			left = create_node(new_elem);
		else
			left->push_in(new_elem);
	}

	//push new_elem in right branch
	void Ternary_Tree::Node::push_right(const Triangles::Triangle& new_elem)
	{
		if (right == nullptr)
			right = create_node(new_elem);
		else
			right->push_in(new_elem);
	}

	//push new_elem in middle branch
	void Ternary_Tree::Node::push_middle(const Triangles::Triangle& new_elem)
	{
		if (middle == nullptr)
			middle = create_node(new_elem);
		else
			middle->push_in(new_elem);
	}

	//free node and its children
	void Ternary_Tree::Node::free()
	{
		if (left != nullptr)
		{
			left->free();
			delete left;
		}
		if (right != nullptr)
		{
			right->free();
			delete right;
		}
		if (middle != nullptr)
		{
			middle->free();
			delete middle;
		}
	}

	//push new_elem due to its location
	void Ternary_Tree::Node::push_in(const Triangles::Triangle& new_elem)
	{
		if (elem.in_left_side(new_elem))
			push_left(new_elem);
		else if (elem.in_right_side(new_elem))
			push_right(new_elem);
		else
		{
			push_left(new_elem);
			push_right(new_elem);
			push_middle(new_elem);
		}

	}

	//check if branch of this node have intersections
	void Ternary_Tree::Node::check(std::vector<bool>& arr)
	{
		if (left != nullptr)
			left->check(arr);
		if (right != nullptr)
			right->check(arr);
		if (middle != nullptr)
			middle->check_branch(arr, this);
	}

	//check intersections with THAT in branch
	void Ternary_Tree::Node::check_branch(std::vector<bool>& arr, Ternary_Tree::Node* that)
	{
		if (left != nullptr)
			left->check_branch(arr, that);
		if (right != nullptr)
			right->check_branch(arr, that);
		if (middle != nullptr)
			right->check_branch(arr, that);

		if (that->elem.intersection(elem))
		{
			arr[that->elem.get_id()] = true;
			arr[elem.get_id()] = true;
			//printing intersected triangles
			//that->elem.print_trian();
			//std::cout << "\tand\t" << std::endl;
			//elem.print_trian();
			//std::cout << std::endl;
		}
	}

	//push triangle in tree
	bool Ternary_Tree::tr_push(const Triangles::Triangle& elem)
	{
		//triangle is a point
		if (!elem.is_triangle())
			return false;

		//first triangle in tree
		if (head == nullptr)
		{
			head = new Node{ elem };
			return true;
		}

		//not first triangle
		head->push_in(elem);
		return true;
	}

	//lookup all tree
	void Ternary_Tree::undergo(std::vector<bool>& arr)
	{
		if (head != nullptr)
			head->check(arr);
	}

	//delete tree
	void Ternary_Tree::free()
	{
		if (head != nullptr)
			head->free();
	}
}