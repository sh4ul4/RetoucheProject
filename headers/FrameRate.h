#pragma once
#ifndef FRAMERATE_H
#define FRAMERATE_H
#include "library.h"
#include "Draw.h"
#include "Window.h"

struct Chrono {
private:
	int start_c = NULL;
	int stop_c = NULL;
public:
	bool set(const unsigned int& end)
	{
		start_c = SDL_GetTicks(); // gets current time
		if (stop_c == NULL)
		{
			stop_c = start_c + end; // inits chrono
		}
		if (start_c > stop_c)
		{
			start_c = NULL;
			stop_c = NULL;
			return 1; // returns 1 if time is elapsed
		}
		return 0; // returns 0 in case chrono is still runnning
	}
	bool isElapsed(void) {
		start_c = SDL_GetTicks(); // gets current time
		if (start_c > stop_c)
		{
			start_c = NULL;
			stop_c = NULL;
			return 1; // returns 1 if time is elapsed
		}
		return 0; // returns 0 in case chrono is still runnning
	}
};

class StableFramerate {
private:
	unsigned long long int frameCounter = 0; // increments by 1 with each frame
	double nextTime = NULL; // next time a frame is rendered
	Chrono chrono; // wait for 1000
	short int frames = NULL; // adds 1 per frame
	short int framerate = NULL;
	double now = NULL; // SDL_GetTicks()
public:
	void stabilizeCalculationAndRendering(const double& TickInterval = 0) // limit calculation and rendering
	{
		if (TickInterval == 60) { nextTime += 17; }
		else { nextTime += 1.621059 + (181237898.4) / (1 + pow(TickInterval / 0.0000460458, 1.156912)); }
		now = SDL_GetTicks(); // current time in SDL_Ticks
		if (nextTime > now) {
			SDL_Delay(Uint32(nextTime - now)); // time to wait before rendering next frame
		}
	}
	void stabilizeRendering(const Window& window, double TickInterval = 0) // limit rendering
	{
		// optimized formula with approximative constants
		if (TickInterval == 60) { TickInterval = 17; }
		else { TickInterval = 1.621059 + (181237898 / (1 + pow(TickInterval / 0.0000460458, 1.156912))); }
		now = SDL_GetTicks(); // current time in SDL_Ticks
		if (nextTime == 0) { nextTime = now + TickInterval; }
		if (nextTime < now) {
			window.RenderScreen();
			nextTime = 0;
		}
	}
	void render(const int& X, const int& Y, SDL_Renderer* renderer)
	{
		frames++;
		if (chrono.set(1000)) {
			framerate = frames; // return the framerate after 1 sec
			frames = 0;
		}
		Draw::RenderDigits(X, Y, 8, framerate, red, renderer);
	}
	void newFrame(void) {
		frameCounter++;
	}
};

#endif // !FRAMERATE_H