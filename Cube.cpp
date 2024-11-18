#include "Cube.h"
#include "ofGraphics.h"

Cube::Cube(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float height, float width, float depth, const Quaternion& orientation) 
	: RigidBody(position,velocity,mass,red,green,blue,width,height,depth,orientation) {

	m_box = ofBoxPrimitive();
	m_box.set(width * height);

	m_box.setPosition(position.x(), position.y(), position.z());

	addForce(Vector3D(0.f, 10.F, 0.f), Vector3D(0.f, 0.f, 0.f));

}

void Cube::Draw() {
	ofSetColor(ofColor::red);
	m_box.drawFaces();
	ofSetColor(ofColor::black);
	m_box.drawWireframe();
}

void Cube::integrate(float dt) {
	
	RigidBody::integrate(dt);
	
	m_box.setPosition(m_position.x(),m_position.y(),m_position.z());
	m_box.setOrientation(m_orientation.ToGLMQuat());
}

