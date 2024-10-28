//
//  ParticleGravity.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 30/09/2024.
//

#ifndef ParticleGravity_hpp
#define ParticleGravity_hpp

#include "Force/ParticleForceGenerator.hpp"
#include "Vector3D/Vector3D.hpp"
#include "Particle/Particle.hpp"

#include <memory>

class ParticleGravity : public ParticleForceGenerator {
    
private:
    Vector3D m_gravity;
    
public:
    ParticleGravity(const Vector3D& gravity = Vector3D(0.f, 981.f, 0.f));
    
    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) override;
};

#endif /* ParticleGravity_hpp */
