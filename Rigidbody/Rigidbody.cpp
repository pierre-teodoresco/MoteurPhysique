#pragma once
#include "Rigidbody.hpp"

// Constructeur
RigidBody::RigidBody(float mass, const Vector3D& position, const Quaternion& orientation)
    : m_mass(mass), m_position(position), m_orientation(orientation) {
    setMass(mass);
    m_linearVelocity = Vector3D(0, 0, 0);
    m_angularVelocity = Vector3D(0, 0, 0);
    m_forceAccum = Vector3D(0, 0, 0);
    m_torqueAccum = Vector3D(0, 0, 0);
    updateInertiaTensor(); // Initialise le Tenseur d'inertie
}

// Definition et calcul de l'inverseMasse
void RigidBody::setMass(float mass) {
    m_mass = mass;
    m_inverseMass = (mass > 0.0f) ? 1.0f / mass : 0.0f;
}

// Ajout des forces au corps rigide
void RigidBody::addForce(const Vector3D& force) {
    m_forceAccum += force;
}

// Ajout du torque au corps rigide
void RigidBody::addTorque(const Vector3D& torque) {
    m_torqueAccum += torque;
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