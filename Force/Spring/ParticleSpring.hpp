#ifndef ParticleSpring_hpp
#define ParticleSpring_hpp

#include "Force/Spring/Spring.h"
#include "Force/ParticleForceGenerator.hpp"
#include <memory>

class ParticleSpring : public Spring {
private:
    std::shared_ptr<Particle> m_particleB;  // Autre particule attachée à la particule principale (héritée de Spring)
    

public:
    ParticleSpring(float springConstant, float restLength, std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB);

    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) override;
};

#endif /* ParticleSpring_hpp */
