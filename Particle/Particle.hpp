//
//  Particle.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "Vector/Vector3D.hpp"
#include <array>
#include <cmath>

class Particle {
    
protected:
    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration; // Acceleration resulting from applied forces
    Vector3D m_forceAccum;  // Accumulated forces
    Vector3D m_veloAccum;  // Accumulated velocity
    Vector3D m_dispAccum; // Accumulated displacement

    float m_friction;

    float m_mass;
    float m_inverseMass;   // Inverse of the mass (useful to avoid division)
    
    float m_radius;
    std::array<int, 3> m_color;

    bool m_isStaticObject;
public:
    /* CONSTRUCTORS */
    Particle(const Vector3D& position, const Vector3D& velocity, float mass, float radius);
    Particle(const Vector3D& position, const Vector3D& velocity, float mass, int red, int green, int blue, float radius, float friction = 1.0f, bool isStaticObject = false);
    
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

    // Radius
    float radius() const;

    float friction() const;

    // Gravity
    bool isStaticObject() const;

    // Force accumulator
    void addForce(const Vector3D& force);
    void addVelocity(const Vector3D& velo);
    void addDisplacement(const Vector3D& disp);
    
    /* INTEGRATORS */
    
    // Euler integration to update position and velocity
    void integrate(float duration);
    
    // Clear accumulated forces
    void clearForces();
    
    /* OPEN FRAMEWORK */
    void draw();
};

#endif /* Particle_hpp */
