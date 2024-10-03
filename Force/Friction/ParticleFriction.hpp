//
//  ParticleStaticFriction.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 02/10/2024.
//

#ifndef ParticleFriction_hpp
#define ParticleFriction_hpp

#include "Force/ParticleForceGenerator.hpp"

/* Fonctions générales aux frictions */

float computeNormalForce(const std::shared_ptr<Particle>& particle, float gravity);

/* Friction statique */

class ParticleStaticFriction : public ParticleForceGenerator {
    
private:
    float m_frictionCoefficient;    // Coefficient de friction statique (usuellement noté µ_s)
    float m_gravity;                // Gravité pour calculer la force normale
    
public:
    ParticleStaticFriction(float frictionCoefficient, float gravity);

    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) override;
};

/* Friction cinétique */

class ParticleKineticFriction : public ParticleForceGenerator {
private:
    float m_frictionCoefficient;  // Coefficient de friction cinétique (µ_k)
    float m_gravity;              // Gravité pour calculer la force normale

public:
    // Constructeur avec coefficient de friction et gravité
    ParticleKineticFriction(float frictionCoefficient, float gravity);

    // Implémentation de la méthode updateForce pour la friction cinétique
    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) override;
};

#endif /* ParticleFriction_hpp */
