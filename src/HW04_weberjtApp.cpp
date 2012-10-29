#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <iostream>
#include <fstream>
#include "weberjtStarbucks.h"
#include <vector>
#include "stdlib.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_weberjtApp : public AppBasic {
  public:
	Entry* testX;
	Entry* testY;
	Entry* testRand;
	Font* font;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04_weberjtApp::setup()
{
	weberjtStarbucks* var = new weberjtStarbucks();//My Starbucks object
	font = new Font("Ariel",30);
	ifstream file("Starbucks_2006.csv"); //Stream to read from csv
	int count = 0; //Counter for length of array and indexing
	string str; //String for each line in csv
	string x; //String that will be cast to double for x value of location
	string y; //String that will be cast to double for y value of location
	string description; //String to hold description of entry
	
	while(file.good()){//While stream gives no errors
		//Count how many items in list
		std::getline(file,str,'\r');
		count++;	
	}
	file.close();//Close so file can be reopened and reread
	Entry* c = new Entry[count];//Entry array to pass to build
	count = 0; //reset count
	file.open("Starbucks_2006.csv"); //Reopen csv so it can be read again
	
	while(file.good()){
		std::getline(file,str,'\r');
		int index = str.find(','); //Index of ',' in str

		description = str.substr(0,index); 
		x = str.substr(index+1,str.length()-1);
		index = x.find(','); //Index of ',' in x
		y = x.substr(index + 1, str.rfind(','));//Use that index to find y string
		x = x.substr(0,index);

		//convert location strings to doubles
		double xVal = strtod(x.c_str(), NULL);
		double yVal = strtod(y.c_str(),NULL);

		//Set values of Entry at count 
		c[count].identifier = description;
		c[count].x = xVal;
		c[count].y = yVal;
		count++;
	}
	file.close();

	//Build method
	var->build(c, count);

	//Tests for getNearest
	testX = var->getNearest(0.018679855,0.918968);
	testY = var->getNearest(0.55, 0.55);
	testRand = var->getNearest(0.158793726,0.8); 	

}

void HW04_weberjtApp::mouseDown( MouseEvent event )
{
}

void HW04_weberjtApp::update()
{
}

void HW04_weberjtApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	//Draw test cases to cinder window because that's how I roll
	gl::drawString(testX->identifier, Vec2f(50.0,50.0),Color8u(255,255,255),*font);
	gl::drawString(testY->identifier, Vec2f(50.0,100.0),Color8u(255,255,255),*font);
	gl::drawString(testRand->identifier, Vec2f(50.0,150.0),Color8u(255,255,255),*font);
}

CINDER_APP_BASIC( HW04_weberjtApp, RendererGl )
