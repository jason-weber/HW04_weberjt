#include "weberjtStarbucks.h"


weberjtStarbucks::weberjtStarbucks(){
	root = new Node();
	divs = 50;
}
void weberjtStarbucks::build(Entry* c, int n)
{
	Node* cur = root; //Create traversal node
	for(int i = 0; i < divs; i++){ // Loop to create parent list
		cur->insertAfter(cur, new Node());
	}


	for(int i = 0; i < n; i++){
		cur = root; //Reset cur to root at the beginning for each item in c
		int level = (int)(c[i].x*divs); //Find which parent to select

		for(int j = 0; j < level; j++){//Move to that parent
			cur = cur->next_;
		}

		if(cur->children_ == NULL){
			cur->addChild();//If the parent has no children, create one
			cur->children_->data->identifier = c[i].identifier;//Fill child data
			cur->children_->data->x = c[i].x;
			cur->children_->data->y = c[i].y;
			cur = cur->next_;
			continue;
		}
		cur = cur->children_;//Move cur into child list of parent node
		Node* stop = cur;//Variable set to the first child node
		do{
			//checks for repeat locations while traversing the list
			if((abs(c[i].x - cur->data->x) <= 0.00001) && (abs(c[i].y - cur->data->y) < 0.00001) && (cur != cur->next_)){
				break;
			}
			if(cur == stop->prev_){
				root->insertAfter(cur, new Node());
				cur->next_->data->identifier = c[i].identifier;
				cur->next_->data->x = c[i].x;
				cur->next_->data->y = c[i].y;
			}
			cur = cur->next_;
		}while(cur != stop);//Stop once first child node is reached again
	}
}
Entry* weberjtStarbucks::getNearest(double x, double y)
{
	Node* cur = root;
	double temp;
	double nearest = 100.0;
	Entry* result;
	for(int i = 0; i < (int)(x*divs);i++){
		cur= cur->next_;
	}
	cur = cur->children_;
	Node* stop = cur;
	result = cur->data;
	do{
		temp = ((x-cur->data->x)*(x-cur->data->x)) + ((y-cur->data->y)*(y-cur->data->y));
		if(sqrt(temp) < nearest){
			result = cur->data;
			nearest = sqrt(temp);
		}
		cur = cur->next_;
	}while(cur != stop);
	return result;
}



