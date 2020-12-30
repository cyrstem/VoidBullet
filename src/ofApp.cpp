#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("VO!D");
    ofSetBackgroundColor(ofColor::black);
    ofSetFrameRate(60);
    ofEnableDepthTest();
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

    //firelava

    frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

}

//--------------------------------------------------------------
void ofApp::update(){
    spinY+=0.23;
    //fireRays
    int radius = 1;
        while (log_list.size() <550)        
        {
            int location_index = ofRandom(location_list.size());
            vector<glm::vec3> log;
            log.push_back(location_list[location_index]);
            log_list.push_back(log);
            color_list.push_back(ofColor(ofRandom(9,139)));
            life_list.push_back(170);
            
        }

        for (int i = this->log_list.size() - 1; i >= 0; i--) {
 
		this->life_list[i] -= 1;
		if (this->life_list[i] < 0) {
 
			this->log_list.erase(this->log_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
 
			continue;
		}
 
		auto x = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0065, this->noise_seed.x + ofGetFrameNum() * 0.005)), 0, 1, -15, 15);
		auto y = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0065, this->noise_seed.y + ofGetFrameNum() * 0.005)), 0, 1, -15, 15);
		auto z = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0065, this->noise_seed.z + ofGetFrameNum() * 0.005)), 0, 1, -15, 15);
		this->log_list[i].push_back(this->log_list[i].back() + glm::vec3(x, y, z));
	}
        //firelava

        face.clear();
        frame.clear();

        ofSeedRandom(139);
        float phi_deg_step =15;
        float theta_deg_step = 5;
        for (float radius = 130; radius <= 250; radius += 50) {
 
		auto noise_seed = ofRandom(1000);
		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {
 
			for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {
 
				auto noise_location = glm::vec3(
					sin(theta_deg * DEG_TO_RAD) * cos(phi_deg * DEG_TO_RAD),
					sin(theta_deg * DEG_TO_RAD) * sin(phi_deg * DEG_TO_RAD),
					cos(theta_deg * DEG_TO_RAD));
				auto noise_value = ofNoise(glm::vec4(noise_location, noise_seed + ofGetFrameNum() * 0.01));
 
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

}

//--------------------------------------------------------------
void ofApp::draw(){
   
    cam.begin();
    ofRotateYDeg(spinY);
        ofPushStyle();
        ofSetColor(ofColor::black);
        vacio.draw();  
        ofPopStyle();
        for (int i = 0; i < this->log_list.size(); i++) {
 
		ofSetColor(this->color_list[i]);
		ofFill();
		ofDrawSphere(this->log_list[i].front(), 1);
 
		auto alpha = this->life_list[i] > 60 ? 255 : ofMap(this->life_list[i], 0, 60, 0, 255);
		ofSetColor(this->color_list[i], alpha);
 
		ofNoFill();
		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

    
    ofSetColor(ofColor::fromHsb(255,10,6));
	this->face.draw();
 

    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}
