//
//  ParticleForceRegistry.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 30/09/2024.
//

#include "ParticleForceRegistry.hpp"

ParticleForceRegistry::ParticleForceRegistry() {
    // Réserver 3 registrations pour optimiser. La valeur 3 est arbitraire et a modifiée si les besoins sont différents
    m_registry.reserve(3);
}

void ParticleForceRegistry::add(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator) {
    ParticleForceRegistration newForce = ParticleForceRegistration { particle, forceGenerator };
    m_registry.push_back(newForce);
}

void ParticleForceRegistry::remove(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> forceGenerator) {
    // Parcourir le registre et retirer l'entrée qui correspond au couple particle/forceGenerator
    for (auto it = m_registry.begin(); it != m_registry.end(); ++it) {
        if (it->particle == particle && it->forceGenerator == forceGenerator) {
            m_registry.erase(it);
            break;
        }
    }
}

void ParticleForceRegistry::clear() {
    m_registry.clear();
}

void ParticleForceRegistry::updateForces(float duration) {
    // Permet de déstructurer ParticleForceRegistration directement
    for (auto& [particle, forceGenerator] : m_registry) {
        forceGenerator->updateForce(particle, duration);
    }
}
