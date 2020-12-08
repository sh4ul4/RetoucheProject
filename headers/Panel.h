#pragma once

#include <iostream>
#include "Point.h"
#include "Shape.h"
#include "Input.h"
#include <vector>

class Panel {
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
	};
	// Panel variables
	Point2 position;
	Point2 size;
	std::vector<Shape> shapes;
	bool isActive = false;
	Button moveButton;
	Button closeButton;
	Texture texture;
	// style-sheet
	int buttonsize = 10;
public:
	Panel() = delete;
	Panel(const Point2& position, const Point2& size) :position(position), size(size) {
		if (size.x < 0 || size.y < 0) { std::cout << "Error: size can't be negative" << std::endl; exit(1); }
		moveButton = Button({ 0,0 }, 10, 10);
		closeButton = Button({ size.x - 10,0 }, 10, 10);
	}
	Panel(const int& x, const int& y, const int& w, const int& h) :position({ x,y }), size({ w,h }) {
		if (size.x < 0 || size.y < 0) { std::cout << "Error: size can't be negative" << std::endl; exit(1); }
		moveButton = Button({ 0,0 }, 10, 10);
		closeButton = Button({ size.x - 10,0 }, 10, 10);
	}
	const int& x()const { return position.x; }
	const int& y()const { return position.y; }
	const int& width()const { return size.x; }
	const int& height()const { return size.y; }
	void moveBy(const int& x, const int& y) { position.x += x; position.y += y; }
	void moveTo(const Point2& pos) { position = pos; }
	void active(const bool& isActive) { this->isActive = isActive; }
	void addShape(const Shape& shape) {
		shapes.push_back(shape);
	}
	void moveShapeToFront(const int& index) {
		if (shapes.size() <= index) { std::cout << "Error: index out of bounds" << std::endl; exit(1); }
		shapes.push_back(shapes.at(index));
		shapes.erase(shapes.begin() + index);
	}
	void render(const Window& w)const {
		for (Shape s : shapes)s.render(w);
		if (isActive) {
			Draw::DrawFillRectangle(position, size, white, w.getRenderer());

			Draw::DrawLine(position, { position.x + size.x, position.y }, black, w.getRenderer());
			Draw::DrawLine({ position.x + size.x, position.y }, position + size, black, w.getRenderer());
			Draw::DrawLine(position + size, { position.x, position.y + size.y }, black, w.getRenderer());
			Draw::DrawLine({ position.x, position.y + size.y }, position, black, w.getRenderer());

			moveButton.render(position, black, w);
			closeButton.render(position, black, w);
		}
		else {
			Draw::DrawFillRectangle(position, size, gray, w.getRenderer());

			Draw::DrawLine(position, { position.x + size.x, position.y }, dark_gray, w.getRenderer());
			Draw::DrawLine({ position.x + size.x, position.y }, position + size, dark_gray, w.getRenderer());
			Draw::DrawLine(position + size, { position.x, position.y + size.y }, dark_gray, w.getRenderer());
			Draw::DrawLine({ position.x, position.y + size.y }, position, dark_gray, w.getRenderer());

			moveButton.render(position, dark_gray, w);
			closeButton.render(position, dark_gray, w);
		}
	}
	bool inside(const Point2& p)const {
		return p.x <= position.x + size.x && p.y <= position.y + size.y && p.x >= position.x && p.y >= position.y;
	}
	bool insideMoveButton(const Point2& p)const {
		return moveButton.inside(p - position);
	}
	bool insideCloseButton(const Point2& p)const {
		return closeButton.inside(p - position);
	}
	Point2 getRelativePosition(const Point2& p)const {
		return p - position;
	}
	float distanceToPanel(const Panel& p)const {
		const Point2 center(position + size / 2);
		const Point2 pcenter(p.position + p.size / 2);
		return Max(abs(center.x - pcenter.x) - (size.x + p.size.x) / 2, abs(center.y - pcenter.y) - (size.y + p.size.y) / 2);
	}
	bool closeHorizontal(const Panel& p)const {
		const Point2 center(position + size / 2);
		const Point2 pcenter(p.position + p.size / 2);
		return (abs(center.x - pcenter.x) - (size.x + p.size.x) / 2) < (abs(center.y - pcenter.y) - (size.y + p.size.y) / 2);
	}
};

class PanelManager {
	std::vector<Panel> panels;
	int active = -1; // index to currently active panel
	Point2 movementStart;
	bool movingPanel = false;
public:
	void addPanel(const Point2& position, const Point2& size) {
		panels.emplace_back(position, size);
	}
	void addPanel(const int& x, const int& y, const int& w, const int& h) {
		panels.emplace_back(x, y, w, h);
	}
	void checkForIntercation(const InputEvent& event) {
		bool clickedInPanel = false;
		for (int i = panels.size() - 1; i >= 0; i--) {
			if (event.mouse.leftClick || movingPanel == true) {
				if (panels[i].inside({ event.mouse.x,event.mouse.y }) || movingPanel == true) {
					if (active == i) {
						
					}
					else {
						active = i;
						panels[active].active(true);
						panels.push_back(panels.at(active));
						panels.erase(panels.begin() + active);
					}
					clickedInPanel = true;
					break;
				}
				else panels[i].active(false);
			}
		}
		if (clickedInPanel == false && movingPanel == false) active = -1;
		for (int i = panels.size() - 1; i >= 0; i--) {
			if (active == i) {
				if (event.mouse.leftClick == false) {
					movingPanel = false;
				}
				if (movingPanel) {
					panels[active].moveTo(Point2(event.mouse.x, event.mouse.y) - movementStart);
				}
				else if (panels[i].insideMoveButton({ event.mouse.x,event.mouse.y })) {
					movingPanel = true;
					movementStart = panels[active].getRelativePosition({ event.mouse.x,event.mouse.y });
				}
			}
			/*else if (movingPanel == true) {
				int distance = panels[active].distanceToPanel(panels[i]);
				if (abs(distance) < 10) {
					if (panels[active].closeHorizontal(panels[i])) {
						if (panels[active].y() < panels[i].y()) {
							panels[active].moveBy(0, abs(distance));
							movementStart.y+= abs(distance);
						}
						else {
							panels[active].moveBy(0, -abs(distance));
							movementStart.y+= -abs(distance);
						}
					}
					else {
						//panels[active].moveBy(1, 0);
						//movementStart.x++;
					}
				}
			}*/
		}
		for (int i = panels.size() - 1; i >= 0; i--) {
			if (event.mouse.leftClick && movingPanel == false && event.mouse.moving == false && panels[i].insideCloseButton({ event.mouse.x,event.mouse.y })) {
				if (i == active)active = -1;
				panels.erase(panels.begin() + i);
			}
		}
	}
	void render(const Window& w)const {
		for (Panel p : panels)p.render(w);
	}
};