//
//  Particle.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "Vector3D.hpp"

class Particle {
    
private:
    Vector3D m_position;  // Particle's position
    Vector3D m_velocity;  // Particle's velocity
    Vector3D m_acceleration; // Acceleration resulting from applied forces
    Vector3D m_forceAccum;  // Accumulated forces

    float m_inverseMass;   // Inverse of the mass (useful to avoid division)
    
public:
    /* CONSTRUCTORS */
    Particle(const Vector3D& position, const Vector3D& velocity, float mass);
    
    /* DESTRUCTOR */
    ~Particle() = default;
    
    /* GETTERS */
    
    // Position, velocity, and acceleration
    Vector3D position() const;
    Vector3D velocity() const;
    Vector3D acceleration() const;

    // Inverse mass
    float inverseMass() const;
    void setInverseMass(float inverseMass);
    
    // Mass
    void setMass(float mass);
    
    // Force accumulator
    void addForce(const Vector3D& force);
    
    /* INTEGRATORS */
    
    // Euler integration to update position and velocity
    void integrate(float duration);
    
    // Clear accumulated forces
    void clearForces();
    
    /* OPEN FRAMEWORK */
    void draw() const;
};

#endif /* Particle_hpp */
