//
//  ParticleGravity.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 30/09/2024.
//

#include "Force/Gravity/ParticleGravity.hpp"
#include "Particle/Particle.hpp"

ParticleGravity::ParticleGravity(const Vector3D& gravity): m_gravity(gravity) {}

void ParticleGravity::updateForce(std::shared_ptr<Particle> particle, float duration) {
    if (particle->inverseMass() == 0.0f) return;  // Particule avec masse infinie
    
    particle->addForce(m_gravity * particle->mass());
}
