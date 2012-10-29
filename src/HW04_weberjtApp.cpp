#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <iostream>
#include <fstream>
#include "weberjtStarbucks.h"
#include <vector>
#include "stdlib.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_weberjtApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04_weberjtApp::setup()
{
	weberjtStarbucks* var = new weberjtStarbucks();
	
	ifstream file("Starbucks_2006.csv");
	int count = 0;
	string str;
	string x;
	string y;
	string description;
	while(file.good()){
		std::getline(file,str,'\r');
		count++;	
	}
	file.close();
	Entry* c = new Entry[count];
	count = 0;
	file.open("Starbucks_2006.csv");
	while(file.good()){
		std::getline(file,str,'\r');
		int index = str.find(',');
		description = str.substr(0,index);
		x = str.substr(index+1,str.length()-1);
		index = x.find(',');
		y = x.substr(index + 1, str.rfind(','));
		x = x.substr(0,index);
		double xVal = strtod(x.c_str(), NULL);
		double yVal = strtod(y.c_str(),NULL);
		c[count].identifier = description;
		c[count].x = xVal;
		c[count].y = yVal;
		count++;
	}
	file.close();
	var->build(c, count);
	Entry* testX = var->getNearest(0.018679855,0.918968); //Location off by only x, Should return Aberdeen Washington 98520 Safeway
	Entry* testY = var->getNearest(0.55, 0.55);//Location off by only y, Should return Akron Ohio Chapel Hill Mall Kiosk
	Entry* testRand = var->getNearest(0.158793726,0.8);//Should give Yuma Arizona 85365 16th Street - I-8  Yuma
	int h = 0;

	
}

void HW04_weberjtApp::mouseDown( MouseEvent event )
{
}

void HW04_weberjtApp::update()
{
}

void HW04_weberjtApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_weberjtApp, RendererGl )
