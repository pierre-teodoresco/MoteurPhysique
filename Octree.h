#ifndef OCTREE_H
#define OCTREE_H

#include "Rigidbody/Rigidbody.hpp"
#include "Vector\Vector3D.hpp"
#include <vector>
#include <memory>

struct SphereBound {
	Vector3D center;
	float radius;

	SphereBound(const Vector3D& center, float radius) : center(center), radius(radius){}

	bool isspherecolide(const SphereBound& other) const
	{
		float distance = (center - other.center).squaredNorm();
		float c_Radius = radius + other.radius;

		return distance <= (c_Radius * c_Radius);
	}
};

class Octree {
public:
	Octree(const SphereBound& limit, int size);

	bool insert(const std::shared_ptr<RigidBody>& object);
	void checkRange(const SphereBound& range, std::vector<std::shared_ptr<RigidBody>>& n_objects) const;

private:
	SphereBound s_limit; // Limite de la sphere englobante
	int s_size; //taille max de la sphere
	bool isdivided;

	std::vector<std::shared_ptr<RigidBody>>cell_objects; // Objects deja present dans la sphere

	//Sous cellules division de l'octree en 8
	std::unique_ptr<Octree> m_children[8];

	void cellDivide();
};

#endif OCTREE_H