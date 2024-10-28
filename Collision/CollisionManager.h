#pragma once
#include "Particle/Particle.hpp"
#include "Force/ParticleForceRegistry.hpp"
#include <vector>
#include <array>
#include <memory>

class CollisionManager
{
	public:
		static void detectCollisions(std::vector<std::shared_ptr<Particle>> particles, std::shared_ptr<ParticleForceRegistry>, float minSpeed, float frameTime);
};

