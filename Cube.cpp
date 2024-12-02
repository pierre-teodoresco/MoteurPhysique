#include "Cube.h"
#include "ofGraphics.h"

Cube::Cube(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float height, float width, float depth, const Quaternion& orientation) 
	: RigidBody(position,velocity,mass,red,green,blue,width,height,depth,orientation) {

	m_box = ofBoxPrimitive();
	m_box.set(width * height);

	m_box.setPosition(position.x(), position.y(), position.z());
	hasLaunched = false; 

}

void Cube::Draw() {
	m_box.setPosition(m_position.x(), m_position.y(), m_position.z());
	m_box.setOrientation(m_orientation.ToGLMQuat());

	ofSetColor(ofColor::red);
	m_box.drawFaces();
	ofSetColor(ofColor::black);
	m_box.drawWireframe();

	ofSetColor(0,0,255);
	ofDrawCircle(m_position.x() + 100.F,m_position.y() + 100.F, 10.F);
}

void Cube::integrate(float dt) {
	if (dt > 0.f && !hasLaunched) {
		addForce(Vector3D(0.f,100000.f, 0.f), Vector3D(100.f, 100.f, 0.f));
		hasLaunched = true;
	}

	RigidBody::integrate(dt);
}

