#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "library.h"

class Window {
	unsigned int width = NULL; unsigned int height = NULL;
	short int windowStatus = -1;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_AudioDeviceID deviceId = NULL;
	bool shuttingDown = false;
public:
	int getWidth(void)const { return width; }
	int getHeight(void)const { return height; }
	int getWidthCenter(void) const { return width / 2; }
	int getHeightCenter(void) const { return height / 2; }
	SDL_Renderer* getRenderer(void)const { return renderer; }
	SDL_Window* getWindow(void) const { return window; }
	Window() = delete;
	Window(int width, int height):width(width),height(height) {
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Init(SDL_INIT_TIMER);
		SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED, &window, &renderer);
	}
	void Shutdown(void) // Shuts down all the different components
	{
		std::cout << "Prepare to shut down.\n";
		shuttingDown = true;
		//---------------------------------------
		SDLK_CLEAR;
		std::cout << "Keys cleared.\n";
		//---------------------------------------
		Mix_FreeMusic(0);
		Mix_FreeChunk(0);
		std::cout << "Channels cleared.\n";
		//---------------------------------------
		Mix_Quit();
		std::cout << "Mixer cleared.\n";
		//---------------------------------------
		TTF_Quit();
		//---------------------------------------
		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		std::cout << "Renderer destroyed.\n";
		//---------------------------------------
		if (window) {
			SDL_DestroyWindow(window);
		}
		exit(0);
		std::cout << "Window destroyed.\n";
		//---------------------------------------
		int numclosed_f = _fcloseall();
		printf("Number of files closed by _fcloseall: %u\n", numclosed_f);
		//---------------------------------------
		std::cout << "Shutdown complete." << std::endl;
	}
	void Wait(int time)const // Pause everything for a certain time
	{
		SDL_Delay(time); // takes time in milliseconds
	}
	void FillScreen(const Color color)const
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); // set the requested color
		SDL_RenderClear(renderer);
	}
	void RenderScreen(void)const
	{
		SDL_RenderPresent(renderer);
	}
	void ToggleWindow(int width, int height) // Toggle the window between Fullscreen-mode and Windowed-mode
	{
		windowStatus *= -1;
		SDL_SetWindowResizable(window, SDL_TRUE);
		if (windowStatus == 1) {
			SDL_DisplayMode DM;
			SDL_GetCurrentDisplayMode(0, &DM);
			this->width = DM.w;
			this->height = DM.h;
			SDL_SetWindowSize(window, this->width, this->height);
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else if (windowStatus == -1) {
			this->width = width;
			this->height = height;
			SDL_SetWindowSize(window, this->width, this->height);
			SDL_SetWindowFullscreen(window, 0);
		}
		SDL_SetWindowResizable(window, SDL_FALSE);
	}
};

#endif // !WINDOW_H
