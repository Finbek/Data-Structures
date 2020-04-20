#ifndef BST_H
#define BST_H

#include <iostream>

template <typename keyT, typename valT>
struct TreeNode {
	keyT key;
	valT val;
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;

	TreeNode(keyT _key = keyT(), valT _val = valT(), TreeNode* _parent = nullptr) {
		key = _key;
		val = _val;
		parent = _parent;
		left = nullptr;
		right = nullptr;
	}
};

template <typename keyT, typename valT>
class BinarySearchTree {
	TreeNode<keyT, valT>* root;
	// You may add additional private member variables and functions

public:
	BinarySearchTree() {
		// Constructor
	}

	~BinarySearchTree() {
		// Destructor
	}

	TreeNode<keyT, valT>* insert(keyT key, valT val) {
		// Insert a new node to tree
	}

	bool remove (TreeNode<keyT, valT>* node) {
		// Remove 'node' and return true on success, false on fail
		// For example, if node is nullptr, do nothing and return false
	}

	TreeNode<keyT, valT>* search(keyT key) const {
		// Find the node that has key 'key'
		// If not found, return nullptr
	}

	void clear() {
		// Remove all nodes in the tree
	}

	void print_in(TreeNode<keyT, valT>* current) const {
		if (current != nullptr) {
			print_in(current->left);
			std::cout << current->key << ' ' << std::flush;
			print_in(current->right);
		}
	}

	void print_pre(TreeNode<keyT, valT>* current) const {
		if (current != nullptr) {
			std::cout << current->key << ' ';
			print_pre(current->left);
			print_pre(current->right);
		}
	}

	void print_post(TreeNode<keyT, valT>* current) const {
		if (current != nullptr) {
			print_post(current->left);
			print_post(current->right);
			std::cout << current->key << ' ';
		}
	}

	void print() const {
		// It prints all node info in three different ways
		// to make sure all nodes are in the right place
		print_in(this->root);
		std::cout << std::endl;

		print_pre(this->root);
		std::cout << std::endl;

		print_post(this->root);
		std::cout << std::endl;
	}
};

#endif
