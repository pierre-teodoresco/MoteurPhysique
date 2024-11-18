#include "Spawner.h"
#include <cstdlib>

void Spawner::Refresh() {
	m_spawnTime = 3 + std::rand() % (7 - 3 + 1);
	m_currentTime = 0.0f;

	float x = std::rand() % 800;

	m_boxes.push_back(Cube(400.f - x));
}

void Spawner::Update() {
	m_currentTime += ofGetLastFrameTime();
	if (m_currentTime >= m_spawnTime) {
		Refresh();
	}
}
