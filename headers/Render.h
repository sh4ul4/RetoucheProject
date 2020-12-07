#pragma once
#ifndef RENDER_H
#define RENDER_H

#include "library.h"
#include "FrameRate.h"
#include "Draw.h"
#include "Window.h"

class Render
{
public:
	StableFramerate framerate;

	void init(Window* window) {
		SDL_GL_SetSwapInterval(0);
		//window->ToggleWindow(window->getWidth(), window->getHeight());
		InitMixer(8);
		TTF_Init();
		///SDL_ShowCursor(0);
	}
public:
	void render(InputEvent* inputEvent, Window* window) {
		if (inputEvent == nullptr || window == nullptr)exit(1);
		inputEvent->update();


		framerate.stabilizeCalculationAndRendering(60);
		//Wait(10);

		framerate.render(10, 10,window->getRenderer());
		window->RenderScreen();
		window->FillScreen(light_gray);
	}
};

#endif // !RENDER_H