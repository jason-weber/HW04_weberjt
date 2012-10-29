#include "Node.h"


/*
* Default Node constructor
*/
Node::Node()
{
	next_ = prev_ = this; //Sets up first node to create circular linked list
	data = new Entry();//Create blank entry
	children_ = NULL; //Node start with no children
}

/*
* Constructs Node with given points and color
* @param entry Entry data to put into node
* 
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
