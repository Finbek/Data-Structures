#ifndef LIST_H
#define LIST_H
#include <iostream>
template <class T>
class Node {
    /*
     * This is a wrapper around 'item', the element we want to store.
     *
     * Template is used to make it work regardless of what type 'T' is.
     * Refer to http://www.cplusplus.com/doc/oldtutorial/templates/ for more info.
     */
public:
    Node* prev;
    Node* next;
    T item;

    Node(T val = T()) {
        prev = nullptr;
        next = nullptr;
        item = val;
    }
};

// Part 1: Implement a doubly linked list.
template <class T>
class LinkedList {
    // Dummy nodes
    Node<T>* head;
    Node<T>* tail;
    int LinkedList_size;

    // You may add member variables you need.

public:
    LinkedList() {
        // Constructor.
        head = new Node<T>;
        tail = new Node<T>;
	
        head->prev = nullptr;
        head->next = tail;

        tail->prev = head;
        tail->next = nullptr;
	
	LinkedList_size=0;
        // Initialize your variables if you added them.
    }

    ~LinkedList() {
        // Destructor.
        clear();
        delete head;
        delete tail;

        // Release yours if you added them.
    }

    // Implement member functions below.
    // Remember: member functions can call each other.

    int size() {
        // Return the number of elements in list
	return this->LinkedList_size;

    }

    bool empty() {
	if(LinkedList_size==0)
		return true;
	else
		return false;
        // Return true if no elements are in list and false otherwise.
    }

    T& front() {
        // Return the front (first) element.
        // Note the return type.
        // It is REFERENCE (not value) of the ITEM (not Node).
        if(this->LinkedList_size>0)
	{
		T&ref = this->head->next->item;
		return  ref;
	}
    }

    T& back() {
	if(this->LinkedList_size>0)
	{
		T& ref = this->tail->prev->item;
		return  ref;
	}
        // Return the back (last) element.
        // Same note as in front().
    }

    void insert(Node<T>* node_before, T val) {
        // Create a node with val. Insert it after node_before.
        // i.e. node_before -> new node -> node_before->next
       	Node<T>* NewNode=new Node<T>(val);
	if(node_before==this->tail)
	{	
		return;
	}
	Node<T>* node_after = node_before->next;
	NewNode->next=node_after;
	NewNode->prev=node_before;
	node_before->next=NewNode;
	node_after->prev=NewNode;
	this->LinkedList_size+=1;
    }

    void erase(Node<T>* target) {
	
	if(this->LinkedList_size==0 || target==this->head || target==this->tail)
	{
		return;
	}

	Node<T>* node_after=target->next;
	Node<T>* node_before=target->prev;
	node_after->prev=node_before;
	node_before->next=node_after;
	LinkedList_size-=1;
	delete target;
        // Remove target node from the list.
    }

    void push_front(T val) {
        // Create a node with val. Add it to the front of the list.
	insert(this->head,  val);
    }

    void pop_front() {
        // Remove the front node.
        erase(this->head->next);
	
    }

    void push_back(T val) {
        // Create a node with val. Add it to the back of the list.
        insert(this->tail->prev, val);
    }

    void pop_back() {
        // Remove the back node.
        erase(this->tail->prev);
    }

    void clear() {
        // Remove all nodes in list.
      	while(this->LinkedList_size!=0)
	{	
		pop_front();
	}  
    }

    Node<T>* find(T val) {
        // Return the pointer of first node with the item val.
        Node<T>*  Node = this->head;
	while(Node)
	{
		if(Node->item==val)
		{
			return Node;
		}
		Node=Node->next;
	}
    }

    // You may add other member functions.
};

#endif
