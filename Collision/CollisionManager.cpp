#include "CollisionManager.h"

void CollisionManager::detectCollisions(std::vector<std::shared_ptr<Particle>> particles)
{
    //It�ration � travers chaque paire de particules
    for (int i = 0; i < particles.size(); i++)
    {
        std::shared_ptr<Particle> particleA = particles.at(i);
        for (int j = i + 1; j < particles.size(); j++)
        {
            std::shared_ptr<Particle> particleB = particles.at(j);

            //Calculer le vecteur distance entre les deux particules
            Vector3D dist = particleA->position() - particleB->position();

            //Si la distance est inf�rieure � la somme de leurs rayons, il ya collision
            if (dist.norm() < (particleA->radius() + particleB->radius()))
            {
                //Calculer de combien elles se p�n�trent l'une l'autre
                //puis r�duire le vecteur distance � cette taille
                float penetration = dist.norm() - (particleA->radius() + particleB->radius());
                Vector3D normal = dist.normalize(); //Vecteur unitaire dans la direction de B vers A
                Vector3D displacement = normal * penetration;

                //Calculer un nouveau vecteur "unitaire" repr�sentant le d�placement par unit� de masse 
                //pour �viter de devoir faire plusieurs divisions
                Vector3D dispPerMass = displacement / (particleA->mass() + particleB->mass());

                //Appliquer � chaque particule sa "part" du d�placement, bas�e sur la masse de l'autre
                particleA->addDisplacement(dispPerMass * (particleB->mass() * -1.0f));
                particleB->addDisplacement(dispPerMass * particleA->mass());

                float elasticity = 0.5f;
                float relativeVelocity = (particleA->velocity() - particleB->velocity()).dot(normal);
                float momentumTransfer = ((1 + elasticity) * relativeVelocity) / (particleA->inverseMass() + particleB->inverseMass());

                particleA->addVelocity(normal * momentumTransfer * particleA->inverseMass() * -1.0f);
                particleB->addVelocity(normal * momentumTransfer * particleB->inverseMass());
            }
        }
    }
}
