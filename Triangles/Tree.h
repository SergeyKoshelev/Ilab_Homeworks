#pragma once

#include <iostream>
#include <iterator>
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
			bool flag;
		
			Node(const Triangles::Triangle& tr) : elem(tr), left(nullptr), middle(nullptr), right(nullptr), flag(false) {};

			Node* create_node(Triangles::Triangle& elem);
			void push_left(Triangles::Triangle& new_elem);
			void push_right(Triangles::Triangle& new_elem);
			void push_middle(Triangles::Triangle& new_elem);
			void push_in(Triangles::Triangle& new_elem);
			void see_node(bool* arr);
			void free();
		};

	private:
		Node* head;

	public:
		Ternary_Tree() : head(nullptr) {};

		bool tr_push(Triangles::Triangle& elem);
		void undergo(bool* arr);
		void free();

	};

	//create new node and return pointer on it
	Ternary_Tree::Node* Ternary_Tree::Node::create_node(Triangles::Triangle& elem)
	{
		Node* nodeptr = new Node{ elem };
		return nodeptr;
	}

	//push new_elem in left branch
	void Ternary_Tree::Node::push_left(Triangles::Triangle& new_elem)
	{
		if (this->left == nullptr)
			this->left = create_node(new_elem);
		else
			this->left->push_in(new_elem);
	}

	//push new_elem in right branch
	void Ternary_Tree::Node::push_right(Triangles::Triangle& new_elem)
	{
		if (this->right == nullptr)
			this->right = create_node(new_elem);
		else
			this->right->push_in(new_elem);
	}

	//push new_elem in middle branch
	void Ternary_Tree::Node::push_middle(Triangles::Triangle& new_elem)
	{
		if (this->middle == nullptr)
			this->middle = create_node(new_elem);
		else
			this->middle->push_in(new_elem);
	}

	void Ternary_Tree::Node::free()
	{
		if (this->left != nullptr)
			this->left->free();
		if (this->right != nullptr)
			this->right->free();
		if (this->middle != nullptr)
			this->right->free();

		delete this;
	}

	//push new_elem due to its location
	void Ternary_Tree::Node::push_in(Triangles::Triangle& new_elem)
	{
		//under construction
		if (elem.in_left_side(new_elem))
			this->push_left(new_elem);
		else if (elem.in_right_side(new_elem))
			this->push_right(new_elem);
		else
		{
			this->push_left(new_elem);
			this->push_right(new_elem);
			this->push_middle(new_elem);
		}

	}

	void Ternary_Tree::Node::see_node(bool* arr)
	{
		if (this->left != nullptr)
			this->left->see_node(arr);
		if (this->right != nullptr)
			this->right->see_node(arr);
		if (this->middle != nullptr)
			this->right->see_node(arr);

		arr[this->elem.get_id()] = true;
	}

	//push triangle in tree
	bool Ternary_Tree::tr_push(Triangles::Triangle& elem)
	{
		//triangle is a point
		if (!elem.is_triangle())
			return false;

		//first triangle in tree
		if (this->head == nullptr)
		{
			this->head = new Node{ elem };
			return true;
		}

		//not first triangle
		this->head->push_in(elem);
		return true;
	}

	//lookup all tree
	void Ternary_Tree::undergo(bool* arr)
	{
		this->head->see_node(arr);
	}

	//delete tree
	void Ternary_Tree::free()
	{
		this->head->free();
	}
}