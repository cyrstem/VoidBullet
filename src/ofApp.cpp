#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("VO!D");
    ofSetBackgroundColor(ofColor::black);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    vacio.init();


 // set DOF parameters
    depth.setup(ofGetWidth(), ofGetHeight());
    focalDist = 1500;
    focalRange = 1500;
    cam.setPosition(0,0,1500);
}

//--------------------------------------------------------------
void ofApp::update(){
   
    vacio.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
   //ofBackgroundGradient(ofColor::fromHsb(0,122,33),ofColor::fromHsb(0,0,0),OF_GRADIENT_CIRCULAR);
       
//    depth.begin();
    cam.begin();
   
        vacio.draw();

    cam.end();
   // depth.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ')
    {
        ofSetFullscreen(true);
    }
    
}