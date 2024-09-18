//
//  Particle.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
//

#include "Particle.hpp"

/* CONSTRUCTORS */
Particle::Particle(const Vector3D& position, const Vector3D& velocity, float mass)
    : m_position(position), m_velocity(velocity), m_forceAccum(0, 0, 0), m_acceleration(0, 0, 0) {
    setMass(mass); // Initialize mass (or inverse mass) here
}

/* GETTERS */

// Get position
Vector3D Particle::position() const {
    return m_position;
}

// Get velocity
Vector3D Particle::velocity() const {
    return m_velocity;
}

// Get acceleration
Vector3D Particle::acceleration() const {
    return m_acceleration;
}

// Get inverse mass
float Particle::inverseMass() const {
    return m_inverseMass;
}

/* SETTERS */

// Set inverse mass
void Particle::setInverseMass(float inverseMass) {
    m_inverseMass = inverseMass;
}

// Set mass
void Particle::setMass(float mass) {
    if (mass == 0.0f) {
        m_inverseMass = 0.0f;  // Infinite mass (immovable object)
    } else {
        m_inverseMass = 1.0f / mass;
    }
}

/* FORCE ACCUMULATOR */

// Add a force to the particle
void Particle::addForce(const Vector3D& force) {
    m_forceAccum += force;
}

/* INTEGRATOR */

// Euler integration to update position and velocity
void Particle::integrate(float duration) {
    if (m_inverseMass <= 0.0f) return; // If the particle has infinite mass, do not move it

    // Update position using velocity
    m_position += m_velocity * duration;
    
    // Calculate acceleration from the accumulated force
    m_acceleration = m_forceAccum * m_inverseMass;
    
    // Update velocity using acceleration
    m_velocity += m_acceleration * duration;
    
    // Reset accumulated forces after integration
    clearForces();
}

// Reset the force accumulator
void Particle::clearForces() {
    m_forceAccum = Vector3D(0, 0, 0);
}

/* OPEN FRAMEWORK */

#include "ofMain.h"

void Particle::draw() const {
    ofDrawCircle(m_position.v2(), 1.f / m_inverseMass);
}
