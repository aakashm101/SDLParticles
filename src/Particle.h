#pragma once

struct Particle {
	double m_x;
	double m_y;

	double m_speed;
	double m_direction;

	Particle();
	void update(int interval);
};