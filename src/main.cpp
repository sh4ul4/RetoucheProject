#include <iostream>
#include "library.h"
#include "Window.h"

#include "library.h"
#include "Input.h"
#include "Window.h"
#include "Render.h"
#include "Draw.h"
#include "Panel.h"

int main(int argc, char* argv[]) {

	Window window(1200, 600);
	InputEvent inputEvent;
	Render render;
	render.init(&window);

	PanelManager pm;
	pm.addPanel({ 0,0 }, { 100,100 });
	pm.addPanel({ 300,10 }, { 100,150 });
	pm.addPanel({ 340,60 }, { 100,150 });

	while (!inputEvent.keyboard.escape) {
		render.render(&inputEvent,&window);
		pm.checkForIntercation(inputEvent);
		pm.render(window);
	}
	window.Shutdown();
	return 0;
}