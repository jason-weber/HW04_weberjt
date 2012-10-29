#include "Starbucks.h"

class Node{

	public:
		Node* next_; //next node in linked list
		Node* prev_; //previous node in linked list
		Node* children_;//children head node of children linked list
		Entry* data;

		
		//Constructors
		Node();
		Node(Node* node);
		Node(Entry* entry);

		void insertAfter(Node* posNode, Node* insNode); //insert node after given node
		void addChild();//adds child to node

		


};