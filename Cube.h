#pragma once
#include <vector>
#include "of3dPrimitives.h"
#include "Rigidbody/Rigidbody.hpp"

class Cube : public RigidBody {

public:
	Cube(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float height, float width, float depth, const Quaternion& orientation);

	void Draw();
	ofBoxPrimitive& getBox() { return m_box; }

	void integrate(float dt);

private:
	ofBoxPrimitive m_box;
	bool hasLaunched;
};
