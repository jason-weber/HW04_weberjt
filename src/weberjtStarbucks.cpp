#include "weberjtStarbucks.h"


weberjtStarbucks::weberjtStarbucks(){
	root = new Node();
	divs = 25;//Number of parent nodes
}
void weberjtStarbucks::build(Entry* c, int n)
{
	Node* cur = root; //Create traversal node
	for(int i = 0; i < divs; i++){ // Loop to create parent list
		cur->insertAfter(cur, new Node());
	}


	for(int i = 0; i < n; i++){
		cur = root; //Reset cur to root at the beginning for each item in c
		int level = (int)ceil((c[i].x * divs)); //Find which parent to select

		for(int j = 1; j < level; j++){//Move to that parent
			cur = cur->next_;
		}

		if(cur->children_ == NULL){
			cur->addChild();//If the parent has no children, create one
			//Fill child data
			cur->children_->data->identifier = c[i].identifier;
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
			//If cur is the last node in the child list
			if(cur == stop->prev_){
				root->insertAfter(cur, new Node());//insert new node
				//Fill node with data
				cur->next_->data->identifier = c[i].identifier;
				cur->next_->data->x = c[i].x;
				cur->next_->data->y = c[i].y;
				cur = cur->next_;
			}
			cur = cur->next_;
		}while(cur != stop);//Stop once first child node is reached again
	}
}
Entry* weberjtStarbucks::getNearest(double x, double y)
{
	Node* pcur = root;
	Node* cur = root->children_; //Node for traversal
	double temp;//Placeholder for distance equation
	double nearest = 100.0;//Nearest initially set to absurdly large distance
	Entry* result;

	//Loop to correct parent node
	for(int i = 0; i < (int)ceil(x * divs)-5;i++){
		pcur = pcur->next_;
	}
	cur = pcur->children_;//Enter child list from parent node
	Node* stop = cur;
	result = cur->data;
	for(int i = 0; i < 10; i++){//accounts for boundary x values by checking more than one parent list
		cur = pcur->children_;
		stop = cur;
		do{
			temp = ((x-cur->data->x)*(x-cur->data->x)) + ((y-cur->data->y)*(y-cur->data->y));
			//If cur's data location is closer to x an y than the previous closest entry
			if(sqrt(temp) < nearest){
				result = cur->data;
				nearest = sqrt(temp);
			}
			cur = cur->next_;
		}while(cur != stop);//Stop when cur gets back to beginning of list
		pcur = pcur->next_;
	}
	return result;
}



