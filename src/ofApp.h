#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		ofEasyCam cam;
		//void 
		ofSpherePrimitive vacio;
		float spinY;
		//Fire Rays;
		vector<glm::vec3>location_list;

		glm::vec3 noise_seed;
		vector<vector<glm::vec3>> log_list;
		vector<ofColor> color_list;
		vector<float> life_list;

		//Firelava\

		ofMesh face,frame;
		

};
