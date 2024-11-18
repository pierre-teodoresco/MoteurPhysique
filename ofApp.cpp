#include "ofApp.h"

#include "Ballistic/Ballistic.hpp"
#include "Collision/CollisionManager.h"
#include "Force/ParticleForceRegistry.hpp"
#include "Force/Spring/Spring.h"

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
    m_spawner.Update();

    for (auto& box : m_spawner.GetBoxes()) {
        float dt = std::min((float)ofGetLastFrameTime(), 0.1f);

        // Détection des collisions existantes durant cette frame
        CollisionManager::detectCollisions(m_spawner.GetBoxes(), m_registry, m_gravityVec.norm(), dt);

        // Application de la gravité
        for (auto& p : m_spawner.GetBoxes()) {
            // Créer les forces (ici uniquement la gravité) et les ajouter au registre
            m_registry->add(p, m_gravity);
        }

        for (auto s : activeSprings) {
            m_registry->add(s->getParticle(), s);
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
