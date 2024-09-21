// Particles.hpp

#ifndef Particles_hpp
#define Particles_hpp

#include "Vector3D.hpp"

class Particles {
public:
    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;
    float m_inverseMass;

    void setPosition(Vector3D position);
    void setVelocity(Vector3D velocity);
    void setAcceleration(Vector3D acceleration);
    void setMass(float mass);

    
    Vector3D getPosition();
    Vector3D getVelocity();
    Vector3D getAcceleration();
    float getInverseMass();

    // Constructeur
    Particles(Vector3D position = Vector3D(), Vector3D velocity = Vector3D(), Vector3D acceleration = Vector3D(), float mass = 1.0f);


    void integrateEuler(float deltaTime);
};

#endif /* Particles_hpp */
