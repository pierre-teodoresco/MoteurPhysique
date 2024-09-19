//
//  Ballistic.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 18/09/2024.
//

#include "Ballistic.hpp"
#include "Particle/Particle.hpp"
#include "ofMain.h"

#include <vector>
#include <array>
#include <memory>

std::unique_ptr<Particle> p;
float currentRadius;
std::array<int, 3> currentColor;
std::vector<Vector3D> trajectory;

void Ballistic::setup() {
    createParticle('b');  // Créer le boulet de canon par défaut
}

void Ballistic::update() {
    // Garder trace des anciennes positions
    trajectory.push_back(p->position());
    
    // Appliquer la gravité
    const Vector3D gravity(0.f, 9.81f, 0.f);
    Vector3D weight = gravity * p->mass();
    p->applyForce(weight);
    
    // Intégrer avec le delta time
    float dt = ofGetLastFrameTime();
    p->integrate(dt);
}

void Ballistic::draw() {
    // Les textes et les trajectoires sont blancs
    ofSetColor(255, 255, 255);
    
    // Afficher le temps de frame
    ofDrawBitmapString("Frame time: " + ofToString(ofGetLastFrameTime()), 10, 20);
    
    // Afficher la légende dans le coin supérieur droit
    int windowWidth = ofGetWidth();
    int marginRight = 100;  // Distance par rapport au bord droit
    int marginTop = 20;    // Distance par rapport au haut

    // Texte à afficher
    std::string info = "Controls:\n";
    info += "B: Cannonball (Mass: 3.92 kg)\n";
    info += "F: Football (Mass: 0.43 kg)\n";
    info += "P: Ping-pong ball (Mass: 0.0027 kg)\n";

    // Afficher le texte dans le coin supérieur droit
    ofDrawBitmapString(info, windowWidth - marginRight - 200, marginTop);  // Position à droite
    
    // Dessiner la trajectoire
    for (const auto& pos : trajectory) {
        ofDrawCircle(pos.v2(), 2);
    }

    // Dessiner la particule avec la couleur actuelle
    ofSetColor(currentColor[0], currentColor[1], currentColor[2]);
    p->draw(currentRadius);  // Utiliser currentRadius pour changer la taille
}

void Ballistic::exit() {
    p.reset();  // Libérer la mémoire automatiquement avec unique_ptr
}

void Ballistic::createParticle(char type) {
    // Créer la nouvelle particule avec std::make_unique, cela détruit automatiquement l'ancienne.
    Vector3D pos(0.f, 700.f, 0.f);
    Vector3D velocity;

    switch (type) {
        case 'b':  // Boulet de canon
            velocity = Vector3D(50.f, -60.f, 0.f);  // Vitesse plus lente pour une courbe lourde
            p = std::make_unique<Particle>(pos, velocity, 3.92f);  // Masse d'un boulet de canon (~3.92 kg)
            currentRadius = 30;  // Rayon plus grand
            currentColor = {199, 45, 40};  // Rouge
            break;
        
        case 'f':  // Ballon de foot
            velocity = Vector3D(70.f, -60.f, 0.f);  // Vitesse modérée pour une belle trajectoire
            p = std::make_unique<Particle>(pos, velocity, 0.43f);  // Masse du ballon de foot (~0.43 kg)
            currentRadius = 25;  // Rayon d'un ballon de foot
            currentColor = {255, 255, 0};  // Jaune ou couleur du ballon
            break;
        
        case 'p':  // Balle de ping-pong
            velocity = Vector3D(120.f, -100.f, 0.f);  // Vitesse très rapide pour une balle légère
            p = std::make_unique<Particle>(pos, velocity, 0.0027f);  // Masse très faible pour la balle de ping-pong (~0.0027 kg)
            currentRadius = 10;  // Petit rayon pour la balle de ping-pong
            currentColor = {255, 255, 255};  // Blanc
            break;
    }

    // Réinitialiser la trajectoire pour la nouvelle particule
    //trajectory.clear();
}
