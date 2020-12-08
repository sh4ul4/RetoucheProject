#pragma once

#include <map>
#include "Point.h"
#include "Draw.h"

class Shape {
	std::map<int,Point2> vertices; // each vertice has a link to the next as an indice (last links to first)
	bool filled = false;
	bool contoured = true;
	Color color = black;
public:
	const bool& fill()const { return filled; }
	const bool& contour()const { return contoured; }
	void fill(const bool& filled) { this->filled = filled; }
	void contour(const bool& contoured) { this->contoured = contoured; }
	void render(const Window& w)const {
		if (vertices.size() == 3) {
			if (filled)Draw::DrawFillTriangle(vertices.at(0), vertices.at(1), vertices.at(2), color, w.getRenderer());
			else if (contoured)Draw::DrawTriangle(vertices.at(0), vertices.at(1), vertices.at(2), color, w.getRenderer());
			else return;
		}
	}
};
