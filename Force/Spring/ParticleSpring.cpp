#include "ParticleSpring.hpp"

ParticleSpring::ParticleSpring(const Vector3D& anchor, float springConstant, float restLength, std::shared_ptr<Particle> particle)
    : m_anchor(anchor) {
    m_springConstant = springConstant;
    m_restLength = restLength;
    m_attachedParticle = particle;
}

void ParticleSpring::updateForce(std::shared_ptr<Particle> particle, float duration) {
    // Calcul de la différence de position par rapport au point d'ancrage
    Vector3D displacement = particle->position() - m_anchor;
    float distance = displacement.norm();
    
    // Calcul de l'extension du ressort
    float extension = distance - m_restLength;

    // Force exercée par le ressort : F = -k * extension
    Vector3D force = displacement.normalize() * (-m_springConstant * extension);

    // Application de la force à la particule
    particle->addForce(force);
}

