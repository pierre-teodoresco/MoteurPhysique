#pragma once
#include <algorithm>
#include "..\Octree.h"
#include "Rigidbody.hpp"

// Constructeur
RigidBody::RigidBody(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float height, float width, float depth, const Quaternion& orientation) : Particle(position, velocity, mass, red, green, blue, std::min({ height, width, depth }), 0.0f, false),
    m_orientation(orientation), m_width(width), m_height(height), m_depth(depth) {
    setMass(mass);
    m_torqueAccum = Vector3D(0, 0, 0);
    m_angularVelocity = Vector3D(0, 0, 0);
    float data[3][3] = { {12 / (m_mass * (m_depth * m_depth + m_height * m_height)), 0, 0}, {0, 12 / (m_mass * (m_height * m_height + m_width * m_width)), 0}, {0, 0, 12 / (m_mass * (m_depth * m_depth + m_width * m_width))} }; //Inertia moment for a box
    m_uprightInverseInertiaTensor = Matrix3(data);
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

void RigidBody::addVelocity(const Vector3D& velo, const Vector3D& location)
{
    m_velocity += velo;

    Vector3D lever = location - m_position;
    m_angularVelocity += m_inverseInertiaTensor * lever * velo;
}

void RigidBody::integrate(float dt)
{
    if (m_inverseMass <= 0.0f || m_isStaticObject) return; // If the particle has infinite mass, do not move it

    updateInertiaTensor();
    Vector3D angularAcceleration = m_inverseInertiaTensor * m_torqueAccum;
    m_angularVelocity += angularAcceleration * dt;

    Quaternion angularVelocityQuat = Quaternion(0, m_angularVelocity.x(), m_angularVelocity.y(), m_angularVelocity.z());

    m_orientation = m_orientation + angularVelocityQuat * m_orientation * 0.5f * dt;
    m_orientation = m_orientation.Normalize();

    m_torqueAccum = Vector3D(0, 0, 0);

    Particle::integrate(dt);
}

// Mis a Jour du tenseur Inertie
void RigidBody::updateInertiaTensor() {
    m_inertiaTensor = Matrix3::identity();
    Matrix3 rotationMatrix = m_orientation.ToRotationMatrix3();
    m_inverseInertiaTensor = rotationMatrix * m_uprightInverseInertiaTensor * rotationMatrix.inverse(); //R * J^-1 * R^-1
}

// Convesion de la velocite angulaire en quaternion
Quaternion RigidBody::fromAngularVelocity(const Vector3D& angularVelocity, float dt) {
    float angle = angularVelocity.norm() * dt;
    Vector3D axis = angularVelocity.normalize();
    return Quaternion(cos(angle / 2), axis.x() * sin(angle / 2), axis.y() * sin(angle / 2), axis.z() * sin(angle / 2));
}