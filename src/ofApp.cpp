#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("VO!D");
    ofSetBackgroundColor(ofColor::black);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    //ofEnableAntiAliasing();
    vacio.init();
}

//--------------------------------------------------------------
void ofApp::update(){
   
    vacio.update();

    lightpos = glm::vec3(sin(ofGetElapsedTimef()/4.18f) * 150 * 0 + 0,
     sin(ofGetElapsedTimef()/2.8f) * 150 * 2 + 0,
     -cos(ofGetElapsedTimef()/2.8f) * 150 * 2 + 5);

    light.setPosition(lightpos);

  
}

//--------------------------------------------------------------
void ofApp::draw(){
   //ofBackgroundGradient(ofColor::fromHsb(0,122,33),ofColor::fromHsb(0,0,0),OF_GRADIENT_CIRCULAR);
   
    cam.begin();
       // light.enable();
        vacio.draw();
       // light.disable();
        light.draw();

    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ')
    {
        ofSetFullscreen(true);
    }
    
}