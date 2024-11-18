#include "Cube.h"
#include "Cube.h"

Cube::Cube() {
	m_box = ofBoxPrimitive();
	m_box.set(100);

	m_box.setPosition(0.f, 0.f, 0.f);
}

Cube::Cube(float x) {
	m_box = ofBoxPrimitive();
	m_box.set(100);

	m_box.setPosition(x, 0.f, 0.f);
}

void Cube::Draw() {
	ofSetColor(ofColor::red);
	m_box.drawFaces();
	ofSetColor(ofColor::black);
	m_box.drawWireframe();
}

