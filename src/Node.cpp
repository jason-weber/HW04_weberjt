#include "Node.h"


/*
* Default Node constructor
*/
Node::Node()
{
	next_ = prev_ = this; //Sets up first node to create circular linked list
	data = new Entry();
	children_ = NULL; //Node start with no children
}

/*
* Constructs Node with given points and color
* @param v1 Top left vertex of rectangle
* @param v2 Bottom right vertex of rectangle
* @param c Color the rectangle should be drawn
*/
Node::Node(Entry* entry){
	next_ = prev_ = this; //Sets up first node to create circular linked list
	this->data = entry;
	children_ = NULL; //Node start with no children
}

/*
* Inserts a node after the given node
* @param posNode Where the node should be placed after
* @param insNode Node to insert
*/
void Node::insertAfter(Node* posNode, Node* insNode)
{
	//assigns variables in next_ direction
	insNode->next_ = posNode->next_;
	posNode->next_ = insNode;

	//assigns variables in prev_ direction
	insNode->next_->prev_ = insNode;
	insNode->prev_ = posNode;
}

/*
* Adds a child to a node
* @param v1 Top left vertex of child rectangle
* @param v2 Bottom right vertex of child rectangle
* @param c Color to draw child
*/
void Node::addChild()
{
	if(children_ == NULL)
	{
		children_ = new Node();
	}
	else{
		insertAfter(children_, new Node());
	}
}
