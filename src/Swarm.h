#pragma once
#include "Particle.h"
#include "SDL.h"

class Swarm{
private:
	Particle* m_particles;
	int lastTime;
public:
	static const int NPARTICLES = 5000;
	Swarm();
	~Swarm();
	const Particle* const getParticles();
	void update(int elapsed);
};