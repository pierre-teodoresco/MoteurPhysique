//
//  Ballistic.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 18/09/2024.
//

#ifndef Ballistic_hpp
#define Ballistic_hpp

#include "Vector3D/Vector3D.hpp"
#include "Force/ParticleForceGenerator.hpp"
#include "Force/ParticleForceRegistry.hpp"
#include "Force/Gravity/ParticleGravity.hpp"
#include <memory>
#include <vector>
#include <array>
#include <string>
#include <limits>

namespace Ballistic {

Vector3D gravityVector = Vector3D(0, 981.f, 0);
float gravityNorm = gravityVector.norm();
auto gravity = std::make_shared<ParticleGravity>(gravityVector);

void setup();
void update();
void draw();
void exit();
void createParticle(char type);
void mousePressed(int x, int y);  // Gérer le clic de la souris
Vector3D getGravity();

}

#endif /* Ballistic_hpp */

