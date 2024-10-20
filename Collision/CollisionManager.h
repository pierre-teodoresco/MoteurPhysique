#pragma once
#include "Particle/Particle.hpp"
#include <vector>
#include <array>
#include <memory>

class CollisionManager
{
	public:
		static void detectCollisions(std::vector<std::shared_ptr<Particle>> particles);
};

