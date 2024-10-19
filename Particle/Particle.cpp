//
//  Particle.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
//

#include "Particle.hpp"

#include <stdexcept>

/* CONSTRUCTORS */
Particle::Particle(const Vector3D& position, const Vector3D& velocity, float mass, float radius) {
    Particle(position, velocity, mass, 255, 255, 255, radius);
}

Particle::Particle(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float radius)
    : m_position(position), m_velocity(velocity), m_forceAccum(0, 0, 0), m_veloAccum(0, 0, 0), m_dispAccum(0, 0, 0), m_acceleration(0, 0, 0) {
    setMass(mass); // Initialize mass (or inverse mass) here
    m_color = { red, green, blue };
    m_radius = radius;
}

/* SETTERS */

// Get Mass
float Particle::mass() const {
    if (m_inverseMass == 0.0f) {
        throw std::runtime_error("Mass of a static particle is infinite");
    }
    return 1.f / m_inverseMass;
}

// Set inverse mass
void Particle::setInverseMass(float inverseMass) {
    m_inverseMass = inverseMass;
}

// Set mass
void Particle::setMass(float mass) {
    if (mass == 0.0f) {
        throw std::runtime_error("Mass can't be null");
    }
    m_inverseMass = 1.0f / mass;
}

// Get Radius
float Particle::radius() const {
    return m_radius;
}

/* FORCE ACCUMULATOR */

// Add a force to the particle
void Particle::applyForce(const Vector3D& force) {
    m_forceAccum += force;
}

void Particle::applyVelocity(const Vector3D& velo) {
    m_veloAccum += velo;
}

void Particle::applyDisplacement(const Vector3D& disp) {
    m_dispAccum += disp;
}

/* INTEGRATOR */

// Euler integration to update position and velocity
void Particle::integrate(float dt) {
    if (m_inverseMass <= 0.0f) return; // If the particle has infinite mass, do not move it

    // Update position using accumulated displacement
    m_position += m_dispAccum;
    // Update position using velocity
    m_position += m_velocity * dt;
    
    // Calculate acceleration from the accumulated force
    m_acceleration = m_forceAccum * m_inverseMass;
    
    // Update velocity using accumulated velocity
    m_velocity += m_veloAccum;
    // Update velocity using acceleration
    m_velocity += m_acceleration * dt;
    
    // Reset accumulated forces after integration
    clearForces();
}

// Reset the force accumulator
void Particle::clearForces() {
    m_forceAccum = Vector3D(0, 0, 0);
    m_veloAccum = Vector3D(0, 0, 0);
    m_dispAccum = Vector3D(0, 0, 0);
}

/* OPEN FRAMEWORK */

#include "ofMain.h"

void Particle::draw() {
    ofSetColor(m_color[0], m_color[1], m_color[2]);
    ofDrawCircle(m_position.v3(), m_radius);
}
