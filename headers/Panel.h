#pragma once

#include <iostream>
#include "Point.h"
#include "Shape.h"
#include "Texture.h"
#include "Input.h"
#include "Filter.h"
#include "InputBox.h"
#include <vector>
#include "Button.h"

class Panel {
protected:
	// Panel variables
	Point2 position;
	Point2 size;
	//std::vector<Shape> shapes;
	bool isActive = false;
	Button moveButton;
	Button closeButton;
	Button chooseButton;
public:
	Panel() = delete;
	Panel(const Point2& position, const Point2& size) :position(position), size(size) {
		if (size.x < 0 || size.y < 0) { std::cout << "Error: size can't be negative" << std::endl; exit(1); }
		moveButton = Button({ 0,0 }, 10, 10);
		closeButton = Button({ size.x - 10,0 }, 10, 10);
		chooseButton = Button({ 16,0 }, 10, 10);
	}
	Panel(const int& x, const int& y, const int& w, const int& h) :position({ x,y }), size({ w,h }) {
		if (size.x < 0 || size.y < 0) { std::cout << "Error: size can't be negative" << std::endl; exit(1); }
		moveButton = Button({ 0,0 }, 10, 10);
		closeButton = Button({ size.x - 10,0 }, 10, 10);
		chooseButton = Button({ 16,0 }, 10, 10);
	}
	const int& x()const { return position.x; }
	const int& y()const { return position.y; }
	const int& width()const { return size.x; }
	const int& height()const { return size.y; }
	void moveBy(const int& x, const int& y) { position.x += x; position.y += y; }
	void moveTo(const Point2& pos) { position = pos; }
	void active(const bool& isActive) { this->isActive = isActive; }
	/*void addShape(const Shape& shape) {
		shapes.push_back(shape);
	}*/
	void moveShapeToFront(const int& index) {
		/*if (shapes.size() <= index) { std::cout << "Error: index out of bounds" << std::endl; exit(1); }
		shapes.push_back(shapes.at(index));
		shapes.erase(shapes.begin() + index);*/
	}
	virtual void render(const Window& w)const {
		//for (Shape s : shapes)s.render(w);
		if (isActive) {
			Draw::DrawFillRectangle(position, size, white, w.getRenderer());

			Draw::DrawLine(position, { position.x + size.x, position.y }, black, w.getRenderer());
			Draw::DrawLine({ position.x + size.x, position.y }, position + size, black, w.getRenderer());
			Draw::DrawLine(position + size, { position.x, position.y + size.y }, black, w.getRenderer());
			Draw::DrawLine({ position.x, position.y + size.y }, position, black, w.getRenderer());

			moveButton.render(position, black, w);
			closeButton.render(position, black, w);
			chooseButton.render(position, black, w);
		}
		else {
			Draw::DrawFillRectangle(position, size, gray, w.getRenderer());

			Draw::DrawLine(position, { position.x + size.x, position.y }, dark_gray, w.getRenderer());
			Draw::DrawLine({ position.x + size.x, position.y }, position + size, dark_gray, w.getRenderer());
			Draw::DrawLine(position + size, { position.x, position.y + size.y }, dark_gray, w.getRenderer());
			Draw::DrawLine({ position.x, position.y + size.y }, position, dark_gray, w.getRenderer());

			moveButton.render(position, dark_gray, w);
			closeButton.render(position, dark_gray, w);
			chooseButton.render(position, dark_gray, w);
		}
	}
	virtual void checkForIntercations(const InputEvent& event, const Window& w) {
		if (isActive) {
			if (event.mouse.leftClick) {
				
			}
		}
		else {

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
	bool insideChooseButton(const Point2& p)const {
		return chooseButton.inside(p - position);
	}
	Point2 getRelativePosition(const Point2& p)const {
		return p - position;
	}
	/*float distanceToPanel(const Panel& p)const {
		const Point2 center(position + size / 2);
		const Point2 pcenter(p.position + p.size / 2);
		return Max(abs(center.x - pcenter.x) - (size.x + p.size.x) / 2, abs(center.y - pcenter.y) - (size.y + p.size.y) / 2);
	}
	bool closeHorizontal(const Panel& p)const {
		const Point2 center(position + size / 2);
		const Point2 pcenter(p.position + p.size / 2);
		return (abs(center.x - pcenter.x) - (size.x + p.size.x) / 2) < (abs(center.y - pcenter.y) - (size.y + p.size.y) / 2);
	}*/
};

class TexturePanel : public Panel {
	Texture texture;
	Point2 texturePosition;
	int textureW = 0;
	int textureH = 0;
	Button chooseFilterButton;
public:
	TexturePanel() = delete;
	TexturePanel(const int& x, const int& y, const int& w, const int& h, const char* path, const Window& win) :Panel(x,y,w,h),texture(path,win.getRenderer()) {
		texturePosition = { 1,11 };
		textureW = this->size.x - 1;
		textureH = this->size.y - 11;
		chooseFilterButton = Button({ 32,0 }, 10, 10);
	}
	void applyBasicFilter(const Window& w) {
		ContrastFilter filter;
		filter.filter(texture, w, 1);
	}
	void render(const Window& w) {
		Panel::render(w);
		texture.renderTexture(w.getRenderer(), position + texturePosition, textureW, textureH, 0, 0);
		Color buttonCol;
		if (isActive)buttonCol = black;
		else buttonCol = dark_gray;
		chooseFilterButton.render(position, buttonCol, w);
	}
	void savePNG() {
		texture.savePNG("../input/result.png");
	}
	bool insideChooseFilterButton(const Point2& p)const {
		return chooseFilterButton.inside(p - position);
	}
	void checkForIntercations(InputEvent& event, const Window& w) {
		Panel::checkForIntercations(event, w);
		if (isActive) {
			if (event.mouse.leftClick) {
				if (insideChooseFilterButton({ event.mouse.x,event.mouse.y })) {
					applyBasicFilter(w);
				}
			}
			if (event.keyboard.s) {
				savePNG();
				event.keyboard.s = false;
			}
		}
		else {

		}
	}
};

class SelectionPanel : public Panel {
	InputBox ib1;
public:
	SelectionPanel() = delete;
	SelectionPanel(const Point2& position, const Point2& size, const Window& w) :Panel(position, size), ib1(Point2(0, 20), 100, w) {
		//ib1 = InputBox(position + Point2(0, 20), 100, w);
	}
	void render(const Window& w) {
		Panel::render(w);
		ib1.render(position,w);
	}
	void checkForIntercations(InputEvent& event, const Window& w) {
		Panel::checkForIntercations(event, w);
		if (isActive) {
			ib1.update(event, position);
		}
		else {

		}
	}
};

class PanelManager {
	std::vector<std::shared_ptr<Panel>> panels;
	int active = -1; // index to currently active panel
	Point2 movementStart;
	bool movingPanel = false;
public:
	void addPanel(const Point2& position, const Point2& size) {
		panels.emplace_back(new Panel(position, size));
	}
	void addPanel(const int& x, const int& y, const int& w, const int& h) {
		panels.emplace_back(new Panel(x, y, w, h));
	}
	void addPanel(const int& x, const int& y, const int& w, const int& h, const char* path, const Window& win) {
		panels.emplace_back(new TexturePanel(x, y, w, h, path, win));
	}
	void addPanel(const Point2& position, const Point2& size, const Window& w) {
		panels.emplace_back(new SelectionPanel(position, size, w));
	}
	void checkForInteraction(InputEvent& event, const Window& w) {
		bool clickedInPanel = false;
		for (int i = panels.size() - 1; i >= 0; i--) {
			if (event.mouse.leftClick || movingPanel == true) {
				if (panels[i]->inside({ event.mouse.x,event.mouse.y }) || movingPanel == true) {
					if (active == i) {

					}
					else {
						active = i;
						panels[active]->active(true);
						moveItemToBack(panels, active);
					}
					clickedInPanel = true;
					break;
				}
				else panels[i]->active(false);
			}
		}
		if (clickedInPanel == false && event.mouse.leftClick && movingPanel == false) active = -1;
		for (int i = panels.size() - 1; i >= 0; i--) {
			if (active == i) {
				if (event.mouse.leftClick == false) {
					movingPanel = false;
				}
				if (movingPanel) {
					panels[active]->moveTo(Point2(event.mouse.x, event.mouse.y) - movementStart);
				}
				else if (panels[i]->insideMoveButton({ event.mouse.x,event.mouse.y })) {
					movingPanel = true;
					movementStart = panels[active]->getRelativePosition({ event.mouse.x,event.mouse.y });
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
			// call function for different derived classes
			TexturePanel* tmp1 = dynamic_cast<TexturePanel*>(panels[i].get());
			SelectionPanel* tmp2 = dynamic_cast<SelectionPanel*>(panels[i].get());
			//otherPanel tmp2... = ...
			//
			if (tmp1 != nullptr)tmp1->checkForIntercations(event, w);
			else if (tmp2 != nullptr)tmp2->checkForIntercations(event, w);
			// if(tmp2 ...) ...
			else { panels[i]->checkForIntercations(event, w); }

		}
		for (int i = panels.size() - 1; i >= 0; i--) {
			if (event.mouse.leftClick && movingPanel == false && event.mouse.moving == false && panels[i]->insideCloseButton({ event.mouse.x,event.mouse.y })) {
				if (i == active)active = -1;
				panels.erase(panels.begin() + i);
				event.mouse.leftClick = false;
			}
		}
	}
	void render(const Window& w)const {
		for (int i = 0; i < panels.size(); i++) {
			TexturePanel* tmp1 = dynamic_cast<TexturePanel*>(panels[i].get());
			SelectionPanel* tmp2 = dynamic_cast<SelectionPanel*>(panels[i].get());
			if (tmp1 != nullptr)tmp1->render(w);
			else if (tmp2 != nullptr)tmp2->render(w);
			else panels[i]->render(w);
		}
	}
};