#pragma once 

#include "ofMain.h"

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

};