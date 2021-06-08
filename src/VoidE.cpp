#include "VoidE.h"

void VoidE::init(){
     ofDisableArbTex();
	 ofEnableDepthTest();
	 ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);
	 ofEnableAlphaBlending();
	 ofEnableAntiAliasing();
    ofLoadImage(mtex,"tex.jpg");

    blackShader.load("Eye");
	//fireRing.load("Fire");


    //void sphere
    vacio.setPosition(0,0,0);
    vacio.setRadius(200);
    vacio.setResolution(120);
    vacio.setMode(OF_PRIMITIVE_TRIANGLES);
    spinY = 0.0;

    //fireRays
    ofSetLineWidth(3);
    noise_seed = glm::vec3(ofRandom(3000),ofRandom(3000),ofRandom(3000));
    ofIcoSpherePrimitive ico_sphere = ofIcoSpherePrimitive(201,3);
    vector<ofMeshFace> triangles = ico_sphere.getMesh().getUniqueFaces();
    for (int i = 0; i < triangles.size(); i++)
    {
        ofPoint average = (triangles[i].getVertex(0) +triangles[i].getVertex(1) + triangles[i].getVertex(2))/3;
        location_list.push_back(average);
    }
    time =ofGetElapsedTimef();
	
	ofFboSettings f;
	f.width =300;
	f.height =300;
	f.internalformat =GL_RGBA;
	f.maxFilter =32;
	firemT.allocate(f);


		lightsColor =glm::vec3 (255.,0.0,0.0);
		meshCol = glm::vec3 (255.255,0.0,0.0);
		meshSpecCol = glm::vec3 (255.0,0.0,1.0);
		ambientCol =glm::vec3 (255.,255.,255.);
		intesity = 0.003;
}

void VoidE::update(){
     spinY+=0.23;
    //fireRays
    int radius = 1;
        while (log_list.size() <550)        
        {
            int location_index = ofRandom(location_list.size());
            vector<glm::vec3> log;
            log.push_back(location_list[location_index]);
            log_list.push_back(log);
            color_list.push_back(ofColor(ofRandom(255,1)));
            life_list.push_back(190);
            
        }

        for (int i = this->log_list.size()-1; i >= 0; i--) {
 
		this->life_list[i] -= 1;
		if (this->life_list[i] < 0) {
 
			this->log_list.erase(this->log_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
 
			continue;
		}
 
		auto x = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0165, this->noise_seed.x + 360 * 0.005)), 0, 1, -15, 15);
		auto y = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0165, this->noise_seed.y + 360 * 0.005)), 0, 1, -15, 15);
		auto z = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0165, this->noise_seed.z + 360 * 0.005)), 0, 1, -15, 15);
		this->log_list[i].push_back(this->log_list[i].back() + glm::vec3(x, y, z));
	}
        //firelava

        face.clear();

        ofSeedRandom(139);
        float phi_deg_step =1;
        float theta_deg_step =1;
        for (float radius = 110; radius <= 250; radius += 100) {
 
		auto noise_seed = ofRandom(1500);
		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {
 
			for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {
 
				auto noise_location = glm::vec3(
					sin(theta_deg * DEG_TO_RAD) * cos(phi_deg * DEG_TO_RAD),
					sin(theta_deg * DEG_TO_RAD) * sin(phi_deg * DEG_TO_RAD),
					cos(theta_deg * DEG_TO_RAD));
				auto noise_value = ofNoise(glm::vec4(noise_location, noise_seed + ofGetFrameNum() * 0.021));
 
				if (noise_value < 0.5) { continue; }
 
				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;
 
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
 
				this->face.addVertices(vertices);
			
 
				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);
 
			
			}
		}
	}

	firemT.begin();
	ofClear(0);
	firemT.end();


    lightpos = glm::vec3(cos(ofGetElapsedTimef()/1.18f) * 150 * 0 + 0,
     sin(ofGetElapsedTimef()/1.8f) * 150 * 2 + 0,
     -cos(ofGetElapsedTimef()/1.8f) * 150 * 2 + 0);

    light.setPosition(lightpos);

}

void VoidE::draw(){
     ofRotateYDeg(spinY);

 //shader

        blackShader.begin();
        blackShader.setUniformTexture("tex0",mtex,0);
    	blackShader.setUniform1f("time",time);
		blackShader.setUniform3f("lightPos",lightpos);
        blackShader.setUniform3f("lightCol",lightsColor);
        blackShader.setUniform1f("intensity",intesity);
        blackShader.setUniform3f("meshSpecCol", meshSpecCol);
	    blackShader.setUniform3f("meshCol", meshCol);
        blackShader.setUniform3f("ambientCol", ambientCol);	
        	vacio.draw(); 
        blackShader.end();

	fireRing.begin();
		fireRing.setUniform1f("time",ofGetElapsedTimef());
	 	fireRing.setUniform2f("resolution",300,300);
        for (int i = 0; i < this->log_list.size(); i++) {
 
		ofSetColor(this->color_list[i]);
		ofFill();
		ofDrawSphere(this->log_list[i].front(), 1);
 
		//auto alpha = this->life_list[i] > 360 ? 255 : ofMap(this->life_list[i], 0, 360, 0, 255);
		//ofSetColor(this->color_list[i], alpha);
 
		ofNoFill();
		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	//
	fireRing.end();


// ///check how to render fbo to a texture or image and thenn pass to the shaderr
// 	fireRing.begin();
// 		fireRing.setUniform1f("time",ofGetElapsedTimef());
// 		fireRing.setUniform2f("resolution",300,300);
// 		fireRing.setUniform1f("blurAmnt",0.3);
// 		fireRing.setUniformTexture("tex0",firemT.getTexture(),0);

// 			this->face.draw();
// 	fireRing.end();



	light.draw();


	// fboTexture.begin();
	// 	fireRing.begin();
	// 	//ofPopStyle();
	// 	//ofFill();
	
	// 	fireRing.setUniform1f("time",ofGetElapsedTimef());
	// 	fireRing.setUniform2f("resolution",300,300);
	// 		ofDrawRectangle(0,0,300,300);
	// 	fireRing.end();
	// 	//ofPushStyle();
    // fboTexture.end();
	// // fireRing.draw(0,0);

	// 		fboTexture.getTextureReference().bind();
	// 			this->face.draw();
	// 		fboTexture.getTextureReference().unbind();
	// //fireRing.end();
		
}

