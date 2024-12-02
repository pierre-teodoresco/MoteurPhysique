#pragma once
#include "Force/ParticleForceGenerator.hpp"
#include "../../Particle/Particle.hpp"

class Spring :
    public ParticleForceGenerator
{
protected:
    float m_springConstant;  // Constante de raideur k
    float m_restLength;      // Longueur à l'équilibre du ressort
    std::shared_ptr<Particle> m_attachedParticle; //Particule attachée au ressort

public:
    std::shared_ptr<Particle> getParticle();
};

