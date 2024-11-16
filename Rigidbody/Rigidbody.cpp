#pragma once
#include "Rigidbody.hpp"

// Constructeur
RigidBody::RigidBody(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float radius, const Quaternion& orientation) : Particle(position, velocity, mass, red, green, blue, radius, 0.0f, false),
    m_mass(mass), m_position(position), m_orientation(orientation) {
    setMass(mass);
    m_linearVelocity = Vector3D(0, 0, 0);
    m_angularVelocity = Vector3D(0, 0, 0);
    m_forceAccum = Vector3D(0, 0, 0);
    m_torqueAccum = Vector3D(0, 0, 0);
    updateInertiaTensor(); // Initialise le Tenseur d'inertie
}

// Ajout des forces au corps rigide
void RigidBody::addForce(const Vector3D& force, const Vector3D& location) {
    m_forceAccum += force;
    Vector3D lever = location - m_position;
    addTorque(lever * force);
}

// Ajout du torque au corps rigide
void RigidBody::addTorque(const Vector3D& torque) {
    m_torqueAccum += torque;
}

void RigidBody::integrate(float dt)
{
    if (m_inverseMass <= 0.0f || m_isStaticObject) return; // If the particle has infinite mass, do not move it

// Update position using accumulated displacement
    m_position += m_dispAccum;

    // Calculate acceleration from the accumulated force
    m_acceleration = m_forceAccum * m_inverseMass;

    // Update velocity using accumulated velocity
    //m_velocity += m_veloAccum;
    // Update velocity using acceleration
    m_velocity += m_acceleration * dt;
    // Apply air drag
    m_velocity *= std::pow(0.9f, dt);

    // Update position using velocity
    m_position += m_velocity * dt;

    // Reset accumulated forces after integration
    clearForces();

}

// Mis a Jour du tenseur Inertie
void RigidBody::updateInertiaTensor() {
    m_inertiaTensor = Matrix3::identity();
    m_inverseInertiaTensor = Matrix3::identity();
}

// Convesion de la velocite angulaire en quaternion
Quaternion RigidBody::fromAngularVelocity(const Vector3D& angularVelocity, float dt) {
    float angle = angularVelocity.norm() * dt;
    Vector3D axis = angularVelocity.normalize();
    return Quaternion(cos(angle / 2), axis.x() * sin(angle / 2), axis.y() * sin(angle / 2), axis.z() * sin(angle / 2));
}