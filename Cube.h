#pragma once
#include <vector>
#include "of3dPrimitives.h"

class Cube {

public:
	Cube();
	Cube(float x);

	void Draw();

private:
	ofBoxPrimitive m_box;
};
