#define _USE_MATH_DEFINES
#include "Ballistic.hpp"
#include "Particle/Particle.hpp"
#include "ofMain.h"
#include "Collision/CollisionManager.h"
#include "Force/Spring/Spring.h"
#include "Force/Spring/AnchoredSpring.hpp"
#include "Force/Spring/ParticleSpring.hpp"
#include <cmath>
#include <numbers>
#include <algorithm>

std::vector<std::shared_ptr<Particle>> particles; //Liste des particules gérées par cette classe
std::vector<std::shared_ptr<Spring>> activeSprings; //Liste des particules gérées par cette classe
std::vector<Vector3D> trajectory; //Liste des positions représentant la trajectoire de la dernière particule créée
bool isParticleCreated = false;    // Drapeau pour savoir si une particule a été créée
char selectedParticleType = '\0';  // Stocke le type de particule sélectionné, mais non encore créé

std::shared_ptr<Particle> blobCore;

/* FORCES */
std::shared_ptr<ParticleForceRegistry> forceRegistry;
Vector3D gravityVector = Vector3D(0, 981.f, 0);
float gravityNorm = gravityVector.norm();
auto gravity = std::make_shared<ParticleGravity>(gravityVector);

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
    forceRegistry = std::make_shared<ParticleForceRegistry>();
    particles.push_back(std::make_shared<Particle>(Vector3D(ofGetWidth() / 2, ofGetHeight() * 50, 0), Vector3D(), std::numeric_limits<float>::max(), 255, 255, 255, ofGetHeight() * 49, 80, true));
    particles.push_back(std::make_shared<Particle>(Vector3D(ofGetWidth(), ofGetHeight()-60, 0), Vector3D(), std::numeric_limits<float>::max(), 255, 255, 255, 60, 80, true));

    blobCore = std::make_shared<Particle>(Vector3D(ofGetWidth() / 2, 500, 0), Vector3D(), 2.0f, 45, 199, 40, 35.0, false);
    particles.push_back(blobCore);
    int start = particles.size()-1;
    for (int i = 0; i < 6; i++)
    {
        Vector3D test = Vector3D((ofGetWidth() / 2) + 33 * cos((2 * M_PI * i) / 6), 500 + 33 * sin((2 * M_PI * i) / 6), 0);
        auto p_i = std::make_shared<Particle>(Vector3D((ofGetWidth() / 2) + 36*cos((2 * M_PI * i) / 6), 500+36*sin((2*M_PI*i)/6), 0), Vector3D(), 2.0f, 45, 199, 40, 35.0, false);
        particles.push_back(p_i);
        activeSprings.push_back(std::make_shared<ParticleSpring>(500.0f, 70.0f, blobCore, p_i));
        if (i > 0)
            activeSprings.push_back(std::make_shared<ParticleSpring>(500.0f, 70.0f, p_i, particles.at(start+i)));
    }
    activeSprings.push_back(std::make_shared<ParticleSpring>(500.0f, 70.0f, particles.back(), particles.at(start+1)));
    isParticleCreated = true;
}

void Ballistic::update() {
    if (particles.size() > 0) {
        // Garder trace des anciennes positions
        //trajectory.push_back(particles.back()->position());
        
        // Récupérer la durée de la dernière frame
        float dt = std::min((float)ofGetLastFrameTime(), 0.1f);


        // Détection des collisions existantes durant cette frame
        CollisionManager::detectCollisions(particles, forceRegistry, gravityNorm, dt);

        // Application de la gravité
        for (auto p : particles)
        {
            // Créer les forces (ici uniquement la gravité) et les ajouter au registre
            forceRegistry->add(p, gravity);
        }

        for (auto s : activeSprings)
        {
            forceRegistry->add(s->getParticle(), s);
        }
        
        // Appliquer les forces du registre
        forceRegistry->updateForces(dt);
        
        // Nettoyer le registre
        forceRegistry->clear();

        // Intégration
        for (auto p : particles)
        {
            // Intégrer avec le delta time
            p->integrate(dt);
        }
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
            ofDrawCircle(pos.v3(), 2);
        }

        for (auto p : particles)
        {
            p->draw();
        }
    }
}

void Ballistic::exit() {
    // Inutile avec des shared_ptr
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
        Vector3D pos(0.f, windowHeight-30, 0.f);  // Coin inférieur gauche
        Vector3D clickPos(x, y, 0.f);  // Position du clic de la souris

        // Calculer le vecteur de vélocité initiale
        Vector3D velocity = (clickPos - pos) * 1.5f;

        // Créer la particule à partir du coin inférieur gauche avec le vecteur de vélocité calculé
        switch (selectedParticleType) {
            case 'b':  // Boulet de canon
                particles.push_back(std::make_shared<Particle>(pos, velocity, 3.92f, 199, 45, 40, 30.0, false));
                break;

            case 'f':  // Ballon de foot
                particles.push_back(std::make_shared<Particle>(pos, velocity, 0.43f, 255, 255, 0, 25.0, false));
                break;

            case 'p':  // Balle de ping-pong
                particles.push_back(std::make_shared<Particle>(pos, velocity, 0.0027f, 255, 255, 255, 10.0, false));
                break;
        }

        // Réinitialiser la trajectoire
        trajectory.clear();
        isParticleCreated = true;  // La particule est maintenant créée
    }
}

Vector3D Ballistic::getGravity()
{
    return gravityVector;
}

void Ballistic::addImpulseToBlob(Vector3D impulse)
{
    blobCore->addVelocity(impulse);
}
