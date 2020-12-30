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
    noise_seed = glm::vec3(ofRandom(1000),ofRandom(1000),ofRandom(1000));
    ofIcoSpherePrimitive ico_sphere = ofIcoSpherePrimitive(210,3);
    vector<ofMeshFace> triangles = ico_sphere.getMesh().getUniqueFaces();
    for (int i = 0; i < triangles.size(); i++)
    {
        ofPoint average = (triangles[i].getVertex(0) +triangles[i].getVertex(1) + triangles[i].getVertex(2))/3;
        location_list.push_back(average);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    spinY+=0.13;
    //fireRays
    int radius = 3;
        while (log_list.size() <550)        
        {
            int location_index = ofRandom(location_list.size());
            vector<glm::vec3> log;
            log.push_back(location_list[location_index]);
            log_list.push_back(log);
            color_list.push_back(ofColor(ofRandom(39,139)));
            life_list.push_back(270);
            
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
		ofDrawSphere(this->log_list[i].front(), 2);
 
		auto alpha = this->life_list[i] > 60 ? 255 : ofMap(this->life_list[i], 0, 60, 0, 255);
		ofSetColor(this->color_list[i], alpha);
 
		ofNoFill();
		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}
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
