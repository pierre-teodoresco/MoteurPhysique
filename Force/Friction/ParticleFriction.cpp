//
//  ParticleStaticFriction.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 02/10/2024.
//

#include "ParticleFriction.hpp"

#include <stdexcept>

ParticleStaticFriction::ParticleStaticFriction(float frictionCoefficient, float gravity)
        : m_frictionCoefficient(frictionCoefficient), m_gravity(gravity) {}

void ParticleStaticFriction::updateForce(std::shared_ptr<Particle> particle, float duration) {
    float mass = particle->mass();
    if (mass == 0.0f) {
        throw std::runtime_error("Can't apply force on a null mass particle");
    }

    // Calcul de la force normale : N = m * g
    float normalForce = mass * m_gravity;

    // Calcul de la force de friction statique maximale : F_max = µ_s * N
    float maxStaticFriction = m_frictionCoefficient * normalForce;

    // Calcul de la force totale appliquée sur la particule
    Vector3D totalForce = particle->velocity() * mass;
    float magnitude = totalForce.norm();

    // Si la force est inférieure à la force de friction statique maximale, on annule le mouvement
    if (magnitude < maxStaticFriction) {
        particle->addForce(totalForce * -1.f);  // Applique une force opposée pour annuler
    }
}
