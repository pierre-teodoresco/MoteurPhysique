#include "Particles.hpp"

Particles::Particles(Vector3D position, Vector3D velocity, Vector3D acceleration, float mass) {
    m_position = position;
    m_velocity = velocity;
    m_acceleration = acceleration;
    if (mass > 0) {
        m_inverseMass = 1.0f / mass;
    }
    else {
        m_inverseMass = 0.0f;
    }
}

Vector3D Particles::getPosition() {
    return m_position;
}

Vector3D Particles::getVelocity() {
    return m_velocity;
}

Vector3D Particles::getAcceleration() {
    return m_acceleration;
}

float Particles::getInverseMass() {
    return m_inverseMass;
}

void Particles::setPosition(Vector3D position) {
    m_position = position;
}

void Particles::setVelocity(Vector3D velocity) {
    m_velocity = velocity;
}

void Particles::setAcceleration(Vector3D acceleration) {
    m_acceleration = acceleration;
}

void Particles::setMass(float mass) {
    if (mass > 0) {
        m_inverseMass = 1.0f / mass;
    }
    else {
        m_inverseMass = 0.0f;
    }
}

void Particles::integrateEuler(float deltaTime) {
    if (m_inverseMass <= 0) {
        return;
    }
    m_velocity = m_velocity + (m_acceleration * deltaTime);
    m_position = m_position + (m_velocity * deltaTime);
}
