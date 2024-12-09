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
		static void detectParticleCollisions(std::vector<std::shared_ptr<Particle>> particles, std::shared_ptr<ParticleForceRegistry>, float minSpeed, float frameTime);
		static void detectCollisions(std::vector<std::shared_ptr<Cube>> cubes, std::shared_ptr<ParticleForceRegistry>, float minSpeed, float frameTime);
};

