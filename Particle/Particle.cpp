//
//  Particle.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
//

#include "Particle.hpp"

#include <stdexcept>
#include <array>

float currentRadius; //Rayon de la particule
std::array<int, 3> currentColor; //Couleur de la particule

/* CONSTRUCTORS */
Particle::Particle(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float radius)
    : m_position(position), m_velocity(velocity), m_forceAccum(0, 0, 0), m_acceleration(0, 0, 0){
    setMass(mass); // Initialize mass (or inverse mass) here
    currentColor = { red, green, blue };
    currentRadius = radius;
}

/* SETTERS */

// Get Mass
float Particle::mass() const {
    if (m_inverseMass == 0.0f) {
        throw std::runtime_error("Mass can't be null");
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

void Particle::draw() const {
    ofSetColor(currentColor[0], currentColor[1], currentColor[2]);
    ofDrawCircle(m_position.v3(), currentRadius);
}
