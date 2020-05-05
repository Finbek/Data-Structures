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

    // You may add private helper functions if you need them

public:
    BinarySearchTree() {
        // Constructor
	root=nullptr;
    }

    ~BinarySearchTree() {
        // Destructor
        clear();
	
    }

    TreeNode<keyT, valT>* insert(keyT key, valT val) {
        // Insert a new node to tree and return its pointer
        TreeNode<keyT, valT>* checker = search(key);
	if(checker==nullptr)
	{
	        if(root==nullptr)
		{
			root=new TreeNode<keyT, valT>(key, val,nullptr);
			return root;
		}
		else
		{
			TreeNode<keyT, valT>* cur = root; 
			while( cur)
			{	
				if(key < cur->key)
				{
					if(cur->left==nullptr)
					{	
			  TreeNode<keyT, valT>*  newNode= new TreeNode<keyT, valT>(key, val, cur);
						cur->left=newNode;
						return newNode;
					}
					else
						cur=cur->left;
				}
				else
				{
					if(cur->right==nullptr)
	                	        {
					TreeNode<keyT, valT> * newNode= new TreeNode<keyT, valT>(key, val, cur);
						cur->right=newNode;
						return newNode;
					}
					else
						cur= cur->right;
				}					
			}
		}
   	 }
	else
		return checker;
}

    bool remove(TreeNode<keyT, valT>* node) {
		
	// Remove 'node' and return true on success, false on fail
        // For example, if node is nullptr, do nothing and return false
	 TreeNode<keyT, valT> *cur =root;	
        TreeNode<keyT, valT> *par =nullptr;
	if(node && search(node->key))
	{
		while(cur)
		{
		if(cur->key==node->key){
			if(!cur->left && !cur->right)
			{	
				if(!par)
				{	
					delete cur;
					root=nullptr;	
				}
				else if(par->left==cur)
				{
					par->left=nullptr;
					delete cur;
				}
				else
				{
					par->right=nullptr;
					delete cur;
					
				}
						
			}
			else if(cur->left && !cur->right)
			{
				if(!par)
				{
					root=cur->left;
					cur->left->parent=nullptr;
					delete node;
					
				}
				else if(par->left->key==cur->key)
				{	
					cur->left->parent=par;
					par->left=cur->left;
					delete node;
					
				}
				else 
				{
					par->right=cur->left;
					cur->left->parent=par;
					delete node;
					
				}
			}
			else if(!cur->left && cur->right)
			{
				if(!par)
				{
					root=cur->right;
					cur->right->parent=nullptr;
					delete node;
					
				}
				else if(par->left->key==cur->key)
				{
					par->left=cur->right;
					cur->right->parent=par;
					delete node;
					
				}
				else
				{
					par->right=cur->right;
					cur->right->parent=par;
					delete node;
					
				}
			}
			else
			{
				TreeNode<keyT, valT>* suc = cur->right;
				while(suc->left){
					suc=suc->left;}
				keyT tempKey=suc->key;
				valT tempVal=suc->val;
				remove(suc);
				cur->key=tempKey;
				cur->val=tempVal;
			}
	
		return true;
		}
		else if(cur->key<node->key)
		{
			par=cur;
			cur=cur->right;
		}	
		else
		{
			par=cur;
			cur=cur->left;
		}
	} 
		return false;		
    }
}
    TreeNode<keyT, valT>* search(keyT key) const {
        // Find the node that has key 'key'
        // If not found, return nullptr
        TreeNode<keyT, valT> *cur = root;
	while( cur!=nullptr)
		if(key == cur->key)
			return cur;
		else if(key<cur->key)
			cur=cur->left;
		else
			cur=cur->right;
	return nullptr; 
    }

    void clear() {
        // Remove all nodes in the tree
        while(root)
		remove(root);
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
        // It prints all node info in two ways
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
