#include "Screen.h"

Screen::Screen() {
	m_window	= NULL;
	m_renderer	= NULL;
	m_texture	= NULL;
	m_buffer1	= NULL;
	m_buffer2	= NULL;
}

bool Screen::init() {
	m_window = SDL_CreateWindow("Particles-by Aakash M (based on 'C++ for Complete Beginners' course by John Purcell)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (m_window == NULL) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (m_texture == NULL) {
		std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	return true;
}

bool Screen::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {		// Check for SDL events
		if (event.type == SDL_QUIT || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN) {	// If it is a quit event, exit application
			return false;
		}
	}
	return true;
}

void Screen::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	Uint32 pixel = 0;
	const int a = 0xFF;
	pixel += a; pixel <<= 8;
	pixel += r; pixel <<= 8;
	pixel += g; pixel <<= 8;
	pixel += b;

	m_buffer1[(y * SCREEN_WIDTH) + x] = pixel;
}

void Screen::boxBlur() {
	// Swap buffers
	Uint32* temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			// Applying box blur
			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentx = x + col;
					int currenty = y + row;

					if (currentx >= 0 && currentx < SCREEN_WIDTH && currenty >= 0 && currenty < SCREEN_HEIGHT) {
						Uint32 pixel = m_buffer2[(currenty * SCREEN_WIDTH) + currentx];
						Uint8 red = pixel & 0x00FF0000;
						Uint8 green = pixel & 0x0000FF00;
						Uint8 blue = pixel & 0x000000FF;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			setPixel(x, y, red, green, blue);
		}
	}
}

void Screen::update() {
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void Screen::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}