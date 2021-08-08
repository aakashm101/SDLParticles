#pragma once
#include <iostream>
#include <SDL.h>

class Screen {
private:
	SDL_Window*		m_window;
	SDL_Renderer*	m_renderer;
	SDL_Texture*	m_texture;
	Uint32*			m_buffer1;
	Uint32*			m_buffer2;
public:
	static const int SCREEN_WIDTH	= 800;
	static const int SCREEN_HEIGHT	= 600;
	Screen();
	bool init();
	bool processEvents();
	void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
	void boxBlur();
	void update();
	void close();
};