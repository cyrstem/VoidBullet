#pragma once 

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
class VoidE{
    public:
        void init();
        void update();
        void draw();

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

		ofMesh face;
		
        //shader 
        ofxAutoReloadedShader blackShader, fireRing;
        ofTexture mtex;
        float time;
		ofFbo firemT;


		//lights
			ofLight light, spot;
			glm::vec3 lightpos;
			glm::vec3 lightsColor;
			glm::vec3 meshSpecCol;
			glm::vec3 meshCol;
			glm::vec3 ambientCol;
			float intesity;
			float blurAmt;

};