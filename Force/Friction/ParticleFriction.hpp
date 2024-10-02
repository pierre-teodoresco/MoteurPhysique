//
//  ParticleStaticFriction.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 02/10/2024.
//

#ifndef ParticleFriction_hpp
#define ParticleFriction_hpp

#include "Force/ParticleForceGenerator.hpp"

class ParticleStaticFriction : public ParticleForceGenerator {
    
private:
    float m_frictionCoefficient;    // Coefficient de friction statique (usuellement noté µ)
    float m_gravity;      // Force de friction statique maximale
    
public:
    ParticleStaticFriction(float frictionCoefficient, float gravity);

    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) override;
};

#endif /* ParticleFriction_hpp */
