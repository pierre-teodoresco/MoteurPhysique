#include "Octree.h"
#include "iostream"

Octree::Octree(const SphereBound& limit, int size) : s_limit(limit), s_size(size), isdivided(false)
{}

bool Octree::insert(const std::shared_ptr<RigidBody>& object)
{
	if (!s_limit.isspherecolide(*object->sphereBound)) {
		return false;
	}

	if (cell_objects.size() < s_size && !isdivided) {
		cell_objects.push_back(object);
		return true;
	}

	if (!isdivided) {
		cellDivide();
	}

	for (auto& child : m_children) {
		if (child->insert(object)) {
			return true;
		}
	}
	return false;
}

void Octree::checkRange(const SphereBound& range, std::vector<std::shared_ptr<RigidBody>>& n_objects) const {
	if (!s_limit.isspherecolide(range)) {
		return;
	}

	for (const auto& object : cell_objects) {
		if (range.isspherecolide(*object->sphereBound)) {
			n_objects.push_back(object);
		}
	}

	if (isdivided) {
		for (const auto& child : m_children) {
			child->checkRange(range, n_objects);
		}
	}
}

void Octree::cellDivide()
{
	float n_radius = s_limit.radius / 2.0f;
	Vector3D center = s_limit.center;

	m_children[0] = std::make_unique<Octree>(SphereBound(center + Vector3D(-n_radius, -n_radius, -n_radius), n_radius), s_size);
	m_children[1] = std::make_unique<Octree>(SphereBound(center + Vector3D(n_radius, -n_radius, -n_radius), n_radius), s_size);
	m_children[2] = std::make_unique<Octree>(SphereBound(center + Vector3D(-n_radius, n_radius, -n_radius), n_radius), s_size);
	m_children[3] = std::make_unique<Octree>(SphereBound(center + Vector3D(n_radius, n_radius, -n_radius), n_radius), s_size);
	m_children[4] = std::make_unique<Octree>(SphereBound(center + Vector3D(-n_radius, -n_radius, n_radius), n_radius), s_size);
	m_children[5] = std::make_unique<Octree>(SphereBound(center + Vector3D(n_radius, -n_radius, n_radius), n_radius), s_size);
	m_children[6] = std::make_unique<Octree>(SphereBound(center + Vector3D(-n_radius, n_radius, n_radius), n_radius), s_size);
	m_children[7] = std::make_unique<Octree>(SphereBound(center + Vector3D(n_radius, n_radius, n_radius), n_radius), s_size);

	isdivided = true;
}