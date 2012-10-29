#include "Node.h"
#include <cstdlib>
#include <math.h>


class weberjtStarbucks : public Starbucks {
	public:
		weberjtStarbucks();
		virtual void weberjtStarbucks::build(Entry* c, int n);
		virtual Entry* weberjtStarbucks::getNearest(double x, double y);
		Node* root;
		int divs;


};
