#include "ofApp.h"

#include "Ballistic/Ballistic.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    Ballistic::setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    Ballistic::update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    Ballistic::draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    Ballistic::exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'b' || key == 'f' || key == 'p') {
        Ballistic::createParticle(key);
    }
    if (key == 'w')
        Ballistic::addImpulseToBlob(Vector3D(0, -100, 0));
    if (key == 'a')
        Ballistic::addImpulseToBlob(Vector3D(-200, 0, 0));
    if (key == 's')
        Ballistic::addImpulseToBlob(Vector3D(0, 100, 0));
    if (key == 'd')
        Ballistic::addImpulseToBlob(Vector3D(200, 0, 0));

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
    Ballistic::mousePressed(x, y);
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
