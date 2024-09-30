//
//  ParticleForceRegistry.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 30/09/2024.
//

#ifndef ParticleForceRegistry_hpp
#define ParticleForceRegistry_hpp

#include "Particle/Particle.hpp"
#include "Force/ParticleForceGenerator.hpp"

#include <vector>
#include <memory>

class ParticleForceRegistry {
    
private:
    struct ParticleForceRegistration {
        std::shared_ptr<Particle> particle;
        std::shared_ptr<ParticleForceGenerator> forceGenerator;
    };
    
    typedef std::vector<ParticleForceRegistration> Registry;

public:
    ParticleForceRegistry();
    
    void add(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);
    void remove(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator);
    void clear();
    
    void updateForces(float duration);
    
private:
    Registry m_registry;
};

#endif /* ParticleForceRegistry_hpp */
