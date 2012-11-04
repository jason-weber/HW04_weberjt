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
	Font* font;
	weberjtStarbucks* var;
	Entry* nearest;
	static const int kAppWidth = 800;
	static const int kAppHeight = 600;
	bool colorMap;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void keyDown(KeyEvent event);
};


void HW04_weberjtApp::keyDown(KeyEvent event){
	if(event.KEY_e){
		colorMap = true;
	}

}
/*
* Prepares window size and prevents resizing
* @param settings The settings object to change
*/
void HW04_weberjtApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void HW04_weberjtApp::setup()
{
	var = new weberjtStarbucks();//My Starbucks object
	font = new Font("Ariel",30);
	ifstream file("Starbucks_2006.csv"); //Stream to read from csv
	int count = 0; //Counter for length of array and indexing
	string str; //String for each line in csv
	string x; //String that will be cast to double for x value of location
	string y; //String that will be cast to double for y value of location
	string description; //String to hold description of entry
	bool colorMap = false;
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

}

void HW04_weberjtApp::mouseDown( MouseEvent event )
{
	if(event.isLeftDown()){
		double x = abs((event.getX() - 50)/700.0);
		double y = abs(1 - ((event.getY()-50)/525.0));
		nearest = var->getNearest(x,y);
	}
}

void HW04_weberjtApp::update()
{
}

void HW04_weberjtApp::draw()
{
	gl::clear(Color8u(0,0,0));
	gl::color(Color8u(200,200,200));
	gl::drawSolidRect(Rectf(20,20,kAppWidth-20,kAppHeight-20));



	//var->root->children_->draw();
	Node* pcur = var->root;//Parent iterator node
	Node* ccur = pcur->children_;//Child iterator node
	for(int i = 0; i < var->divs; i++){
		do{
			if(ccur != NULL){
				ccur->draw();
				ccur = ccur->next_;
			}
			else{
				break;
			}
		}while(ccur != pcur->children_);
		pcur = pcur->next_;
		ccur = pcur->children_;
	}
}

CINDER_APP_BASIC( HW04_weberjtApp, RendererGl )
