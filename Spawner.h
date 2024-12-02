#pragma once
#include <vector>
#include "of3dPrimitives.h"
#include "Cube.h"

class Spawner {
public:
	Spawner() = default;

	void Refresh();
	void Update();

	std::vector<std::shared_ptr<Cube>>& GetBoxes() { return m_boxes; }

private:
	float m_currentTime;
	float m_spawnTime;

	std::vector<std::shared_ptr<Cube>> m_boxes;
};
