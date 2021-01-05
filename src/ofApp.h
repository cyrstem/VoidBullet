#pragma once

#include "ofMain.h"
#include "VoidE.h"
#include "ofxDOF.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		ofxDOF depth;
		ofEasyCam cam;
		VoidE vacio;
		int focalDist, focalRange;

};
