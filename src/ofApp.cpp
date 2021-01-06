#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("VO!D");
    ofSetBackgroundColor(ofColor::black);
    ofSetFrameRate(60);
   // ofEnableDepthTest();
    //ofEnableAntiAliasing();
    vacio.init();
}

//--------------------------------------------------------------
void ofApp::update(){
   
    vacio.update();
  
}

//--------------------------------------------------------------
void ofApp::draw(){
   ofBackgroundGradient(ofColor::fromHsb(0,122,33),ofColor::fromHsb(0,0,0),OF_GRADIENT_CIRCULAR);
   
    cam.begin();
       
        vacio.draw();
    

    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ')
    {
        ofSetFullscreen(true);
    }
    
}