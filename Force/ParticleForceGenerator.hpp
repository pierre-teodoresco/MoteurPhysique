//
//  ParticleForceGenerator.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 30/09/2024.
//

#ifndef ParticleForceGenerator_hpp
#define ParticleForceGenerator_hpp

#include "Vector3D/Vector3D.hpp"
#include "Particle/Particle.hpp"

#include <memory>

class ParticleForceGenerator {
    
public:
    virtual void updateForce(std::shared_ptr<Particle> particle, float duration) = 0;

};

#endif /* ParticleForceGenerator_hpp */
