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

/* SETTERS */

// Get Mass
float Particle::mass() const {
    // TODO : handle static object with inverseMass at 0
    assert(m_inverseMass != 0.0f);
    return 1.f / m_inverseMass;
}

// Set inverse mass
void Particle::setInverseMass(float inverseMass) {
    m_inverseMass = inverseMass;
}

// Set mass
void Particle::setMass(float mass) {
    // TODO : handle stuff when mass param is 0
    assert(mass != 0.0f);
    m_inverseMass = 1.0f / mass;
}

/* FORCE ACCUMULATOR */

// Add a force to the particle
void Particle::applyForce(const Vector3D& force) {
    m_forceAccum += force;
}

/* INTEGRATOR */

// Euler integration to update position and velocity
void Particle::integrate(float dt) {
    if (m_inverseMass <= 0.0f) return; // If the particle has infinite mass, do not move it

    // Update position using velocity
    m_position += m_velocity * dt;
    
    // Calculate acceleration from the accumulated force
    m_acceleration = m_forceAccum * m_inverseMass;
    
    // Update velocity using acceleration
    m_velocity += m_acceleration * dt;
    
    // Reset accumulated forces after integration
    clearForces();
}

// Reset the force accumulator
void Particle::clearForces() {
    m_forceAccum = Vector3D(0, 0, 0);
}

/* OPEN FRAMEWORK */

#include "ofMain.h"

void Particle::draw(float radius) const {
    ofDrawCircle(m_position.v2(), radius);
}
