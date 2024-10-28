#ifndef AnchoredSpring_hpp
#define AnchoredSpring_hpp

#include "Force/Spring/Spring.h"
#include "Force/ParticleForceGenerator.hpp"

class AnchoredSpring : public Spring {
private:
    Vector3D m_anchor;  // Point d'ancrage du ressort (position fixe)
    

public:
    AnchoredSpring(const Vector3D& anchor, float springConstant, float restLength, std::shared_ptr<Particle> particle);

    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) override;
};

#endif /* AnchoredSpring_hpp */
