#pragma once

#include "ofMain.h"
#include "VoidE.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

		ofEasyCam cam;
		VoidE vacio;

};
