#pragma once

#include "Transform.h"



namespace base
{
	class Collider
	{		
		hull m_hull;
		aabb m_localBox;

	public:
		Collider(float radius = 0.5f)		     : m_hull(radius)     { m_localBox = m_hull.boundingBox(); }
		Collider(const vec2 *ccw, size_t a_size) : m_hull(ccw,a_size) { m_localBox = m_hull.boundingBox(); }
		Collider(const hull &a_hull)             : m_hull(a_hull)     { m_localBox = m_hull.boundingBox(); }

		const aabb &getLocalBounds() const { return m_localBox; }	
		const aabb &getGlobalBounds(const Transform *T) const { return T->getGlobalTransform() * m_localBox; }

		const hull &getLocalHull() const { return m_hull; }
		const hull &getGlobalHull(const Transform *T) const { return T->getGlobalTransform() * m_hull; }
	};

	bool BoundsTest(const Transform *AT, const Collider *AC,
					const Transform *BT, const Collider *BC)
	{
		auto A = AC->getGlobalBounds(AT);
		auto B = BC->getGlobalBounds(BT);

		return overlap(A, B);
	}


	collision ColliderTest(const Transform *AT, const Collider *AC,
						   const Transform *BT, const Collider *BC)
	{
		auto A = AC->getGlobalHull(AT);
		auto B = BC->getGlobalHull(BT);

		return collides(A, B);
	}
}