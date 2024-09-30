//
//  ParticleGravity.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 30/09/2024.
//

#include "Force/Gravity/ParticleGravity.hpp"
#include "Particle/Particle.hpp"

#include <stdexcept>

ParticleGravity::ParticleGravity(const Vector3D& gravity): m_gravity(gravity) {}

void ParticleGravity::updateForce(std::shared_ptr<Particle> particle, float duration) {
    // TODO : je sais pas quoi faire de cet attribut duration
    
    float mass = particle->mass();
    if (mass == 0.0f) {
        throw std::runtime_error("Can't apply force on a null mass particle");
    }
    particle->addForce(m_gravity * mass);
}
