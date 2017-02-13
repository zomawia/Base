#pragma once


class Lifetime
{
	float m_lifetime;
public:
	float lifespan;

	Lifetime(float a_span = 1) : lifespan(a_span), m_lifetime(0) {}

	void age(float dt) { m_lifetime += dt; }

	bool isAlive() const { return m_lifetime < lifespan; }
	float pctDead() const { return m_lifetime / lifespan; }
	void reset() { m_lifetime = 0; }
};