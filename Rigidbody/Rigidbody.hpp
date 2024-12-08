#pragma once

#include "../Vector/Vector3D.hpp"
#include "../Matrix/Matrix3.hpp"
#include "../Matrix/Matrix4.hpp"
#include "../Quaternion/Quaternion.h"
#include "Particle/Particle.hpp"

class RigidBody : public Particle {
public:
    Vector3D m_torqueAccum; // Force de torque
    Quaternion m_orientation; // Orientation du rigid body
    Vector3D m_angularVelocity; // Velocite Angulaire
    Matrix3 m_inertiaTensor; // Tenseur Inertie
    Matrix3 m_inverseInertiaTensor; // Inverse tenseur Inertie
    Matrix3 m_uprightInverseInertiaTensor; // Inverse tenseur Inertie quand l'objet n'a aucune rotation (J^-1)

    float m_width; //x size
    float m_height; //y size
    float m_depth; //z size

public:
    // Constructeur
    RigidBody(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue,  float width, float height, float depth, const Quaternion& orientation);

    // Setters
    void addForce(const Vector3D& force, const Vector3D& location);
    void addTorque(const Vector3D& torque);
    void addVelocity(const Vector3D& velo, const Vector3D& location);
    // Getters
    const Quaternion& orientation() const { return m_orientation; }
    const Vector3D& angularVelocity() const { return m_angularVelocity; }

    void integrate(float dt);

    
private:
    void updateInertiaTensor();
    Quaternion fromAngularVelocity(const Vector3D& angularVelocity, float dt);
};