#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include "Particle.h"

Particle::Particle() :m_x(0), m_y(0) {
	m_direction = (2 * M_PI * std::rand()) / RAND_MAX;
	m_speed		= (0.04 * std::rand()) / RAND_MAX;
	m_speed		*= m_speed;
}

void Particle::update(int interval) {
	m_direction += interval * 0.0004;
	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);

	m_x += xspeed * interval;
	m_y += yspeed * interval;
}
