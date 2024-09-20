#include "Ballistic.hpp"
#include "Particle/Particle.hpp"
#include "ofMain.h"
#include "Vector3D/Vector3D.hpp"

#include <vector>
#include <array>
#include <memory>
#include <string>

std::unique_ptr<Particle> p;

std::vector<Vector3D> trajectory;
bool isParticleCreated = false;    // Drapeau pour savoir si une particule a été créée
char selectedParticleType = '\0';  // Stocke le type de particule sélectionné, mais non encore créé

// private function
std::string getParticleName(char type) {
    switch (type) {
        case 'b':  // Boulet de canon
            return "Canonnball";

        case 'f':  // Ballon de foot
            return "Football";

        case 'p':  // Balle de ping-pong
            return "Ping-pong ball";
            
        default:
            return "None";
    }
}

void Ballistic::setup() {
    ofShowCursor();
}

void Ballistic::update() {
    if (isParticleCreated) {
        // Garder trace des anciennes positions
        trajectory.push_back(p->position());

        // Appliquer la gravité
        const Vector3D gravity(0.f, 9.81f, 0.f);
        Vector3D weight = gravity * p->mass();
        p->applyForce(weight);

        // Intégrer avec le delta time
        float dt = ofGetLastFrameTime() * 2.f;
        p->integrate(dt);
    }
}

void Ballistic::draw() {
    // Les textes et les trajectoires sont blancs
    ofSetColor(ofColor::white);
    
    // Afficher le temps de frame
    ofDrawBitmapString("Frame time: " + ofToString(ofGetLastFrameTime()), 10, 20);

    // Afficher la légende dans le coin supérieur droit
    int windowWidth = ofGetWidth();
    int marginRight = 100;
    int marginTop = 20;

    std::string info = "Controls:\n";
    info += "B: Cannonball (Mass: 3.92 kg)\n";
    info += "F: Football (Mass: 0.43 kg)\n";
    info += "P: Ping-pong ball (Mass: 0.0027 kg)\n";

    ofDrawBitmapString(info, windowWidth - marginRight - 200, marginTop);  // Position à droite
    
    // Afficher le type de particule
    std::string particleName = "Selected : " + getParticleName(selectedParticleType);
    int textWidth = 8 * particleName.length();  // Estimation de la largeur du texte (chaque caractère fait environ 8px)
    marginRight = (windowWidth - textWidth) / 2;
    ofDrawBitmapString(particleName, marginRight, marginTop);

    if (isParticleCreated) {
        // Dessiner la trajectoire
        for (const auto& pos : trajectory) {
            ofDrawCircle(pos.v2(), 2);
        }

        // Dessiner la particule avec la couleur actuelle
        p->draw();
    }
}

void Ballistic::exit() {
    p.reset();  // Libérer la mémoire automatiquement avec unique_ptr
}

void Ballistic::createParticle(char type) {
    // Sauvegarder le type de particule sélectionné
    selectedParticleType = type;
}

void Ballistic::mousePressed(int x, int y) {
    // Si un type de particule a été sélectionné
    if (selectedParticleType != '\0') {
        // Calculer le vecteur de vélocité basé sur le clic
        int windowHeight = ofGetHeight();
        Vector3D pos(0.f, windowHeight, 0.f);  // Coin inférieur gauche
        Vector3D clickPos(x, y, 0.f);  // Position du clic de la souris

        // Calculer le vecteur de vélocité initiale
        Vector3D velocity = (clickPos - pos) / 5;

        // Créer la particule à partir du coin inférieur gauche avec le vecteur de vélocité calculé
        switch (selectedParticleType) {
            case 'b':  // Boulet de canon
                p = std::make_unique<Particle>(pos, velocity, 3.92f, 199, 45, 40, 30.0);  // Masse d'un boulet de canon (~3.92 kg)
                break;

            case 'f':  // Ballon de foot
                p = std::make_unique<Particle>(pos, velocity, 0.43f, 255, 255, 0, 25.0);  // Masse du ballon de foot (~0.43 kg)
                break;

            case 'p':  // Balle de ping-pong
                p = std::make_unique<Particle>(pos, velocity, 0.0027f, 255, 255, 255, 10.0);  // Masse de la balle de ping-pong (~0.0027 kg)
                break;
        }

        // Réinitialiser la trajectoire
        trajectory.clear();
        isParticleCreated = true;  // La particule est maintenant créée
    }
}
