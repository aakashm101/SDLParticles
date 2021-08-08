#include "Swarm.h"

Swarm::Swarm() :lastTime(0) {
	m_particles = new Particle[NPARTICLES];
}

Swarm::~Swarm() {
	delete[] m_particles;
}

const Particle* const Swarm::getParticles() {
	return m_particles;
}

void Swarm::update(int elapsed) {
	int interval = elapsed - lastTime;
	for (int i = 0; i < Swarm::NPARTICLES; i++) {
		m_particles[i].update(interval);
	}
	lastTime = elapsed;
}
