#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
#include "VoidE.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);


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
