#include "ofApp.h"

#include "Ballistic/Ballistic.hpp"
#include "Collision/CollisionManager.h"
#include "Force/ParticleForceRegistry.hpp"
#include "Force/Spring/Spring.h"
#include "Octree.h"
#include <cstdlib>


std::shared_ptr<ParticleForceRegistry> m_registry;
Vector3D m_gravityVec = Vector3D(0, -981.f, 0);
auto m_gravity = std::make_shared<ParticleGravity>(m_gravityVec);
std::vector<std::shared_ptr<Spring>> activeSprings;

//--------------------------------------------------------------
void ofApp::setup(){
    //Ballistic::setup();

    ofShowCursor();
    m_registry = std::make_shared<ParticleForceRegistry>();

    ofBackground(0);
    ofEnableDepthTest();

    m_spawner = Spawner();
}

//--------------------------------------------------------------
void ofApp::update(){

    if(m_spawner.GetBoxes().empty()) return;

    float dt = std::min((float)ofGetLastFrameTime(), 0.1f);

    // Détection des collisions existantes durant cette frame
    SphereBound spherebound = SphereBound(Vector3D(0, 0, 0), 10000.0f);
    Octree octree = Octree(spherebound, 2);
    CollisionManager::detectCollisions(m_spawner.GetBoxes(), m_registry, m_gravityVec.norm(), dt);

    // Application de la gravité
        // Créer les forces (ici uniquement la gravité) et les ajouter au registre

    for (auto& box : m_spawner.GetBoxes()) {
        m_registry->add(box, m_gravity);
    }
        

    // Appliquer les forces du registre
    m_registry.get()->updateForces(dt);

    // Nettoyer le registre

    m_registry.get()->clear();
        
    // Intégration
    for (auto& p : m_spawner.GetBoxes()) {
        // Intégrer avec le delta time
        p->integrate(dt);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    m_camera.begin();

    ofPushMatrix();

    for (auto& box : m_spawner.GetBoxes()) {
        box.get()->Draw();
	}

    ofPopMatrix();

    m_camera.end();
}

//--------------------------------------------------------------
void ofApp::exit(){
    Ballistic::exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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

    float random = 30 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (60 - 30)));

    m_spawner.GetBoxes().push_back(std::make_shared<Cube>(Vector3D(100.f, -350.f, -1000.f), Vector3D(0.f, 0.f, 0.f),
        1.f, 255.f, 255.f, 255.f, random, random, random, Quaternion(1.f, 0.f, 0.f, 0.f)));
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
