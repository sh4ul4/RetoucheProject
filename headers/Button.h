#pragma once
#include "Point.h"
#include "Window.h"
#include "Draw.h"

struct Button {
	Button() {
		position = size = { 0,0 };
	}
	Button(const Point2& pos, const int& w, const int& h) :position(pos), size({ w,h }) {
		if (size.x < 0 || size.y < 0) { std::cout << "Error: size can't be negative" << std::endl; exit(1); }
	}
	Point2 position;
	Point2 size;
	bool inside(const Point2& p)const {
		return p.x <= position.x + size.x && p.y <= position.y + size.y && p.x >= position.x && p.y >= position.y;
	}
	void render(const Point2& panelPosition, const Color& col, const Window& w)const {
		Draw::DrawLine(panelPosition + position, panelPosition + Point2(position.x + size.x, position.y), col, w.getRenderer());
		Draw::DrawLine(panelPosition + Point2(position.x + size.x, position.y), panelPosition + position + size, col, w.getRenderer());
		Draw::DrawLine(panelPosition + position + size, panelPosition + Point2(position.x, position.y + size.y), col, w.getRenderer());
		Draw::DrawLine(panelPosition + Point2(position.x, position.y + size.y), panelPosition + position, col, w.getRenderer());
	}
	void render(const Point2& panelPosition, const Color& col, const Window& w, const std::string& text)const {
		Draw::RenderString(panelPosition.x + position.x + 2, panelPosition.y + position.y + 2, 6, text, col, w.getRenderer());

		Draw::DrawLine(panelPosition + position, panelPosition + Point2(position.x + size.x, position.y), col, w.getRenderer());
		Draw::DrawLine(panelPosition + Point2(position.x + size.x, position.y), panelPosition + position + size, col, w.getRenderer());
		Draw::DrawLine(panelPosition + position + size, panelPosition + Point2(position.x, position.y + size.y), col, w.getRenderer());
		Draw::DrawLine(panelPosition + Point2(position.x, position.y + size.y), panelPosition + position, col, w.getRenderer());
	}
};