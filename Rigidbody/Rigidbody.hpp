#pragma once

#include "../Vector/Vector3D.hpp"
#include "../Matrix/Matrix3.hpp"
#include "../Matrix/Matrix4.hpp"
#include "../Quaternion/Quaternion.h"
#include "Particle/Particle.hpp"

class RigidBody : public Particle {
private:
    float m_mass; // Masse du rigid body
    float m_inverseMass; // Inverse de la masse
    Vector3D m_position; // Position du rigid body
    Vector3D m_linearVelocity; // Velocite Lineaire
    Vector3D m_angularVelocity; // Velocite Angulaire
    Vector3D m_forceAccum; // Force accumule par le rigidbody
    Vector3D m_torqueAccum; // Force de torque

    Quaternion m_orientation; // Orientation du rigid body
    Matrix3 m_inertiaTensor; // Tenseur Inertie
    Matrix3 m_inverseInertiaTensor; // Inverse tenseur Inertie

public:
    // Constructeur
    RigidBody(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float radius, const Quaternion& orientation);

    // Setters
    void addForce(const Vector3D& force, const Vector3D& location);
    void addTorque(const Vector3D& torque);

    // Getters
    const Quaternion& orientation() const { return m_orientation; }
    const Vector3D& linearVelocity() const { return m_linearVelocity; }
    const Vector3D& angularVelocity() const { return m_angularVelocity; }

    void integrate(float dt);

    
private:
    void updateInertiaTensor();
    Quaternion fromAngularVelocity(const Vector3D& angularVelocity, float dt);
};