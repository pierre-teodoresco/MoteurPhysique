#ifndef ParticleSpring_hpp
#define ParticleSpring_hpp

#include "ParticleForceGenerator.hpp"

class ParticleSpring : public ParticleForceGenerator {
private:
    Vector3D m_anchor;  // Point d'ancrage du ressort (position fixe)
    float m_springConstant;  // Constante de raideur k
    float m_restLength;      // Longueur à l'équilibre du ressort

public:
    ParticleSpring(const Vector3D& anchor, float springConstant, float restLength);

    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) override;
};

#endif /* ParticleSpring_hpp */
