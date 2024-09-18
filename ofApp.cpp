#include "ofApp.h"

#include "Vector3D/Vector3D.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    Vector3D pos(0.f, 700.f, 0.f);
    Vector3D velocity(40.f, -100.f, 0.f);
    p = new Particle(pos, velocity, 5);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Gravity
    const Vector3D acceleration(0.f, 9.81f, 0.f);
    const Vector3D gravity = acceleration * p->mass();
    p->addForce(gravity);
    
    float dt = 1.0f / 60.0f;
    p->integrate(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
    p->draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    delete p;
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

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
