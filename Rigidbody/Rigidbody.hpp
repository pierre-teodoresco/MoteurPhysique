#pragma once

#include "../Vector/Vector3D.hpp"
#include "../Matrix/Matrix3.hpp"
#include "../Matrix/Matrix4.hpp"
#include "../Quaternion/Quaternion.h"

class RigidBody {
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
    RigidBody(float mass, const Vector3D& position, const Quaternion& orientation);

    // Setters
    void setMass(float mass);
    void addForce(const Vector3D& force);
    void addTorque(const Vector3D& torque);

    // Getters
    const Vector3D& position() const { return m_position; }
    const Quaternion& orientation() const { return m_orientation; }
    const Vector3D& linearVelocity() const { return m_linearVelocity; }
    const Vector3D& angularVelocity() const { return m_angularVelocity; }

    void integrate(float dt);

    
private:
    void updateInertiaTensor();
    Quaternion fromAngularVelocity(const Vector3D& angularVelocity, float dt);
};