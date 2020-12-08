#include <iostream>
#include "library.h"
#include "Window.h"

#include "library.h"
#include "Input.h"
#include "Window.h"
#include "Render.h"
#include "Draw.h"
#include "Texture.h"
#include "Panel.h"

int main(int argc, char* argv[]) {

	Window window(1200, 600);
	InputEvent inputEvent;
	Render render;
	render.init(&window);

	TextureManager tm;
	tm.addTexture("../input/rgba.png", window.getRenderer());

	PanelManager pm;
	pm.addPanel({ 0,0 }, { 400,400 });
	pm.addPanel(300, 10, 600, 450, tm.at(0));
	pm.addPanel({ 340,60 }, { 100,150 });

	while (!inputEvent.keyboard.escape) {
		render.render(&inputEvent,&window);
		pm.checkForIntercation(inputEvent);
		pm.render(window);
		if(inputEvent.keyboard.f)pm.applyFilter(2, window);
	}
	window.Shutdown();
	return 0;
}