#include "Ballistic.hpp"
#include "Particle/Particle.hpp"
#include "ofMain.h"
#include "Vector3D/Vector3D.hpp"
#include "Force/ParticleForceGenerator.hpp"
#include "Force/ParticleForceRegistry.hpp"
#include "Force/Gravity/ParticleGravity.hpp"

#include <vector>
#include <array>
#include <string>
#include <memory>

std::vector<std::shared_ptr<Particle>> particles; //Liste des particules gérées par cette classe
std::vector<Vector3D> trajectory; //Liste des positions représentant la trajectoire de la dernière particule créée
bool isParticleCreated = false;    // Drapeau pour savoir si une particule a été créée
char selectedParticleType = '\0';  // Stocke le type de particule sélectionné, mais non encore créé
ParticleForceRegistry forceRegistry;

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
        trajectory.push_back(particles.back()->position());
        
        // Récupérer la durée de la dernière frame
        float dt = ofGetLastFrameTime();

        // Détection des collisions existantes durant cette frame
        detectCollisions();

        // Application de la gravité
        for (auto p : particles)
        {
            // Créer les forces (ici uniquement la gravité) et les ajouter au registre
            auto gravity = std::make_shared<ParticleGravity>();
            forceRegistry.add(p, gravity);
            
            // Appliquer les forces du registre
            forceRegistry.updateForces(dt);
            
            // Intégrer avec le delta time
            p->integrate(dt);
        }
        
        // Nettoyer le registre
        forceRegistry.clear();
    }
}

void Ballistic::detectCollisions() {
    //Itération à travers chaque paire de particules
    for (int i = 0; i < particles.size(); i++)
    {
        std::shared_ptr<Particle> particleA = particles.at(i);
        for (int j = i+1; j < particles.size(); j++)
        {
            std::shared_ptr<Particle> particleB = particles.at(j);
            
            //Calculer le vecteur distance entre les deux particules
            Vector3D dist = particleA->position() - particleB->position();                                
            
            //Si la distance est inférieure à la somme de leurs rayons, il ya collision
            if (dist.norm() < (particleA->radius() + particleB->radius()))        
            {
                //Calculer de combien elles se pénètrent l'une l'autre
                //puis réduire le vecteur distance à cette taille
                float penetration = dist.norm() - (particleA->radius() + particleB->radius());
                Vector3D normal = dist.normalize();
                Vector3D displacement = normal * penetration;

                //Calculer un nouveau vecteur "unitaire" représentant le déplacement par unité de masse 
                //pour éviter de devoir faire plusieurs divisions
                Vector3D dispPerMass = displacement / (particleA->mass() + particleB->mass());

                //Enfin, appliquer à chaque particule sa "part" du déplacement, basée sur la masse de l'autre
                particleA->addDisplacement(dispPerMass * (particleB->mass() * -1.0f));
                particleB->addDisplacement(dispPerMass * particleA->mass());
            }
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
        Vector3D pos(0.f, windowHeight, 0.f);  // Coin inférieur gauche
        Vector3D clickPos(x, y, 0.f);  // Position du clic de la souris

        // Calculer le vecteur de vélocité initiale
        Vector3D velocity = (clickPos - pos) * 1.5f;

        // Créer la particule à partir du coin inférieur gauche avec le vecteur de vélocité calculé
        switch (selectedParticleType) {
            case 'b':  // Boulet de canon
                particles.push_back(std::make_shared<Particle>(pos, velocity, 3.92f, 199, 45, 40, 30.0));
                break;

            case 'f':  // Ballon de foot
                particles.push_back(std::make_shared<Particle>(pos, velocity, 0.43f, 255, 255, 0, 25.0));
                break;

            case 'p':  // Balle de ping-pong
                particles.push_back(std::make_shared<Particle>(pos, velocity, 0.0027f, 255, 255, 255, 10.0));
                break;
        }

        // Réinitialiser la trajectoire
        trajectory.clear();
        isParticleCreated = true;  // La particule est maintenant créée
    }
}
