#pragma once
#include "Particle/Particle.hpp"
#include "Force/ParticleForceRegistry.hpp"
#include <vector>
#include <array>
#include <memory>
#include "Cube.h"

class CollisionManager
{
	public:
		static void detectCollisions(std::vector<std::shared_ptr<Cube>> particles, std::shared_ptr<ParticleForceRegistry>, float minSpeed, float frameTime);
};

