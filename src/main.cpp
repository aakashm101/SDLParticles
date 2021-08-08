#define SDL_MAIN_HANDLED  // Required. Refer https://wiki.libsdl.org/SDL_Init
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "Screen.h"
#include "Swarm.h"

int main() {
	SDL_SetMainReady();	// Required. Refer https://wiki.libsdl.org/SDL_Init
	std::srand((double)std::time(NULL)); // Seed the random number generator

	Screen screen;
	screen.init();

	Swarm swarm;

	while (true) {
		Uint32 elapsed = SDL_GetTicks();
		swarm.update(elapsed);

		const double RED_SMOOTHING_FACTOR = 0.0001;
		const double GREEN_SMOOTHING_FACTOR = 0.0002;
		const double BLUE_SMOOTHING_FACTOR = 0.0003;

		//screen.clear();
		screen.boxBlur();

		const Particle* const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];
			unsigned char red = (sin(elapsed * RED_SMOOTHING_FACTOR) + 1) * 128;
			unsigned char green = (sin(elapsed * GREEN_SMOOTHING_FACTOR) + 1) * 128;
			unsigned char blue = (sin(elapsed * BLUE_SMOOTHING_FACTOR) + 1) * 128;

			int x = (particle.m_x + 1) * ((double)Screen::SCREEN_WIDTH / 2);
			int y = (particle.m_y * (double)Screen::SCREEN_WIDTH / 2) + ((double)Screen::SCREEN_HEIGHT / 2);
			screen.setPixel(x, y, red, blue, green);
		}

		screen.update();
		if (screen.processEvents() == false) {
			break;
		}
	}

	screen.close();
	return 0;
}