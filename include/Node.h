#include "Starbucks.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"



class Node{

	public:
		Node* next_; //next node in linked list
		Node* prev_; //previous node in linked list
		Node* children_;//children head node of children linked list
		Entry* data;
		ci::Color8u color;
		double stretchX;
		double stretchY;
		double offsetX;
		double offsetY;
		int n;

		
		//Constructors
		Node();
		Node(Node* node);
		Node(Entry* entry);

		void insertAfter(Node* posNode, Node* insNode); //insert node after given node
		void addChild();//adds child to node
		void draw();
		


};