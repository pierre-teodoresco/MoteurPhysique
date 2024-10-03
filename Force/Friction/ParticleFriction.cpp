//
//  ParticleStaticFriction.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 02/10/2024.
//

#include "ParticleFriction.hpp"

/* Fonctions générales aux frictions */

// Calcul de la force normale : N = m * g
float computeNormalForce(const std::shared_ptr<Particle>& particle, float gravity) {
    // Dans un cas où le sol est plat
    // La force normale dépend de l'inclinaison du sol
    return particle->mass() * gravity;
}

/* Friction statique */

ParticleStaticFriction::ParticleStaticFriction(float frictionCoefficient, float gravity)
    : m_frictionCoefficient(frictionCoefficient), m_gravity(gravity) {}

void ParticleStaticFriction::updateForce(std::shared_ptr<Particle> particle, float duration) {
    if (particle->inverseMass() == 0.0f) return;  // Particule avec masse infinie

    // Calcul de la force normale
    float normalForce = computeNormalForce(particle, m_gravity);

    // Calcul de la force de friction statique maximale : F_max = µ_s * N
    float maxStaticFriction = m_frictionCoefficient * normalForce;

    // Calcul de la force appliquée sur la particule (dans ce cas, la force due à la quantité de mouvement)
    Vector3D velocity = particle->velocity();
    float speed = velocity.norm();

    // Si la force est inférieure à la force de friction statique maximale, on annule le mouvement
    if (speed < maxStaticFriction) {
        Vector3D frictionForce = velocity * -1.0f;  // Annule complètement la vitesse
        particle->addForce(frictionForce);
    }
}

/* Friction cinétique */

ParticleKineticFriction::ParticleKineticFriction(float frictionCoefficient, float gravity)
    : m_frictionCoefficient(frictionCoefficient), m_gravity(gravity) {}

void ParticleKineticFriction::updateForce(std::shared_ptr<Particle> particle, float duration) {
    if (particle->inverseMass() == 0.0f) return;  // Particule avec masse infinie

    Vector3D velocity = particle->velocity();
    if (velocity.squaredNorm() == 0.f) return;  // Pas de friction cinétique pour une particule au repos

    // Calcul de la force normale
    float normalForce = computeNormalForce(particle, m_gravity);

    // Calcul de la force de friction cinétique en opposition au mouvement : F_k = -µ_k * N * (v / |v|)
    Vector3D frictionForce = velocity.normalize() * -m_frictionCoefficient * normalForce;

    // Application de la force de friction à la particule
    particle->addForce(frictionForce);
}
