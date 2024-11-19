#include "Spawner.h"
#include <cstdlib>

void Spawner::Refresh() {
	m_spawnTime = /*3 + std::rand() % (7 - 3 + 1)*/ 100000;
	m_currentTime = 0.0f;

	m_boxes.push_back(std::make_shared<Cube>(Vector3D(10.f, -350.f, 10.f), Vector3D(0.f, 0.f,0.f),
		1.f,255,255,255,10,10,1000,Quaternion(1,0,0,0)));

	std::cout << "Spawned a cube " << std::endl;
}

void Spawner::Update() {
	m_currentTime += ofGetLastFrameTime();
	if (m_currentTime >= m_spawnTime) {
		Refresh();
	}
}
