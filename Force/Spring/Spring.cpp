#include "Spring.h"

std::shared_ptr<Particle> Spring::getParticle()
{
    return m_attachedParticle;
}