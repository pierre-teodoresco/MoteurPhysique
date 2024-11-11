#include "ParticleSpring.hpp"
#include "Particle/Particle.hpp"

ParticleSpring::ParticleSpring(float springConstant, float restLength, std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB)
{
    m_springConstant = springConstant;
    m_restLength = restLength;
    m_attachedParticle = particleA;
    m_particleB = particleB;
}

void ParticleSpring::updateForce(std::shared_ptr<Particle> particle, float duration) {
    // Calcul de la différence de position par rapport au point d'ancrage
    Vector3D displacement = particle->position() - m_particleB->position();
    float distance = displacement.norm();
    
    // Calcul de l'extension du ressort
    float extension = distance - m_restLength;

    // Force exercée par le ressort : F = -k * extension
    Vector3D force = displacement.normalize() * (-m_springConstant * extension);
    
    // Application de la force aux deux particules
    // On soustrait le damping du ressort (proportionnelle à la vélocité de chaque particule)    
    particle->addForce(force - particle->velocity() * 0.3f);
    m_particleB->addForce(force * -1.0f - m_particleB->velocity() * 0.3f);
}

