#include "CollisionManager.h"
#include "Force/Friction/ParticleFriction.hpp"

void CollisionManager::detectParticleCollisions(std::vector<std::shared_ptr<Particle>> particles, std::shared_ptr<ParticleForceRegistry> registry, float minSpeed, float frameTime)
{
    //Itération à travers chaque paire de particules
    for (int i = 0; i < particles.size(); i++)
    {
        std::shared_ptr<Particle> particleA = particles.at(i);
        for (int j = i + 1; j < particles.size(); j++)
        {
            std::shared_ptr<Particle> particleB = particles.at(j);

            //Calculer le vecteur distance entre les deux particules
            Vector3D dist = particleA->position() - particleB->position();

            //Si la distance est inférieure à la somme de leurs rayons, il ya collision
            if (dist.norm() < (particleA->radius() + particleB->radius()))
            {
                //Calculer de combien elles se pénètrent l'une l'autre
                //puis réduire le vecteur distance à cette taille
                float penetration = dist.norm() - (particleA->radius() + particleB->radius());
                Vector3D normal = dist.normalize(); //Vecteur unitaire dans la direction de B vers A
                Vector3D displacement = normal * penetration;

                //Calculer un nouveau vecteur "unitaire" représentant le déplacement par unité de masse 
                //pour éviter de devoir faire plusieurs divisions
                Vector3D dispPerMass = displacement / (particleA->mass() + particleB->mass());

                //Appliquer à chaque particule sa "part" du déplacement, basée sur la masse de l'autre
                particleA->addDisplacement(dispPerMass * (particleB->mass() * -1.0f));
                particleB->addDisplacement(dispPerMass * particleA->mass());

                
                //Vitesse relative entre les deux particules, positif = elles s'éloignent l'une de l'autre
                float relativeSpeed = (particleA->velocity() - particleB->velocity()).dot(normal); 

                //Constante d'élasticité
                float elasticity;

                //Donc si la vitesse relative n'est pas négative (ou est très petite dans les négatifs), absorber tout le mouvement
                if (relativeSpeed < -minSpeed * frameTime)
                {
                    elasticity = 0.5f;
                }
                else
                {
                    elasticity = 0.0f;
                }

                if (relativeSpeed < 0)
                {
                    float momentumTransfer = ((1 + elasticity) * relativeSpeed) / (particleA->inverseMass() + particleB->inverseMass());

                    particleA->addVelocity(normal * momentumTransfer * particleA->inverseMass() * -1.0f);
                    particleB->addVelocity(normal * momentumTransfer * particleB->inverseMass());

                    registry->add(particleA, std::make_shared<ParticleKineticFriction>(particleB->friction(), -relativeSpeed));
                    registry->add(particleB, std::make_shared<ParticleKineticFriction>(particleA->friction(), -relativeSpeed));
                }
            }
        }
    }
}

void CollisionManager::detectCollisions(std::vector<std::shared_ptr<Cube>> cubes, std::shared_ptr<ParticleForceRegistry>, float minSpeed, float frameTime)
{
    for (auto i : cubes)
    {
        std::vector<Vector3D> otherVertices = i->getVertices();
        for (auto j : cubes)
        {
            if (i != j)
            {
                for (auto v : j->getVertices())
                {
                    //front face
                    std::vector<Vector3D> normals;
                    normals.push_back((otherVertices.at(1) - otherVertices.at(0)).normalize());
                    Vector3D point = otherVertices.at(1);
                    float t = normals.at(0).dot((v - point));
                    float maxPenetration = t;
                    int penetrationNormalIndex = 0;

                    //left face
                    normals.push_back((otherVertices.at(0) - otherVertices.at(4)).normalize());
                    point = otherVertices.at(0);
                    t = normals.at(1).dot((v - point));
                    if (t > maxPenetration)
                    {
                        maxPenetration = t;
                        penetrationNormalIndex = 1;
                    }

                    //top face
                    normals.push_back((otherVertices.at(2) - otherVertices.at(0)).normalize());
                    point = otherVertices.at(2);
                    t = normals.at(2).dot((v - point));
                    if (t > maxPenetration)
                    {
                        maxPenetration = t;
                        penetrationNormalIndex = 2;
                    }

                    //back face
                    normals.push_back((otherVertices.at(0) - otherVertices.at(1)).normalize());
                    point = otherVertices.at(0);
                    t = normals.at(3).dot((v - point));
                    if (t > maxPenetration)
                    {
                        maxPenetration = t;
                        penetrationNormalIndex = 3;
                    }

                    //right face
                    normals.push_back((otherVertices.at(4) - otherVertices.at(0)).normalize());
                    point = otherVertices.at(4);
                    t = normals.at(4).dot((v - point));
                    if (t > maxPenetration)
                    {
                        maxPenetration = t;
                        penetrationNormalIndex = 4;
                    }

                    //bottom face
                    normals.push_back((otherVertices.at(0) - otherVertices.at(2)).normalize());
                    point = otherVertices.at(0);
                    t = normals.at(5).dot((v - point));
                    if (t > maxPenetration)
                    {
                        maxPenetration = t;
                        penetrationNormalIndex = 5;
                    }

                    if (maxPenetration < 0)
                    {
                        Vector3D displacement = normals.at(penetrationNormalIndex) * maxPenetration;
                        Vector3D dispPerMass = displacement / (i->mass() + j->mass());

                        //Appliquer à chaque cube sa "part" du déplacement, basée sur la masse de l'autre
                        i->addDisplacement(dispPerMass * (j->mass() * -1.0f));
                        j->addDisplacement(dispPerMass * i->mass());

                        //Vitesse relative entre les deux cubes, positif = elles s'éloignent l'une de l'autre
                        float relativeSpeed = (i->velocity() - j->velocity()).dot(normals.at(penetrationNormalIndex));

                        //Constante d'élasticité
                        float elasticity;

                        //Donc si la vitesse relative n'est pas négative (ou est très petite dans les négatifs), absorber tout le mouvement
                        if (relativeSpeed < -minSpeed * frameTime)
                        {
                            elasticity = 0.5f;
                        }
                        else
                        {
                            elasticity = 0.0f;
                        }

                        if (relativeSpeed < 0)
                        {
                            float momentumTransfer = ((1 + elasticity) * relativeSpeed) / (i->inverseMass() + j->inverseMass());

                            i->addVelocity(normals.at(penetrationNormalIndex) * momentumTransfer * i->inverseMass() * -1.0f, v);
                            j->addVelocity(normals.at(penetrationNormalIndex) * momentumTransfer * j->inverseMass(), v);
                        }
                        return;
                    }
                    
                }
            }
        }
    }
}

