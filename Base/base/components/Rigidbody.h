#pragma once

#include "Transform.h"

namespace base
{

class Rigidbody
{
public:
	float drag, mass;
	vec2 impulse, force, acceleration, velocity; // defaults to 0's

	float angularDrag;
	float spin, torque, angularAcceleration, angularVelocity;

	Rigidbody(float a_mass = 1)
				: spin(0), torque(0), angularAcceleration(0), angularVelocity(0),
				  drag(0), mass(a_mass), angularDrag(0) {}


	void addForce(const vec2 &a_force)	 { force += a_force; }
	void addImpulse(const vec2 &a_impulse) { impulse += a_impulse; }

	void addTorque(float a_torque) { torque += a_torque; }
	void addSpin(float a_spin)	   { spin += a_spin; }

	void integrate(Transform *T, float dt)
	{
		acceleration += force / mass;
		velocity += acceleration * dt + impulse / mass;
		T->setGlobalPosition(T->getGlobalPosition() + velocity * dt);
		acceleration = -velocity * drag;
		impulse = force = vec2{ 0,0 };

		angularAcceleration += torque / mass;
		angularVelocity += angularAcceleration * dt + spin / mass;
		T->setGlobalAngle(T->getGlobalAngle() + angularVelocity * dt);
		angularAcceleration = -angularVelocity * angularDrag;
		spin = torque = 0;
	}
};

}