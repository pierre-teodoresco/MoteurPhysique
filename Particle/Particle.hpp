//
//  Particle.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "Vector3D/Vector3D.hpp"
#include <array>

class Particle {
    
private:
    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration; // Acceleration resulting from applied forces
    Vector3D m_forceAccum;  // Accumulated forces

    float m_inverseMass;   // Inverse of the mass (useful to avoid division)
    
    float m_radius;
    std::array<int, 3> m_color;
public:
    /* CONSTRUCTORS */
    Particle(const Vector3D& position, const Vector3D& velocity, float mass, float radius);
    Particle(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float radius);
    
    /* DESTRUCTOR */
    ~Particle() = default;
        
    // Position, velocity, and acceleration
    inline const Vector3D& position() const { return m_position; }
    inline const Vector3D& velocity() const { return m_velocity; }
    inline const Vector3D& acceleration() const { return m_acceleration; }

    // Inverse mass
    inline float inverseMass() const { return m_inverseMass; }
    void setInverseMass(float inverseMass);
    
    // Mass
    float mass() const;
    void setMass(float mass);
    
    // Force accumulator
    void applyForce(const Vector3D& force);
    
    /* INTEGRATORS */
    
    // Euler integration to update position and velocity
    void integrate(float duration);
    
    // Clear accumulated forces
    void clearForces();
    
    /* OPEN FRAMEWORK */
    void draw();
};

#endif /* Particle_hpp */
