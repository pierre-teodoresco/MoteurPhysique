//
//  Ballistic.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 18/09/2024.
//

#ifndef Ballistic_hpp
#define Ballistic_hpp

#include "Particle/Particle.hpp"
#include <vector>

namespace Ballistic {

static Particle* p;
static std::vector<Vector3D> trajectory;

void setup();
void update();
void draw();
void exit();

}

#endif /* Ballistic_hpp */
