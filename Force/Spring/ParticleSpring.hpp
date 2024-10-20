#ifndef ParticleSpring_hpp
#define ParticleSpring_hpp

#include "Force/Spring/Spring.h"
#include "Force/ParticleForceGenerator.hpp"

class ParticleSpring : public Spring {
private:
    Vector3D m_anchor;  // Point d'ancrage du ressort (position fixe)
    

public:
    ParticleSpring(const Vector3D& anchor, float springConstant, float restLength, std::shared_ptr<Particle> particle);

    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) override;
};

#endif /* ParticleSpring_hpp */
